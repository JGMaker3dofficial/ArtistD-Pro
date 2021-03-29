#include "../../../../MarlinCore.h"
#if ENABLED(TFT_LITTLE_VGL_UI)
#include "draw_ui.h"
#include "W25Qxx.h"
#include "pic_manager.h"
#include "tft_lvgl_configuration.h"
#include "../../../../module/motion.h"
#include "../../../../module/planner.h"
#include "../../../../sd/cardreader.h"
#if ENABLED(POWER_LOSS_RECOVERY)
#include "../../../../feature/powerloss.h"
#endif
#if ENABLED(PARK_HEAD_ON_PAUSE)
#include "../../../../feature/pause.h"
#endif
#include "../../../../gcode/gcode.h"


CFG_ITMES gCfgItems;
UI_CFG uiCfg;
DISP_STATE_STACK disp_state_stack;
DISP_STATE disp_state = MAIN_UI;
DISP_STATE last_disp_state;
PRINT_TIME print_time;
value_state value;

lv_point_t line_points[4][2] = { 
	{{PARA_UI_POS_X, PARA_UI_POS_Y+PARA_UI_SIZE_Y}, {TFT_WIDTH, PARA_UI_POS_Y+PARA_UI_SIZE_Y}},
	{{PARA_UI_POS_X, PARA_UI_POS_Y*2+PARA_UI_SIZE_Y}, {TFT_WIDTH, PARA_UI_POS_Y*2+PARA_UI_SIZE_Y}},
	{{PARA_UI_POS_X, PARA_UI_POS_Y*3+PARA_UI_SIZE_Y}, {TFT_WIDTH, PARA_UI_POS_Y*3+PARA_UI_SIZE_Y}},
	{{PARA_UI_POS_X, PARA_UI_POS_Y*4+PARA_UI_SIZE_Y}, {TFT_WIDTH, PARA_UI_POS_Y*4+PARA_UI_SIZE_Y}},
};

uint32_t To_pre_view;
uint8_t gcode_preview_over;
uint8_t flash_preview_begin;
uint8_t default_preview_flg;
uint32_t size = 809;
uint16_t row;
uint8_t temperature_change_frequency;
uint8_t printing_rate_update_flag;

extern uint8_t once_flag;
extern uint8_t sel_id;
extern uint8_t public_buf[512];
extern uint8_t bmp_public_buf[17*1024];

extern void LCD_IO_WriteData(uint16_t RegValue);

void gCfgItems_init(void)
{
	gCfgItems.multiple_language = MULTI_LANGUAGE_ENABLE;
	gCfgItems.language = LANG_ENGLISH;
	gCfgItems.leveling_mode = 0;
	gCfgItems.from_flash_pic = 0;
	gCfgItems.curFilesize = 0;
	gCfgItems.finish_power_off = 0;
	gCfgItems.dual_x_mode = REPRINT_FULL_CONTROL;
	gCfgItems.filamentchange_load_length   = 100;
	gCfgItems.filamentchange_load_speed    = 1000;
	gCfgItems.filamentchange_unload_length = 100;
	gCfgItems.filamentchange_unload_speed  = 1000;
	gCfgItems.filament_limit_temper        = 200;
	
	W25QXX.SPI_FLASH_BufferRead((uint8_t *)&gCfgItems.spi_flash_flag, VAR_INF_ADDR,sizeof(gCfgItems.spi_flash_flag));
	if(gCfgItems.spi_flash_flag == GCFG_FLAG_VALUE)
	{
		W25QXX.SPI_FLASH_BufferRead((uint8_t *)&gCfgItems, VAR_INF_ADDR,sizeof(gCfgItems));
	}
	else
	{
		gCfgItems.spi_flash_flag = GCFG_FLAG_VALUE;
		W25QXX.SPI_FLASH_SectorErase(VAR_INF_ADDR);
		W25QXX.SPI_FLASH_BufferWrite((uint8_t *)&gCfgItems, VAR_INF_ADDR,sizeof(gCfgItems));
	}
	#if ENABLED(DUAL_X_CARRIAGE)
	switch (gCfgItems.dual_x_mode)
	{
        case REPRINT_FULL_CONTROL:
			gcode.process_subcommands_now_P(PSTR("M605 S0"));
			break;
        case REPRINT_AUTO_PARK:
			gcode.process_subcommands_now_P(PSTR("M605 S1"));
          	break;
        case REPRINT_DUPLICATION:
			gcode.process_subcommands_now_P(PSTR("M605 S2"));
			break;
		case REPRINT_MIRROR:
			#if ENABLED(POWER_LOSS_RECOVERY)
			uint32_t sdpos_bak;
			sdpos_bak = recovery.info.sdpos;
			#endif
			gcode.process_subcommands_now_P(PSTR("M605 S2"));
			gcode.process_subcommands_now_P(PSTR("M605 S3"));
			while (
				planner.has_blocks_queued() || planner.cleaning_buffer_counter
				#if ENABLED(EXTERNAL_CLOSED_LOOP_CONTROLLER)
				|| (READ(CLOSED_LOOP_ENABLE_PIN) && !READ(CLOSED_LOOP_MOVE_COMPLETE_PIN))
				#endif
			);
			#if ENABLED(POWER_LOSS_RECOVERY)
			recovery.info.sdpos = sdpos_bak;
			#endif
          	break;
        default:
          	break;
      }
	#endif
}

