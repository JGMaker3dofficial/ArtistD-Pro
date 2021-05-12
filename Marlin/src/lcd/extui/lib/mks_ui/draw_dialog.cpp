#include "../../../../MarlinCore.h"
#if ENABLED(TFT_LITTLE_VGL_UI)
#include "draw_ui.h"
#include "../../sd/cardreader.h"
#include "../../../../gcode/queue.h"
#include "../../../../module/temperature.h"
#include "../../../../module/planner.h"
#if ENABLED(POWER_LOSS_RECOVERY)
#include "../../../../feature/powerloss.h"
#endif
#if ENABLED(PARK_HEAD_ON_PAUSE)
#include "../../../../feature/pause.h"
#endif
#include "../../../../gcode/gcode.h"
#if ENABLED(DUAL_X_CARRIAGE)
#include "../../../../module/motion.h"
#endif


static lv_obj_t *scr;
extern uint8_t sel_id;
extern uint8_t once_flag;
extern uint8_t gcode_preview_over;
static uint8_t DialogType;
static lv_obj_t *tempText1;
static lv_obj_t *filament_bar;
extern uint8_t temperature_change_frequency;

static void btn_ok_event_cb(lv_obj_t *btn, lv_event_t event)
{
    if(event == LV_EVENT_CLICKED) {
       
    }
    else if(event == LV_EVENT_RELEASED)
    {
    	if(DialogType == DIALOG_TYPE_PRINT_FILE)
    	{
    		#if ENABLED(FILAMENT_RUNOUT_SENSOR)
    		if(READ(FIL_RUNOUT1_PIN) == FIL_RUNOUT_INVERTING
			#if PIN_EXISTS(FIL_RUNOUT2)
			|| READ(FIL_RUNOUT2_PIN) == FIL_RUNOUT_INVERTING
			#endif
			#if PIN_EXISTS(FIL_RUNOUT3)
			|| READ(FIL_RUNOUT2_PIN) == FIL_RUNOUT_INVERTING
			#endif
			)
    		{
    			lv_clear_dialog();
				lv_draw_dialog(DIALOG_TYPE_FILAMENT_NO_PRESS);
    		}
			else
			#endif
			{
				#if ENABLED(DUAL_X_CARRIAGE)
				if(dual_x_carriage_mode == DXC_DUPLICATION_MODE)
				{
					gcode.process_subcommands_now_P(PSTR("M605 S2"));
					//gcode.process_subcommands_now_P(PSTR("G91\nG1 Z5\nG90"));
					//planner.synchronize();
				}
				#endif
				preview_gcode_prehandle(list_file.file_name[sel_id]);
				reset_print_time();
				start_print_time();
				
				uiCfg.print_state = WORKING;
				lv_clear_dialog();
				lv_draw_printing();
			
				if(gcode_preview_over != 1)
				{
					#if ENABLED (SDSUPPORT)
					char *cur_name;
					cur_name = strrchr(list_file.file_name[sel_id],'/');

					SdFile file;
					SdFile *curDir;
					card.endFilePrint();
					const char * const fname = card.diveToFile(true, curDir, cur_name);
					if (!fname) 
						return;
					if (file.open(curDir, fname, O_READ))
					{
						gCfgItems.curFilesize = file.fileSize();
						file.close();
						update_spi_flash();
					}
					card.openFileRead(cur_name);
					if(card.isFileOpen())
					{	   
						feedrate_percentage = 100;
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
					#endif
				}
			}
    	}
		else if(DialogType == DIALOG_TYPE_STOP)
		{
			wait_for_heatup = false;
			stop_print_time();
			lv_clear_dialog();
			lv_draw_ready_print(1);

			#if ENABLED (SDSUPPORT)
			//card.endFilePrint();
			//wait_for_heatup = false;
			uiCfg.print_state = IDLE;
			card.flag.abort_sd_printing = true;
			//queue.clear();
			//quickstop_stepper();
			//print_job_timer.stop();
			//thermalManager.disable_all_heaters();

			//#if ENABLED(POWER_LOSS_RECOVERY)
			//recovery.purge();
			//#endif
			//queue.enqueue_one_now(PSTR("G91"));
			//queue.enqueue_one_now(PSTR("G1 Z10"));
			//queue.enqueue_one_now(PSTR("G90"));
			//queue.enqueue_one_now(PSTR("G28 X0 Y0"));
			//queue.inject_P(PSTR("G91\nG1 Z10\nG90\nG28 X0 Y0\nM84\nM107"));
			#endif
		}
		else if(DialogType == DIALOG_TYPE_FINISH_PRINT)
		{
			clear_cur_ui();
			lv_draw_ready_print(1);
		}
		#if ENABLED(ADVANCED_PAUSE_FEATURE)
		else if(DialogType == DIALOG_PAUSE_MESSAGE_WAITING
			||DialogType == DIALOG_PAUSE_MESSAGE_INSERT
			||DialogType == DIALOG_PAUSE_MESSAGE_HEAT)
		{
			wait_for_user = false;
		}
		else if(DialogType == DIALOG_PAUSE_MESSAGE_OPTION)
		{
			pause_menu_response = PAUSE_RESPONSE_EXTRUDE_MORE;
		}
		else if(DialogType == DIALOG_PAUSE_MESSAGE_RESUME)
		{
			clear_cur_ui();
			draw_return_ui();
		}
		#endif
		else if(DialogType == DIALOG_TYPE_FILAMENT_NO_PRESS)
		{
			clear_cur_ui();
			draw_return_ui();
		}
		else if(DialogType == DIALOG_REVERT_EEPROM_TIPS)
		{
			gCfgItems.filamentchange_load_length   = 100;
			gCfgItems.filamentchange_load_speed    = 1000;
			gCfgItems.filamentchange_unload_length = 100;
			gCfgItems.filamentchange_unload_speed  = 1000;
			gCfgItems.filament_limit_temper        = 200;
			gcode.process_subcommands_now_P(PSTR("M502"));
			gcode.process_subcommands_now_P(PSTR("M500"));
			update_spi_flash();
			clear_cur_ui();
			draw_return_ui();
		}
		else if (DialogType == DIALOG_TYPE_FILAMENT_HEAT_LOAD_COMPLETED)
		{
      		uiCfg.filament_heat_completed_load = 1;
    	}
    	else if (DialogType == DIALOG_TYPE_FILAMENT_HEAT_UNLOAD_COMPLETED)
		{
      		uiCfg.filament_heat_completed_unload = 1;
    	}
    	else if (DialogType == DIALOG_TYPE_FILAMENT_LOAD_COMPLETED 
          || DialogType == DIALOG_TYPE_FILAMENT_UNLOAD_COMPLETED
    	)
		{
			clear_cur_ui();
			draw_return_ui();
		}
		else
		{
			clear_cur_ui();
			draw_return_ui();
		}
    }
}

static void btn_cancel_event_cb(lv_obj_t *btn, lv_event_t event)
{
    if(event == LV_EVENT_CLICKED) {
       
    }
    else if(event == LV_EVENT_RELEASED)
    {
    	if(DialogType == DIALOG_PAUSE_MESSAGE_OPTION)
		{
			#if ENABLED(ADVANCED_PAUSE_FEATURE)
			pause_menu_response = PAUSE_RESPONSE_RESUME_PRINT;
			#endif
		}
		else if ((DialogType == DIALOG_TYPE_FILAMENT_LOAD_HEAT)
			    || (DialogType == DIALOG_TYPE_FILAMENT_UNLOAD_HEAT)
				|| (DialogType == DIALOG_TYPE_FILAMENT_HEAT_LOAD_COMPLETED)
				|| (DialogType == DIALOG_TYPE_FILAMENT_HEAT_UNLOAD_COMPLETED))
		{
			thermalManager.temp_hotend[uiCfg.curSprayerChoose].target = uiCfg.desireSprayerTempBak;
			clear_cur_ui();
			draw_return_ui();
		}
		else if ((DialogType == DIALOG_TYPE_FILAMENT_LOADING)
			|| (DialogType == DIALOG_TYPE_FILAMENT_UNLOADING))
		{
			queue.enqueue_one_P(PSTR("M410"));
			uiCfg.filament_rate                = 0;
			uiCfg.filament_loading_completed   = 0;
			uiCfg.filament_unloading_completed = 0;
			uiCfg.filament_loading_time_flg    = 0;
			uiCfg.filament_loading_time_cnt    = 0;
			uiCfg.filament_unloading_time_flg  = 0;
			uiCfg.filament_unloading_time_cnt  = 0;
			thermalManager.temp_hotend[uiCfg.curSprayerChoose].target = uiCfg.desireSprayerTempBak;
			clear_cur_ui();
			draw_return_ui();
		}
		else
		{
			clear_cur_ui();
			draw_return_ui();
		}
    }
}

void lv_draw_dialog(uint8_t type)
{
	if(disp_state_stack._disp_state[disp_state_stack._disp_index] != DIALOG_UI)
	{
		disp_state_stack._disp_index++;
		disp_state_stack._disp_state[disp_state_stack._disp_index] = DIALOG_UI;
	}
	disp_state = DIALOG_UI;

	DialogType = type;

	scr = lv_obj_create(NULL, NULL);
	
	lv_obj_set_style(scr, &tft_style_scr);
  	lv_scr_load(scr);
  	lv_obj_clean(scr);

  	lv_obj_t *title = lv_label_create(scr, NULL);
	lv_obj_set_style(title, &tft_style_label_rel);
	lv_obj_set_pos(title, TITLE_XPOS, TITLE_YPOS);
	lv_label_set_text(title, creat_title_text());
  
  	lv_refr_now(lv_refr_get_disp_refreshing());
	
	//LV_IMG_DECLARE(bmp_pic);

	static lv_style_t style_btn_rel;                        /*A variable to store the released style*/
	lv_style_copy(&style_btn_rel, &lv_style_plain);         /*Initialize from a built-in style*/
	style_btn_rel.body.border.color = lv_color_hex3(0x269);
	style_btn_rel.body.border.width = 1;
	style_btn_rel.body.main_color = lv_color_hex3(0xADF);
	style_btn_rel.body.grad_color = lv_color_hex3(0x46B);
	style_btn_rel.body.shadow.width = 4;
	style_btn_rel.body.shadow.type = LV_SHADOW_BOTTOM;
	style_btn_rel.body.radius = LV_RADIUS_CIRCLE;
	style_btn_rel.text.color = lv_color_hex3(0xDEF);
	style_btn_rel.text.font = &gb2312_puhui32;
	
	static lv_style_t style_btn_pr;                         /*A variable to store the pressed style*/
	lv_style_copy(&style_btn_pr, &style_btn_rel);           /*Initialize from the released style*/
	style_btn_pr.body.border.color = lv_color_hex3(0x46B);
	style_btn_pr.body.main_color = lv_color_hex3(0x8BD);
	style_btn_pr.body.grad_color = lv_color_hex3(0x24A);
	style_btn_pr.body.shadow.width = 2;
	style_btn_pr.text.color = lv_color_hex3(0xBCD);
	style_btn_pr.text.font  = &gb2312_puhui32;

	lv_obj_t *labelDialog = lv_label_create(scr, NULL);
	lv_obj_set_style(labelDialog, &tft_style_label_rel);
    	
	if(DialogType == DIALOG_TYPE_FINISH_PRINT 
		|| DialogType == DIALOG_PAUSE_MESSAGE_RESUME
		|| DialogType == DIALOG_TYPE_FILAMENT_NO_PRESS)
	{
		lv_obj_t *btnOk = lv_btn_create(scr, NULL);     				/*Add a button the current screen*/
		lv_obj_set_pos(btnOk, BTN_OK_X+90, BTN_OK_Y);                   /*Set its position*/
		lv_obj_set_size(btnOk, 100, 50);                          		/*Set its size*/
		lv_obj_set_event_cb(btnOk, btn_ok_event_cb); 
		lv_btn_set_style(btnOk, LV_BTN_STYLE_REL, &style_btn_rel);    	/*Set the button's released style*/
		lv_btn_set_style(btnOk, LV_BTN_STYLE_PR, &style_btn_pr);      	/*Set the button's pressed style*/
		lv_obj_t *labelOk = lv_label_create(btnOk, NULL);          		/*Add a label to the button*/
		lv_label_set_text(labelOk, print_file_dialog_menu.confirm);  	/*Set the labels text*/
	}
	else if(DialogType == DIALOG_PAUSE_MESSAGE_WAITING
		||DialogType == DIALOG_PAUSE_MESSAGE_INSERT
		||DialogType == DIALOG_PAUSE_MESSAGE_HEAT)
	{
		lv_obj_t *btnOk = lv_btn_create(scr, NULL);     				/*Add a button the current screen*/
		lv_obj_set_pos(btnOk, BTN_OK_X+90, BTN_OK_Y);                   /*Set its position*/
		lv_obj_set_size(btnOk, 100, 50);                          		/*Set its size*/
		lv_obj_set_event_cb(btnOk, btn_ok_event_cb); 
		lv_btn_set_style(btnOk, LV_BTN_STYLE_REL, &style_btn_rel);    	/*Set the button's released style*/
		lv_btn_set_style(btnOk, LV_BTN_STYLE_PR, &style_btn_pr);      	/*Set the button's pressed style*/
		lv_obj_t *labelOk = lv_label_create(btnOk, NULL);          		/*Add a label to the button*/
		lv_label_set_text(labelOk, print_file_dialog_menu.confirm);  	/*Set the labels text*/		
	}
	else if(DialogType == DIALOG_PAUSE_MESSAGE_PAUSING
		||DialogType == DIALOG_PAUSE_MESSAGE_CHANGING
		||DialogType == DIALOG_PAUSE_MESSAGE_UNLOAD
		||DialogType == DIALOG_PAUSE_MESSAGE_LOAD
		||DialogType == DIALOG_PAUSE_MESSAGE_PURGE
		||DialogType == DIALOG_PAUSE_MESSAGE_RESUME
		||DialogType == DIALOG_PAUSE_MESSAGE_HEATING)
	{

	}
	else if (DialogType == DIALOG_TYPE_FILAMENT_LOAD_HEAT
  	    || DialogType == DIALOG_TYPE_FILAMENT_UNLOAD_HEAT)
	{
		lv_obj_t *btnCancel = lv_btn_create(scr, NULL);     
		lv_obj_set_pos(btnCancel, BTN_OK_X+90, BTN_OK_Y);                           
		lv_obj_set_size(btnCancel, 100, 50);                         
		lv_obj_set_event_cb(btnCancel, btn_cancel_event_cb); 
		lv_btn_set_style(btnCancel, LV_BTN_STYLE_REL, &style_btn_rel);   
		lv_btn_set_style(btnCancel, LV_BTN_STYLE_PR, &style_btn_pr);      
		lv_obj_t *labelCancel = lv_label_create(btnCancel, NULL);          
		lv_label_set_text(labelCancel, print_file_dialog_menu.cancle);

		tempText1 = lv_label_create(scr, NULL);
		lv_obj_set_style(tempText1, &tft_style_label_rel);
		filament_sprayer_temp();
	}
	else if (DialogType == DIALOG_TYPE_FILAMENT_LOAD_COMPLETED
		|| DialogType == DIALOG_TYPE_FILAMENT_UNLOAD_COMPLETED)
	{
		lv_obj_t *btnOk = lv_btn_create(scr, NULL);     
		lv_obj_set_pos(btnOk, BTN_OK_X+90, BTN_OK_Y);                           
		lv_obj_set_size(btnOk, 100, 50);                        
		lv_obj_set_event_cb(btnOk, btn_ok_event_cb); 
		lv_btn_set_style(btnOk, LV_BTN_STYLE_REL, &style_btn_rel);   
		lv_btn_set_style(btnOk, LV_BTN_STYLE_PR, &style_btn_pr);     
		lv_obj_t *labelOk = lv_label_create(btnOk, NULL);          
		lv_label_set_text(labelOk, print_file_dialog_menu.confirm);
	}
	else if (DialogType == DIALOG_TYPE_FILAMENT_LOADING
		|| DialogType == DIALOG_TYPE_FILAMENT_UNLOADING)
	{
		lv_style_copy(&lv_bar_style_indic, &lv_style_pretty_color);
		lv_bar_style_indic.text.color        = lv_color_hex3(0xADF);
		lv_bar_style_indic.image.color       = lv_color_hex3(0xADF);
		lv_bar_style_indic.line.color        = lv_color_hex3(0xADF);
		lv_bar_style_indic.body.main_color   = lv_color_hex3(0xADF);
		lv_bar_style_indic.body.grad_color   = lv_color_hex3(0xADF);
		lv_bar_style_indic.body.border.color = lv_color_hex3(0xADF);

		lv_obj_t *btnCancel = lv_btn_create(scr, NULL);     
		lv_obj_set_pos(btnCancel, BTN_OK_X+90, BTN_OK_Y);                           
		lv_obj_set_size(btnCancel, 100, 50);                         
		lv_obj_set_event_cb(btnCancel, btn_cancel_event_cb); 
		lv_btn_set_style(btnCancel, LV_BTN_STYLE_REL, &style_btn_rel);   
		lv_btn_set_style(btnCancel, LV_BTN_STYLE_PR, &style_btn_pr);      
		lv_obj_t *labelCancel = lv_label_create(btnCancel, NULL);          
		lv_label_set_text(labelCancel, print_file_dialog_menu.cancle);

		filament_bar = lv_bar_create(scr, NULL);
		lv_obj_set_pos(filament_bar, (TFT_WIDTH-400)/2, ((TFT_HEIGHT - titleHeight)-40)/2);
		lv_obj_set_size(filament_bar, 400, 25);
		lv_bar_set_style(filament_bar, LV_BAR_STYLE_INDIC, &lv_bar_style_indic);
		lv_bar_set_anim_time(filament_bar, 1000);
		lv_bar_set_value(filament_bar, 0, LV_ANIM_ON);
	}
	else
	{
		lv_obj_t *btnOk = lv_btn_create(scr, NULL);     					/*Add a button the current screen*/
		lv_obj_set_pos(btnOk, BTN_OK_X, BTN_OK_Y);                          /*Set its position*/
		lv_obj_set_size(btnOk, 100, 50);                          			/*Set its size*/
		lv_obj_set_event_cb(btnOk, btn_ok_event_cb); 
		lv_btn_set_style(btnOk, LV_BTN_STYLE_REL, &style_btn_rel);    		/*Set the button's released style*/
		lv_btn_set_style(btnOk, LV_BTN_STYLE_PR, &style_btn_pr);      		/*Set the button's pressed style*/
		lv_obj_t *labelOk = lv_label_create(btnOk, NULL);          			/*Add a label to the button*/
		
		lv_obj_t *btnCancel = lv_btn_create(scr, NULL);     				/*Add a button the current screen*/
		lv_obj_set_pos(btnCancel, BTN_CANCEL_X, BTN_CANCEL_Y);              /*Set its position*/
		lv_obj_set_size(btnCancel, 100, 50);                          		/*Set its size*/
		lv_obj_set_event_cb(btnCancel, btn_cancel_event_cb); 
		lv_btn_set_style(btnCancel, LV_BTN_STYLE_REL, &style_btn_rel);    	/*Set the button's released style*/
		lv_btn_set_style(btnCancel, LV_BTN_STYLE_PR, &style_btn_pr);      	/*Set the button's pressed style*/
		lv_obj_t *labelCancel = lv_label_create(btnCancel, NULL);          	/*Add a label to the button*/

		if(DialogType == DIALOG_PAUSE_MESSAGE_OPTION)
		{
			lv_label_set_text(labelOk, pause_msg_menu.purgeMore);  				/*Set the labels text*/
			lv_label_set_text(labelCancel, pause_msg_menu.continuePrint);
		}
		else
		{
			lv_label_set_text(labelOk, print_file_dialog_menu.confirm);  		/*Set the labels text*/
			lv_label_set_text(labelCancel, print_file_dialog_menu.cancle);
		}
	}

	//Alarm after material depletion
	if(DialogType == DIALOG_PAUSE_MESSAGE_CHANGING)
	{
		if(READ(FIL_RUNOUT1_PIN)||READ(FIL_RUNOUT2_PIN))
		{
			extDigitalWrite(BEEPER_PIN,HIGH);
		}
	}
	else
	{
		extDigitalWrite(BEEPER_PIN,LOW);
	}

	if(DialogType == DIALOG_TYPE_PRINT_FILE)
	{
		lv_label_set_text(labelDialog, print_file_dialog_menu.print_file);
		lv_obj_align(labelDialog, NULL, LV_ALIGN_CENTER, 0, -20);

		lv_obj_t *labelFile = lv_label_create(scr, NULL);
		lv_obj_set_style(labelFile, &tft_style_label_rel);

		lv_label_set_text(labelFile, list_file.long_name[sel_id]);
		lv_obj_align(labelFile, NULL, LV_ALIGN_CENTER, 0, -60);
	}
	else if(DialogType == DIALOG_TYPE_STOP)
	{
		lv_label_set_text(labelDialog, print_file_dialog_menu.cancle_print);
		lv_obj_align(labelDialog, NULL, LV_ALIGN_CENTER, 0, -20);
	}
	else if(DialogType == DIALOG_TYPE_FINISH_PRINT)
	{
		lv_label_set_text(labelDialog, print_file_dialog_menu.print_finish);
		lv_obj_align(labelDialog, NULL, LV_ALIGN_CENTER, 0, -60);

		lv_obj_t *labelPrinttime = lv_label_create(scr, NULL);
		lv_obj_set_style(labelPrinttime, &tft_style_label_rel);
		memset(public_buf_m, 0, sizeof(public_buf_m));
		strcat(public_buf_m, print_file_dialog_menu.print_time);
		sprintf(&public_buf_m[strlen(print_file_dialog_menu.print_time)], "%d%d:%d%d:%d%d", print_time.hours/10, print_time.hours%10, print_time.minutes/10, print_time.minutes%10,  print_time.seconds/10, print_time.seconds%10);
		lv_label_set_text(labelPrinttime, public_buf_m);
		lv_obj_align(labelPrinttime, NULL, LV_ALIGN_CENTER, 0, -20);
	}
	else if(DialogType == DIALOG_PAUSE_MESSAGE_PAUSING)
	{
		lv_label_set_text(labelDialog, pause_msg_menu.pausing);
		lv_obj_align(labelDialog, NULL, LV_ALIGN_CENTER, 0, -20);
	}
	else if(DialogType == DIALOG_PAUSE_MESSAGE_CHANGING)
	{
		lv_label_set_text(labelDialog, pause_msg_menu.changing);
		lv_obj_align(labelDialog, NULL, LV_ALIGN_CENTER, 0, -20);
	}
	else if(DialogType == DIALOG_PAUSE_MESSAGE_UNLOAD)
	{
		lv_label_set_text(labelDialog, pause_msg_menu.unload);
		lv_obj_align(labelDialog, NULL, LV_ALIGN_CENTER, 0, -20);
	}
	else if(DialogType == DIALOG_PAUSE_MESSAGE_WAITING)
	{
		lv_label_set_text(labelDialog, pause_msg_menu.waiting);
		lv_obj_align(labelDialog, NULL, LV_ALIGN_CENTER, 0, -20);
	}
	else if(DialogType == DIALOG_PAUSE_MESSAGE_INSERT)
	{
		lv_label_set_text(labelDialog, pause_msg_menu.insert);
		lv_obj_align(labelDialog, NULL, LV_ALIGN_CENTER, 0, -20);
	}
	else if(DialogType == DIALOG_PAUSE_MESSAGE_LOAD)
	{
		lv_label_set_text(labelDialog, pause_msg_menu.load);
		lv_obj_align(labelDialog, NULL, LV_ALIGN_CENTER, 0, -20);
	}
	else if(DialogType == DIALOG_PAUSE_MESSAGE_PURGE)
	{
		lv_label_set_text(labelDialog, pause_msg_menu.purge);
		lv_obj_align(labelDialog, NULL, LV_ALIGN_CENTER, 0, -20);
	}
	else if(DialogType == DIALOG_PAUSE_MESSAGE_RESUME)
	{
		lv_label_set_text(labelDialog, pause_msg_menu.resume);
		lv_obj_align(labelDialog, NULL, LV_ALIGN_CENTER, 0, -20);
	}
	else if(DialogType == DIALOG_PAUSE_MESSAGE_HEAT)
	{
		lv_label_set_text(labelDialog, pause_msg_menu.heat);
		lv_obj_align(labelDialog, NULL, LV_ALIGN_CENTER, 0, -20);
	}
	else if(DialogType == DIALOG_PAUSE_MESSAGE_HEATING)
	{
		lv_label_set_text(labelDialog, pause_msg_menu.heating);
		lv_obj_align(labelDialog, NULL, LV_ALIGN_CENTER, 0, -20);
	}
	else if(DialogType == DIALOG_PAUSE_MESSAGE_OPTION)
	{
		lv_label_set_text(labelDialog, pause_msg_menu.option);
		lv_obj_align(labelDialog, NULL, LV_ALIGN_CENTER, 0, -20);
	}
	else if(DialogType == DIALOG_TYPE_FILAMENT_NO_PRESS)
	{
		lv_label_set_text(labelDialog, print_file_dialog_menu.filament_no_press);
		lv_obj_align(labelDialog, NULL, LV_ALIGN_CENTER, 0, -20);
	}
	else if(DialogType == DIALOG_REVERT_EEPROM_TIPS)
	{
		lv_label_set_text(labelDialog, set_menu.revertTips);
		lv_obj_align(labelDialog, NULL, LV_ALIGN_CENTER, 0, -20);
	}
	else if (DialogType == DIALOG_TYPE_FILAMENT_LOAD_HEAT)
	{
		lv_label_set_text(labelDialog, filament_menu.filament_dialog_load_heat);
		lv_obj_align(labelDialog, NULL, LV_ALIGN_CENTER, 0, -20);
	}
	else if (DialogType == DIALOG_TYPE_FILAMENT_HEAT_LOAD_COMPLETED)
	{
		lv_label_set_text(labelDialog, filament_menu.filament_dialog_load_heat_confirm);
		lv_obj_align(labelDialog, NULL, LV_ALIGN_CENTER, 0, -20);
	}
	else if (DialogType == DIALOG_TYPE_FILAMENT_UNLOAD_HEAT)
	{
		lv_label_set_text(labelDialog, filament_menu.filament_dialog_unload_heat);
		lv_obj_align(labelDialog, NULL, LV_ALIGN_CENTER, 0, -20);
	}
	else if (DialogType == DIALOG_TYPE_FILAMENT_HEAT_UNLOAD_COMPLETED)
	{
		lv_label_set_text(labelDialog, filament_menu.filament_dialog_unload_heat_confirm);
		lv_obj_align(labelDialog, NULL, LV_ALIGN_CENTER, 0, -20);
	}
	else if (DialogType == DIALOG_TYPE_FILAMENT_LOAD_COMPLETED)
	{
		lv_label_set_text(labelDialog, filament_menu.filament_dialog_load_completed);
		lv_obj_align(labelDialog, NULL, LV_ALIGN_CENTER, 0, -20);
	}
	else if (DialogType == DIALOG_TYPE_FILAMENT_UNLOAD_COMPLETED)
	{
		lv_label_set_text(labelDialog, filament_menu.filament_dialog_unload_completed);
		lv_obj_align(labelDialog, NULL, LV_ALIGN_CENTER, 0, -20);
	}
	else if (DialogType == DIALOG_TYPE_FILAMENT_LOADING)
	{
		lv_label_set_text(labelDialog, filament_menu.filament_dialog_loading);
		lv_obj_align(labelDialog, NULL, LV_ALIGN_CENTER, 0, -70);
	}
	else if (DialogType == DIALOG_TYPE_FILAMENT_UNLOADING)
	{
		lv_label_set_text(labelDialog, filament_menu.filament_dialog_unloading);
		lv_obj_align(labelDialog, NULL, LV_ALIGN_CENTER, 0, -70);
	}
}

void filament_sprayer_temp()
{
    char buf[20] = {0};
    public_buf_l[0] = '\0';

    if (uiCfg.curSprayerChoose < 1)
    strcat(public_buf_l, preheat_menu.ext1);
    else
    strcat(public_buf_l, preheat_menu.ext2);
    sprintf(buf, preheat_menu.value_state, (int)thermalManager.temp_hotend[uiCfg.curSprayerChoose].celsius,  (int)thermalManager.temp_hotend[uiCfg.curSprayerChoose].target);

    strcat_P(public_buf_l, PSTR(": "));
    strcat(public_buf_l, buf);
    lv_label_set_text(tempText1, public_buf_l);
    lv_obj_align(tempText1, NULL, LV_ALIGN_CENTER, 0, -50);
}

void filament_dialog_handle()
{
	if((temperature_change_frequency == 1)
		&& ((DialogType == DIALOG_TYPE_FILAMENT_LOAD_HEAT)
		|| (DialogType  == DIALOG_TYPE_FILAMENT_UNLOAD_HEAT)))
	{
		filament_sprayer_temp();
		temperature_change_frequency = 0;
	}

	if (uiCfg.filament_heat_completed_load == 1)
	{
		uiCfg.filament_heat_completed_load = 0;
		lv_clear_dialog();
		lv_draw_dialog(DIALOG_TYPE_FILAMENT_LOADING);
		planner.synchronize();
		uiCfg.filament_loading_time_flg = 1;
		uiCfg.filament_loading_time_cnt = 0;
		ZERO(public_buf_m);
		sprintf_P(public_buf_m, PSTR("T%d\nG91\nG1 E%d F%d\nG90"), (int)uiCfg.curSprayerChoose, (int)gCfgItems.filamentchange_load_length, (int)gCfgItems.filamentchange_load_speed);
		queue.inject_P(PSTR(public_buf_m));
    	//gcode.process_subcommands_now_P(PSTR(public_buf_m));
	}

	if (uiCfg.filament_heat_completed_unload == 1)
	{
		uiCfg.filament_heat_completed_unload = 0;
		lv_clear_dialog();
		lv_draw_dialog(DIALOG_TYPE_FILAMENT_UNLOADING);
		planner.synchronize();
		uiCfg.filament_unloading_time_flg = 1;
		uiCfg.filament_unloading_time_cnt = 0;
		ZERO(public_buf_m);
		sprintf_P(public_buf_m, PSTR("T%d\nG91\nG1 E-%d F%d\nG90"), (int)uiCfg.curSprayerChoose, (int)gCfgItems.filamentchange_unload_length, (int)gCfgItems.filamentchange_unload_speed);
		queue.inject_P(PSTR(public_buf_m));
	}
	
	if (((abs((int)((int)thermalManager.temp_hotend[uiCfg.curSprayerChoose].celsius - gCfgItems.filament_limit_temper)) <= 1)
		|| ((int)thermalManager.temp_hotend[uiCfg.curSprayerChoose].celsius > gCfgItems.filament_limit_temper))
		&& (uiCfg.filament_load_heat_flg == 1))
	{
		uiCfg.filament_load_heat_flg = 0;
		lv_clear_dialog();
		lv_draw_dialog(DIALOG_TYPE_FILAMENT_HEAT_LOAD_COMPLETED);				
	}
	
	if (uiCfg.filament_loading_completed == 1)
	{
		uiCfg.filament_rate = 0;
		uiCfg.filament_loading_completed = 0;
		lv_clear_dialog();
		lv_draw_dialog(DIALOG_TYPE_FILAMENT_LOAD_COMPLETED);
	}

	if (((abs((int)((int)thermalManager.temp_hotend[uiCfg.curSprayerChoose].celsius - gCfgItems.filament_limit_temper)) <= 1)
		 || ((int)thermalManager.temp_hotend[uiCfg.curSprayerChoose].celsius > gCfgItems.filament_limit_temper))
		 && (uiCfg.filament_unload_heat_flg == 1))
	{
		uiCfg.filament_unload_heat_flg = 0;
		lv_clear_dialog();
		lv_draw_dialog(DIALOG_TYPE_FILAMENT_HEAT_UNLOAD_COMPLETED);				
	}
	
	if (uiCfg.filament_unloading_completed == 1)
	{
		uiCfg.filament_rate = 0;
		uiCfg.filament_unloading_completed = 0;
		lv_clear_dialog();
		lv_draw_dialog(DIALOG_TYPE_FILAMENT_UNLOAD_COMPLETED);
	}

	if ((DialogType == DIALOG_TYPE_FILAMENT_LOADING)
	   || (DialogType == DIALOG_TYPE_FILAMENT_UNLOADING))
	{
		lv_filament_setbar();
	}
}

void lv_filament_setbar()
{
	lv_bar_set_value(filament_bar, uiCfg.filament_rate, LV_ANIM_ON);
}

void lv_clear_dialog(void)
{
	lv_obj_del(scr);
}

#endif