void gCfg_to_spiFlah(void)
{
	W25QXX.SPI_FLASH_SectorErase(VAR_INF_ADDR);
	W25QXX.SPI_FLASH_BufferWrite((uint8_t *)&gCfgItems, VAR_INF_ADDR, sizeof(gCfgItems));
}

void ui_cfg_init(void)
{
	uiCfg.curTempType = 0;
	uiCfg.curSprayerChoose = 0;
	uiCfg.curSprayerLevel = 0;
	uiCfg.stepHeat = 50;
	uiCfg.leveling_first_time = 0;
	uiCfg.extruStep = 10;
	uiCfg.extruSpeed = 10;
	uiCfg.move_dist = 1;
	uiCfg.moveSpeed = 3000;
	uiCfg.stepPrintSpeed = 10;
	uiCfg.filament_heat_completed_load = 0;
	uiCfg.filament_rate                = 0;
	uiCfg.filament_loading_completed   = 0;
	uiCfg.filament_unloading_completed = 0;
	uiCfg.filament_loading_time_flg    = 0;
	uiCfg.filament_loading_time_cnt    = 0;
	uiCfg.filament_unloading_time_flg  = 0;
	uiCfg.filament_unloading_time_cnt  = 0;

	uiCfg.filament_loading_time = (uint32_t)((gCfgItems.filamentchange_load_length*60.0/gCfgItems.filamentchange_load_speed)+0.5);
  	uiCfg.filament_unloading_time = (uint32_t)((gCfgItems.filamentchange_unload_length*60.0/gCfgItems.filamentchange_unload_speed)+0.5);
}

void update_spi_flash(void)
{
	W25QXX.SPI_FLASH_SectorErase(VAR_INF_ADDR);
	W25QXX.SPI_FLASH_BufferWrite((uint8_t *)&gCfgItems, VAR_INF_ADDR, sizeof(gCfgItems));
}

lv_style_t tft_style_scr;
lv_style_t tft_style_label_pre;
lv_style_t tft_style_label_rel;

lv_style_t tft_style_label_sel_pre;
lv_style_t tft_style_label_sel_rel;
lv_style_t style_para_value_pre;
lv_style_t style_para_value_rel;

lv_style_t style_line;

lv_style_t style_num_key_pre;
lv_style_t style_num_key_rel;

lv_style_t style_num_text;

lv_style_t lv_bar_style_indic;

void tft_style_init(void)
{
	lv_style_copy(&tft_style_scr, &lv_style_scr);
	tft_style_scr.body.main_color.full  = 0x0000;
	tft_style_scr.body.grad_color.full  = 0x0000;
	tft_style_scr.text.color     		= LV_COLOR_TEXT;
	tft_style_scr.text.sel_color     	= LV_COLOR_TEXT;
	tft_style_scr.line.width   			= 0;
	tft_style_scr.text.letter_space 	= 0;
    tft_style_scr.text.line_space   	= 0;

	lv_style_copy(&tft_style_label_pre, &lv_style_scr);
	lv_style_copy(&tft_style_label_rel, &lv_style_scr);
	tft_style_label_pre.body.main_color.full	= 0x0000;
	tft_style_label_pre.body.grad_color.full	= 0x0000;
	tft_style_label_pre.text.color     			= LV_COLOR_TEXT;
	tft_style_label_pre.text.sel_color     		= LV_COLOR_TEXT;
	tft_style_label_rel.body.main_color.full	= 0x0000;
	tft_style_label_rel.body.grad_color.full	= 0x0000;	
	tft_style_label_rel.text.color     			= LV_COLOR_TEXT;
	tft_style_label_rel.text.sel_color     		= LV_COLOR_TEXT;
	tft_style_label_pre.text.font     			= &gb2312_puhui32;
	tft_style_label_rel.text.font     			= &gb2312_puhui32;
	tft_style_label_pre.line.width   			= 0;
	tft_style_label_rel.line.width   			= 0;
	tft_style_label_pre.text.letter_space 		= 0;
	tft_style_label_rel.text.letter_space 		= 0;
    tft_style_label_pre.text.line_space   		= -5;
	tft_style_label_rel.text.line_space   		= -5;

	lv_style_copy(&tft_style_label_sel_pre, &lv_style_scr);
	lv_style_copy(&tft_style_label_sel_rel, &lv_style_scr);
	tft_style_label_sel_pre.body.main_color		= LV_COLOR_YELLOW;
	tft_style_label_sel_pre.body.grad_color		= LV_COLOR_YELLOW;
	tft_style_label_sel_pre.text.color     		= LV_COLOR_BLACK;
	tft_style_label_sel_pre.text.sel_color     	= LV_COLOR_BLACK;
	tft_style_label_sel_rel.body.main_color		= LV_COLOR_BLACK;
	tft_style_label_sel_rel.body.grad_color		= LV_COLOR_BLACK;	
	tft_style_label_sel_rel.text.color     		= LV_COLOR_YELLOW;
	tft_style_label_sel_rel.text.sel_color     	= LV_COLOR_YELLOW;
	tft_style_label_sel_pre.text.font     		= &gb2312_puhui32;
	tft_style_label_sel_rel.text.font     		= &gb2312_puhui32;
	tft_style_label_sel_pre.line.width   		= 0;
	tft_style_label_sel_rel.line.width   		= 0;
	tft_style_label_sel_pre.text.letter_space 	= 0;
	tft_style_label_sel_rel.text.letter_space 	= 0;
    tft_style_label_sel_pre.text.line_space  	= -5;
	tft_style_label_sel_rel.text.line_space   	= -5;

	lv_style_copy(&style_num_key_pre, &lv_style_scr);
	lv_style_copy(&style_num_key_rel, &lv_style_scr);
	style_num_key_pre.body.main_color		= LV_COLOR_KEY_BACKGROUND;
	style_num_key_pre.body.grad_color		= LV_COLOR_KEY_BACKGROUND;
	style_num_key_pre.text.color     		= LV_COLOR_TEXT;
	style_num_key_pre.text.sel_color     	= LV_COLOR_TEXT;
	style_num_key_rel.body.main_color		= LV_COLOR_KEY_BACKGROUND;
	style_num_key_rel.body.grad_color		= LV_COLOR_KEY_BACKGROUND;	
	style_num_key_rel.text.color     		= LV_COLOR_TEXT;
	style_num_key_rel.text.sel_color     	= LV_COLOR_TEXT;
	style_num_key_pre.text.font     		= &gb2312_puhui32;
	style_num_key_rel.text.font     		= &gb2312_puhui32;
	style_num_key_pre.line.width   			= 0;
	style_num_key_rel.line.width   			= 0;
	style_num_key_pre.text.letter_space 	= 0;
	style_num_key_rel.text.letter_space 	= 0;
    style_num_key_pre.text.line_space   	= -5;
	style_num_key_rel.text.line_space   	= -5;

	lv_style_copy(&style_num_text, &lv_style_scr);

	style_num_text.body.main_color		= LV_COLOR_WHITE;
	style_num_text.body.grad_color		= LV_COLOR_WHITE;	
	style_num_text.text.color     		= LV_COLOR_BLACK;
	style_num_text.text.sel_color     	= LV_COLOR_BLACK;
	style_num_text.text.font     		= &gb2312_puhui32;
	style_num_text.line.width   		= 0;
	style_num_text.text.letter_space 	= 0;
	style_num_text.text.line_space   	= -5;

	lv_style_copy(&style_para_value_pre, &lv_style_scr);
	lv_style_copy(&style_para_value_rel, &lv_style_scr);
	style_para_value_pre.body.main_color		= LV_COLOR_BACKGROUND;
	style_para_value_pre.body.grad_color		= LV_COLOR_BACKGROUND;
	style_para_value_pre.text.color     		= LV_COLOR_TEXT;
	style_para_value_pre.text.sel_color     	= LV_COLOR_TEXT;
	style_para_value_rel.body.main_color		= LV_COLOR_BACKGROUND;
	style_para_value_rel.body.grad_color		= LV_COLOR_BACKGROUND;	
	style_para_value_rel.text.color     		= LV_COLOR_TEXT;
	style_para_value_rel.text.sel_color     	= LV_COLOR_TEXT;
	style_para_value_pre.text.font     			= &gb2312_puhui32;
	style_para_value_rel.text.font     			= &gb2312_puhui32;
	style_para_value_pre.line.width   			= 0;
	style_para_value_rel.line.width   			= 0;
	style_para_value_pre.text.letter_space 		= 0;
	style_para_value_rel.text.letter_space 		= 0;
    style_para_value_pre.text.line_space   		= -5;
	style_para_value_rel.text.line_space   		= -5;

	lv_style_copy(&style_line, &lv_style_plain);
    style_line.line.color = LV_COLOR_MAKE(0x49, 0x54, 0xff);
    style_line.line.width = 1;
    style_line.line.rounded = 1;
}

#define MAX_TITLE_LEN	28

char public_buf_m[100] = {0};
char public_buf_l[30];

void titleText_cat(char *str, int strSize, char *addPart)
{
	if(str == 0 || addPart == 0)
	{
		return;
	}

	if((int)(strlen(str) + strlen(addPart)) >= strSize)
	{
		return;
	}

	strcat(str, addPart);
}

char *getDispText(int index)
{
	memset(public_buf_l, 0, sizeof(public_buf_l));
	
	switch(disp_state_stack._disp_state[index])
	{
		case PRINT_READY_UI:
			strcpy(public_buf_l, main_menu.title);
			break;
		case PRINT_FILE_UI:
			strcpy(public_buf_l, file_menu.title);
			break;
		case PRINTING_UI:
			if(disp_state_stack._disp_state[disp_state_stack._disp_index] == PRINTING_UI
			#ifndef TFT35
			|| disp_state_stack._disp_state[disp_state_stack._disp_index] == OPERATE_UI
			#endif
			)
			{
				strcpy(public_buf_l, common_menu.print_special_title);
			}
			else
			{
				strcpy(public_buf_l, printing_menu.title);
			}
			break;
		case MOVE_MOTOR_UI:
			strcpy(public_buf_l, move_menu.title);
			break;
		case OPERATE_UI:
			if(disp_state_stack._disp_state[disp_state_stack._disp_index] == PRINTING_UI
			#ifndef TFT35
			|| disp_state_stack._disp_state[disp_state_stack._disp_index] == OPERATE_UI
			#endif
			)
			{
				strcpy(public_buf_l, common_menu.operate_special_title);
			}
			else
			{
				strcpy(public_buf_l, operation_menu.title);
			}
			break;
		case EXTRUSION_UI:
			strcpy(public_buf_l, extrude_menu.title);
			break;
		case CHANGE_SPEED_UI:
			strcpy(public_buf_l, speed_menu.title);
			break;
		case FAN_UI:
			strcpy(public_buf_l, fan_menu.title);
			break;
		case PRE_HEAT_UI:
			if((disp_state_stack._disp_state[disp_state_stack._disp_index - 1] == OPERATE_UI))
			{
				strcpy(public_buf_l,preheat_menu.adjust_title);
			}
			else
			{
				strcpy(public_buf_l, preheat_menu.title);
			} 			
			break;
		case SET_UI:
			strcpy(public_buf_l, set_menu.title);
			break;
		case ZERO_UI:
			strcpy(public_buf_l, home_menu.title);
			break;
		case LANGUAGE_UI:
			strcpy(public_buf_l, language_menu.title);
			break;
		case ABOUT_UI:
			strcpy(public_buf_l, about_menu.title);
			break;
		case DIALOG_UI:
			strcpy(public_buf_l, common_menu.dialog_confirm_title);
			break;	
		case FILAMENTCHANGE_UI:
			strcpy(public_buf_l, filament_menu.title); 		
			break;	
		case LEVELING_UI:
			strcpy(public_buf_l, leveling_menu.title); 					
			break;			
        case MOTOR_SETTINGS_UI:
            strcpy(public_buf_l, motor_settings_menu.title);
            break;
		case X_MODE_UI:
			strcpy(public_buf_l, x_mode_menu.title);
			break;
		case EEPROM_SETTINGS_UI:
			strcpy(public_buf_l, set_menu.eepromTitle);
			break;
		case TOOL_OFFSET_UI:
			strcpy(public_buf_l, t_offset_menu.title);
			break;
		default:
			break;
	}

	return public_buf_l;
}

char *creat_title_text()
{
	int index = 0;
	char *tmpText = 0;
	char tmpCurFileStr[20];
	
	memset(tmpCurFileStr, 0, sizeof(tmpCurFileStr));
	#if _LFN_UNICODE
	//cutFileName((TCHAR *)curFileName, 16, 16, (TCHAR *)tmpCurFileStr);	
	#else
	cutFileName(list_file.long_name[sel_id], 16, 16, tmpCurFileStr);
	#endif
	memset(public_buf_m, 0, sizeof(public_buf_m));
	
	while(index <= disp_state_stack._disp_index)
	{
		tmpText = getDispText(index);
		if((*tmpText == 0) || (tmpText == 0))
		{
			index++;
			continue;
		}
		
		titleText_cat(public_buf_m, sizeof(public_buf_m), tmpText);
		if(index < disp_state_stack._disp_index)
		{
			titleText_cat(public_buf_m, sizeof(public_buf_m), (char *)">");
		}
		
		index++;
	}
	
	if(disp_state_stack._disp_state[disp_state_stack._disp_index] == PRINTING_UI)
	{
		titleText_cat(public_buf_m, sizeof(public_buf_m), (char *)":");
		titleText_cat(public_buf_m, sizeof(public_buf_m), tmpCurFileStr);	
	}

	if(strlen(public_buf_m) > MAX_TITLE_LEN)
	{
		memset(public_buf_m, 0, sizeof(public_buf_m));
		tmpText = getDispText(0);
		if(*tmpText != 0)
		{
			titleText_cat(public_buf_m, sizeof(public_buf_m), tmpText);
			titleText_cat(public_buf_m, sizeof(public_buf_m), (char *)">...>");
			tmpText = getDispText(disp_state_stack._disp_index);
			if(*tmpText != 0)
			{
				titleText_cat(public_buf_m, sizeof(public_buf_m), tmpText);
			}
		}
		
	}

	return public_buf_m;
}

void preview_gcode_prehandle(char *path)
{
	#if ENABLED (SDSUPPORT)
	uint32_t pre_read_cnt = 0;
	uint32_t *p1;
	char *cur_name;
	
	cur_name=strrchr(path, '/');	
	card.openFileRead(cur_name);
	card.read(public_buf, 512);
	p1 = (uint32_t *)strstr((char *)public_buf, ";simage:");

	if(p1)
	{
		pre_read_cnt = (uint32_t)p1-(uint32_t)((uint32_t *)(&public_buf[0]));
		To_pre_view = pre_read_cnt;
		gcode_preview_over = 1;
		gCfgItems.from_flash_pic = 1;
		update_spi_flash();		
	}
	else
	{
		gcode_preview_over = 0;
		default_preview_flg = 1;
		gCfgItems.from_flash_pic = 0; 
		update_spi_flash();	
	}
	card.closefile();
	#endif
}

void gcode_preview(char *path, int xpos_pixel, int ypos_pixel)
{
	#if ENABLED (SDSUPPORT)
	volatile uint32_t i, j;
	volatile uint16_t *p_index;
	char *cur_name;
	
	cur_name=strrchr(path, '/');	
	card.openFileRead(cur_name);

	card.setIndex((PREVIEW_LITTLE_PIC_SIZE+To_pre_view)+size*row+8);
    ili9320_SetWindows(xpos_pixel, ypos_pixel+row, 200, 1);
	LCD_WriteRAM_Prepare(); 
	j=0;
	i=0;
		
	while(1)
	{
		card.read(public_buf, 400);
		for(i=0;i<400;)
		{
			bmp_public_buf[j]= ascii2dec_test((char*)&public_buf[i])<<4|ascii2dec_test((char*)&public_buf[i+1]);
			//bmp_public_buf[j]= ascii2dec_test1((char*)&buff_pic[8+i])<<4|ascii2dec_test1((char*)&buff_pic[8+i+1]);
			i+=2;
			j++;
		}
		
		//if(i>800)break;
		//#if defined(TFT70)
		//if(j>400)
		//{
		//	f_read(file, buff_pic, 1, &read);
		//	break;
		//}				
		//#elif defined(TFT35)
		if(j>=400)
		{
			//f_read(file, buff_pic, 1, &read);
			break;
		}				
		//#endif
	}

	for(i=0;i<400;)
	{
		p_index = (uint16_t *)(&bmp_public_buf[i]); 
		//if(*p_index == 0x0000)*p_index=gCfgItems.preview_bk_color;
		LCD_IO_WriteData(*p_index);
		i=i+2;
	}

	if(row<20)
	{
		W25QXX.SPI_FLASH_SectorErase(BAK_VIEW_ADDR_TFT35+row*4096);
	}
	W25QXX.SPI_FLASH_BufferWrite(bmp_public_buf, BAK_VIEW_ADDR_TFT35+row*400, 400);
	row++;

	if(row >= 200)
	{
		size = 809;
		row = 0;
		gcode_preview_over = 0;
		//flash_preview_begin = 1;

		card.closefile();

		/*if(gCurFileState.file_open_flag != 0xaa)
		{
			
		
			reset_file_info();
			
			res = f_open(file, curFileName, FA_OPEN_EXISTING | FA_READ);

			if(res == FR_OK)
			{
				f_lseek(file,PREVIEW_SIZE+To_pre_view);
				gCurFileState.file_open_flag = 0xaa;

				//bakup_file_path((uint8_t *)curFileName, strlen(curFileName));

				srcfp = file;

				mksReprint.mks_printer_state = MKS_WORKING;

				once_flag = 0;
			}
			
		}*/	
		char *cur_name;

		cur_name=strrchr(list_file.file_name[sel_id],'/');	

		SdFile file;
		SdFile *curDir;
		card.endFilePrint();
		const char *const fname = card.diveToFile(true, curDir, cur_name);
		if (!fname) return;
		if (file.open(curDir, fname, O_READ))
		{
			gCfgItems.curFilesize = file.fileSize();
			file.close();
			update_spi_flash();
		}
		
		card.openFileRead(cur_name);
		if (card.isFileOpen())
		{
			feedrate_percentage = 100;
			//saved_feedrate_percentage = feedrate_percentage;
			planner.flow_percentage[0] = 100;
			planner.e_factor[0]= planner.flow_percentage[0]*0.01;
			if(EXTRUDERS==2)
			{
				planner.flow_percentage[1] = 100;
				planner.e_factor[1]= planner.flow_percentage[1]*0.01;  
			}                            
			card.startFileprint();
			#if ENABLED(POWER_LOSS_RECOVERY)
			recovery.prepare();
			#endif
			once_flag = 0;
		}
		return;
	}
	
	card.closefile();
	#endif
}

void Draw_default_preview(int xpos_pixel, int ypos_pixel, uint8_t sel)
{
	int index; 
	int x_off = 0, y_off = 0;
	int _y;
	uint16_t *p_index;
	int i;
	uint16_t temp_p;
	
	for(index = 0; index < 10; index ++)//200*200
	{
		if(sel == 1)
		{
			flash_view_Read(bmp_public_buf, 8000);//20k
		}
		else
		{
			default_view_Read(bmp_public_buf, 8000);//20k
		}

		i = 0;
		
		ili9320_SetWindows(xpos_pixel, y_off*20+ypos_pixel, 200, 20);     //200*200

		LCD_WriteRAM_Prepare(); 
		for(_y = y_off * 20; _y < (y_off + 1) * 20; _y++)
		{
			for (x_off = 0; x_off < 200; x_off++) 
			{
				if(sel==1)
				{
					temp_p = (uint16_t)(bmp_public_buf[i]|bmp_public_buf[i+1]<<8);
					p_index = &temp_p;
				}
				else
				{
					p_index = (uint16_t *)(&bmp_public_buf[i]); 	
				}
				LCD_IO_WriteData(*p_index);
				i += 2;
				
			}
			if(i >= 8000)
				break;
		}
		y_off++;		
	}
}

void disp_pre_gcode(int xpos_pixel, int ypos_pixel)
{
	if(gcode_preview_over == 1)
	{
		gcode_preview(list_file.file_name[sel_id],xpos_pixel,ypos_pixel);
	}

	if(flash_preview_begin == 1)
	{
		flash_preview_begin = 0;
		Draw_default_preview(xpos_pixel,ypos_pixel,1);	
	}

	if(default_preview_flg == 1)
	{
		Draw_default_preview(xpos_pixel,ypos_pixel,0);
		default_preview_flg = 0;
	}
}

void print_time_run(void)
{
	static uint8_t lastSec = 0;
	
	if(print_time.seconds >= 60)
	{
		print_time.seconds = 0;
		print_time.minutes++;
		if(print_time.minutes >= 60)
		{
			print_time.minutes = 0;
			print_time.hours++;
		}
	}

	if(disp_state == PRINTING_UI)
	{
		if(lastSec != print_time.seconds)
		{
			disp_print_time();
		}
		lastSec =  print_time.seconds;
	}
}

void GUI_RefreshPage(void)
{
    if((systick_uptime_millis % 1000) == 0) 
		temperature_change_frequency=1;
	if((systick_uptime_millis % 3000) == 0)
		printing_rate_update_flag = 1;

	switch(disp_state)
	{
		case MAIN_UI:          
			lv_draw_ready_print(1);
			break;
		case EXTRUSION_UI:  
			if(temperature_change_frequency == 1)
			{
				temperature_change_frequency = 0;
				disp_hotend_temp();
			}
			break;
		case PRE_HEAT_UI:
			if(temperature_change_frequency == 1)
			{
				temperature_change_frequency = 0;
				disp_desire_temp();
			}
			break;
		case PRINT_READY_UI:
			/*if(gCfgItems.display_style == 2)
			{
				if(temperature_change_frequency){
					temperature_change_frequency=0;
					disp_restro_state();
				}
			}*/
			break;
		case PRINT_FILE_UI:
			break;
		case PRINTING_UI:
			if(temperature_change_frequency)
			{
				temperature_change_frequency = 0;
				disp_ext_temp();
				disp_bed_temp();
				disp_fan_speed();
				disp_print_time();
				disp_fan_Zpos();
			}
			if(printing_rate_update_flag || marlin_state == MF_SD_COMPLETE)
			{
				printing_rate_update_flag = 0;
				if(gcode_preview_over == 0)
				{
					setProBarRate();
				}
			}
			break;
		case OPERATE_UI:
			/*if(temperature_change_frequency == 1)
			{
				temperature_change_frequency = 0;
				disp_temp_operate();
			}
			setProBarRateOpera();*/
			break;
		case FAN_UI:
			if(temperature_change_frequency == 1)
			{
				temperature_change_frequency = 0;
				disp_fan_value();
			}
			break;
		case MOVE_MOTOR_UI:
			/*
			if(mksReprint.mks_printer_state == MKS_IDLE)
			{
				if((z_high_count==1)&&(temper_error_flg != 1)) 
				{
					z_high_count = 0;
					{
						
						memset((char *)gCfgItems.move_z_coordinate,' ',sizeof(gCfgItems.move_z_coordinate));
						GUI_DispStringAt((const char *)gCfgItems.move_z_coordinate,380, TITLE_YPOS);
						sprintf((char *)gCfgItems.move_z_coordinate,"Z: %.3f",current_position[Z_AXIS]);
						GUI_DispStringAt((const char *)gCfgItems.move_z_coordinate,380, TITLE_YPOS);
					}
				}
			}*/
			break;
		case FILAMENTCHANGE_UI:
			if(temperature_change_frequency)
			{
				temperature_change_frequency = 0;
				disp_filament_temp();
			}
			break;
		case DIALOG_UI:
			filament_dialog_handle();
			break;
		default:
			break;		
	}
	
	print_time_run();
}

void clear_cur_ui(void)
{
	last_disp_state = disp_state_stack._disp_state[disp_state_stack._disp_index];
	
	switch(disp_state_stack._disp_state[disp_state_stack._disp_index])
	{
		case PRINT_READY_UI:	
			lv_clear_ready_print();
			break;
		case PRINT_FILE_UI:
			lv_clear_print_file();
			break;
		case PRINTING_UI:
			lv_clear_printing();
			break;
		case MOVE_MOTOR_UI:
			lv_clear_move_motor();
			break;
		case OPERATE_UI:
			lv_clear_opration();
			break;
		case EXTRUSION_UI:
			lv_clear_extrusion();
			break;
		case PRE_HEAT_UI:
			lv_clear_preHeat();
			break;
		case CHANGE_SPEED_UI:
			lv_clear_change_speed();
			break;
		case FAN_UI:
			lv_clear_fan();
			break;
		case SET_UI:
			lv_clear_set();
			break;
		case ZERO_UI:
			lv_clear_home();
			break;
		case LANGUAGE_UI:
			lv_clear_language();
			break;
		case ABOUT_UI:
			lv_clear_about();
			break;
		case DIALOG_UI:
			lv_clear_dialog();
			break;
		case LEVELING_UI:
			lv_clear_manualLevel();
			break;
		case MOTOR_SETTINGS_UI:
			lv_clear_motor_settings();
			break;
		case FILAMENTCHANGE_UI:
			lv_clear_filament_change();
			break;  
		case NUMBER_KEY_UI:
			lv_clear_number_key();
			break;
		case X_MODE_UI:
			lv_clear_x_mode();
			break;
		case EEPROM_SETTINGS_UI:
			lv_clear_eeprom_settings();
			break;
		case TOOL_OFFSET_UI:
			lv_clear_tool_offset();
			break;
		default:
			break;
	}
}

void draw_return_ui(void)
{
	if(disp_state_stack._disp_index > 0)
	{
		disp_state_stack._disp_index--;
		
		switch(disp_state_stack._disp_state[disp_state_stack._disp_index])
		{
			case PRINT_READY_UI:
				lv_draw_ready_print(1);
				break;
			case PRINT_FILE_UI:
				lv_draw_print_file();
				break;
			case PRINTING_UI:
				if(gCfgItems.from_flash_pic == 1)
					flash_preview_begin = 1;
				else
					default_preview_flg = 1; 
				lv_draw_printing();
				break;
			case MOVE_MOTOR_UI:
				lv_draw_move_motor();
				break;
			case OPERATE_UI:
				lv_draw_opration();
				break;
			case EXTRUSION_UI:
				lv_draw_extrusion();
				break;
			case PRE_HEAT_UI:
				lv_draw_preHeat();
				break;
			case CHANGE_SPEED_UI:
				lv_draw_change_speed();
				break;
			case FAN_UI:
				lv_draw_fan();
				break;
			case SET_UI:
				lv_draw_set();
				break;
			case ZERO_UI:
				lv_draw_home();
				break;
			case LANGUAGE_UI:
				lv_draw_language();
				break;
			case ABOUT_UI:
				lv_draw_about();
				break;
			case FILAMENTCHANGE_UI:
				lv_draw_filament_change();
				break;
			case LEVELING_UI:
				lv_draw_manualLevel();
				break;
			case MOTOR_SETTINGS_UI:
				lv_draw_motor_settings();
				break;  
			case NUMBER_KEY_UI:
				//draw_NumberKey();
				break;  
			case DIALOG_UI:
				//draw_dialog(DialogType);
				break;
			#if ENABLED(DUAL_X_CARRIAGE)
			case X_MODE_UI:
				lv_draw_x_mode();
				break;
			#endif
			case EEPROM_SETTINGS_UI:
				lv_draw_eeprom_settings();
				break;
			case TOOL_OFFSET_UI:
				lv_draw_tool_offset();
				break;
			default:
				break;
		}
	}
}

#if ENABLED (SDSUPPORT)
void sd_detection(void)
{
	#if ENABLED(SDSUPPORT)
    static bool last_sd_status;
    const bool sd_status = IS_SD_INSERTED();

    if (sd_status != last_sd_status)
	{
		last_sd_status = sd_status;
		if (sd_status) {
			card.mount();
		}
		else {
			card.release();
		}
    }
  #endif // SDSUPPORT
}
#endif

extern volatile uint32_t systick_uptime_millis;

void print_time_count(void)
{
	if((systick_uptime_millis % 1000) == 0) 
	{		
		if(print_time.start == 1)
		{
			print_time.seconds++;
		}
	}
}

void printer_action_polling(void)
{
	if(uiCfg.print_state == REPRINTED)
	{
		uiCfg.print_state = WORKING;
		#if ENABLED(POWER_LOSS_RECOVERY)
		recovery.resume();
		#endif
	}
}

void lv_ex_line(lv_obj_t *line, lv_point_t *points)
{
    /*Copy the previous line and apply the new style*/
    lv_line_set_points(line, points, 2);     /*Set the points*/
    lv_line_set_style(line, LV_LINE_STYLE_MAIN, &style_line);
    lv_obj_align(line, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
}

#endif
