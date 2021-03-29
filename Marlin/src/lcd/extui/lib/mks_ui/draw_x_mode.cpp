#include "../../../../MarlinCore.h"
#if ENABLED(TFT_LITTLE_VGL_UI)
#include "draw_ui.h"
#include "../../../../gcode/queue.h"
#include "../../../../gcode/gcode.h"
#if ENABLED(DUAL_X_CARRIAGE)
#include "../../../../module/motion.h"


#define ID_X_MODE_FULL						1
#define ID_X_MODE_FULL_ARROW				2
#define ID_X_MODE_AUTO						3
#define ID_X_MODE_AUTO_ARROW				4
#define ID_X_MODE_DUPLICATION				5
#define ID_X_MODE_DUPLICATION_ARROW			6
#define ID_X_MODE_MIRROR					7
#define ID_X_MODE_MIRROR_ARROW				8
#define ID_X_MODE_RETURN					9

static lv_obj_t *scr;
static lv_obj_t *labelFullControl, *labelAutoPark, *labelDupli, *labelMirror;
static lv_obj_t *buttonFullControl, *buttonAutoPark, *buttonDupli, *buttonMirror;

static void event_handler(lv_obj_t * obj, lv_event_t event)
{
	switch(obj->mks_obj_id)
	{
		case ID_X_MODE_RETURN:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				lv_clear_x_mode();
				draw_return_ui();
			}
			break;
		case ID_X_MODE_FULL:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				//lv_clear_x_mode();
				//draw_return_ui();
				gcode.process_subcommands_now_P(PSTR("M605 S0"));
				gcode.process_subcommands_now_P(PSTR("M500"));
				queue.inject_P(PSTR("G28"));
				lv_btn_set_style(buttonFullControl, LV_BTN_STYLE_REL, &tft_style_label_sel_rel);
				lv_btn_set_style(buttonAutoPark, LV_BTN_STYLE_REL, &tft_style_label_rel);
				lv_btn_set_style(buttonDupli, LV_BTN_STYLE_REL, &tft_style_label_rel);
				lv_btn_set_style(buttonMirror, LV_BTN_STYLE_REL, &tft_style_label_rel);
				gCfgItems.dual_x_mode = REPRINT_FULL_CONTROL;
				update_spi_flash();
			}
			break;
		case ID_X_MODE_AUTO:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				//lv_clear_x_mode();
				//draw_return_ui();
				gcode.process_subcommands_now_P(PSTR("M605 S1"));
				gcode.process_subcommands_now_P(PSTR("M500"));
				queue.inject_P(PSTR("G28"));
				lv_btn_set_style(buttonFullControl, LV_BTN_STYLE_REL, &tft_style_label_rel);
				lv_btn_set_style(buttonAutoPark, LV_BTN_STYLE_REL, &tft_style_label_sel_rel);
				lv_btn_set_style(buttonDupli, LV_BTN_STYLE_REL, &tft_style_label_rel);
				lv_btn_set_style(buttonMirror, LV_BTN_STYLE_REL, &tft_style_label_rel);
				gCfgItems.dual_x_mode = REPRINT_AUTO_PARK;
				update_spi_flash();
			}
			break;
		case ID_X_MODE_DUPLICATION:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				//lv_clear_x_mode();
				//draw_return_ui();
				gcode.process_subcommands_now_P(PSTR("M605 S2"));
				gcode.process_subcommands_now_P(PSTR("M500"));
				queue.inject_P(PSTR("G28"));
				lv_btn_set_style(buttonFullControl, LV_BTN_STYLE_REL, &tft_style_label_rel);
				lv_btn_set_style(buttonAutoPark, LV_BTN_STYLE_REL, &tft_style_label_rel);
				lv_btn_set_style(buttonDupli, LV_BTN_STYLE_REL, &tft_style_label_sel_rel);
				lv_btn_set_style(buttonMirror, LV_BTN_STYLE_REL, &tft_style_label_rel);
				gCfgItems.dual_x_mode = REPRINT_DUPLICATION;
				update_spi_flash();
			}
			break;
		case ID_X_MODE_MIRROR:
			if(event == LV_EVENT_CLICKED) {

			}
			else if(event == LV_EVENT_RELEASED) {
				//lv_clear_x_mode();
				//draw_return_ui();
				gcode.process_subcommands_now_P(PSTR("M605 S2"));
				gcode.process_subcommands_now_P(PSTR("M605 S3"));
				gcode.process_subcommands_now_P(PSTR("M500"));
				queue.inject_P(PSTR("G28"));
				lv_btn_set_style(buttonFullControl, LV_BTN_STYLE_REL, &tft_style_label_rel);
				lv_btn_set_style(buttonAutoPark, LV_BTN_STYLE_REL, &tft_style_label_rel);
				lv_btn_set_style(buttonDupli, LV_BTN_STYLE_REL, &tft_style_label_rel);
				lv_btn_set_style(buttonMirror, LV_BTN_STYLE_REL, &tft_style_label_sel_rel);
				gCfgItems.dual_x_mode = REPRINT_MIRROR;
				update_spi_flash();
			}
			break;
	}
}

void lv_draw_x_mode(void)
{
	lv_obj_t *buttonBack,*label_Back;
	lv_obj_t *buttonFullControlNarrow;
	lv_obj_t *buttonAutoParkNarrow;
	lv_obj_t *buttonDupliNarrow;
	lv_obj_t *buttonMirrorNarrow;
	lv_obj_t *line1, *line2, *line3, *line4;

	if(disp_state_stack._disp_state[disp_state_stack._disp_index] != X_MODE_UI)
	{
		disp_state_stack._disp_index++;
		disp_state_stack._disp_state[disp_state_stack._disp_index] = X_MODE_UI;
	}
	disp_state = X_MODE_UI;

	scr = lv_obj_create(NULL, NULL);
	
	lv_obj_set_style(scr, &tft_style_scr);
  	lv_scr_load(scr);
  	lv_obj_clean(scr);

  	lv_obj_t *title = lv_label_create(scr, NULL);
	lv_obj_set_style(title, &tft_style_label_rel);
	lv_obj_set_pos(title, TITLE_XPOS, TITLE_YPOS);
	lv_label_set_text(title, creat_title_text());
  
  	lv_refr_now(lv_refr_get_disp_refreshing());
	
	LV_IMG_DECLARE(bmp_para_back);
	LV_IMG_DECLARE(bmp_para_arrow);

	buttonFullControl = lv_btn_create(scr, NULL);     											/*Add a button the current screen*/
	lv_obj_set_pos(buttonFullControl, PARA_UI_POS_X, PARA_UI_POS_Y);                            /*Set its position*/
	lv_obj_set_size(buttonFullControl, PARA_UI_SIZE_X, PARA_UI_SIZE_Y);                         /*Set its size*/
	lv_obj_set_event_cb_mks(buttonFullControl, event_handler, ID_X_MODE_FULL, NULL, 0);
	lv_btn_set_style(buttonFullControl, LV_BTN_STYLE_REL, &tft_style_label_rel);    			/*Set the button's released style*/
	lv_btn_set_style(buttonFullControl, LV_BTN_STYLE_PR, &tft_style_label_sel_pre);      		/*Set the button's pressed style*/
	lv_btn_set_layout(buttonFullControl, LV_LAYOUT_OFF);
	labelFullControl = lv_label_create(buttonFullControl, NULL);          						/*Add a label to the button*/

	buttonFullControlNarrow = lv_imgbtn_create(scr, NULL);
	lv_obj_set_pos(buttonFullControlNarrow, PARA_UI_POS_X+PARA_UI_SIZE_X, PARA_UI_POS_Y+PARA_UI_ARROW_V);
	lv_obj_set_event_cb_mks(buttonFullControlNarrow, event_handler, ID_X_MODE_FULL_ARROW, "bmp_arrow.bin", 0);	
    lv_imgbtn_set_src(buttonFullControlNarrow, LV_BTN_STATE_REL, &bmp_para_arrow);
    lv_imgbtn_set_src(buttonFullControlNarrow, LV_BTN_STATE_PR, &bmp_para_arrow);	
	lv_imgbtn_set_style(buttonFullControlNarrow, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonFullControlNarrow, LV_BTN_STATE_REL, &tft_style_label_rel);
	lv_btn_set_layout(buttonFullControlNarrow, LV_LAYOUT_OFF);

	line1 = lv_line_create(scr, NULL);
	lv_ex_line(line1, line_points[0]);

	buttonAutoPark = lv_btn_create(scr, NULL);     												/*Add a button the current screen*/
	lv_obj_set_pos(buttonAutoPark, PARA_UI_POS_X, PARA_UI_POS_Y*2);                            	/*Set its position*/
	lv_obj_set_size(buttonAutoPark, PARA_UI_SIZE_X, PARA_UI_SIZE_Y);                          	/*Set its size*/
	lv_obj_set_event_cb_mks(buttonAutoPark, event_handler, ID_X_MODE_AUTO, NULL, 0);
	lv_btn_set_style(buttonAutoPark, LV_BTN_STYLE_REL, &tft_style_label_rel);    				/*Set the button's released style*/
	lv_btn_set_style(buttonAutoPark, LV_BTN_STYLE_PR, &tft_style_label_sel_pre);      			/*Set the button's pressed style*/
	lv_btn_set_layout(buttonAutoPark, LV_LAYOUT_OFF);
	labelAutoPark = lv_label_create(buttonAutoPark, NULL);          							/*Add a label to the button*/

	buttonAutoParkNarrow = lv_imgbtn_create(scr, NULL);
	lv_obj_set_pos(buttonAutoParkNarrow, PARA_UI_POS_X+PARA_UI_SIZE_X, PARA_UI_POS_Y*2+PARA_UI_ARROW_V);
	lv_obj_set_event_cb_mks(buttonAutoParkNarrow, event_handler, ID_X_MODE_AUTO_ARROW, "bmp_arrow.bin", 0);	
    lv_imgbtn_set_src(buttonAutoParkNarrow, LV_BTN_STATE_REL, &bmp_para_arrow);
    lv_imgbtn_set_src(buttonAutoParkNarrow, LV_BTN_STATE_PR, &bmp_para_arrow);	
	lv_imgbtn_set_style(buttonAutoParkNarrow, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonAutoParkNarrow, LV_BTN_STATE_REL, &tft_style_label_rel);
	lv_btn_set_layout(buttonAutoParkNarrow, LV_LAYOUT_OFF);

	line2 = lv_line_create(scr, NULL);
	lv_ex_line(line2, line_points[1]);

	buttonDupli = lv_btn_create(scr, NULL);     												/*Add a button the current screen*/
	lv_obj_set_pos(buttonDupli, PARA_UI_POS_X, PARA_UI_POS_Y*3);                            	/*Set its position*/
	lv_obj_set_size(buttonDupli, PARA_UI_SIZE_X, PARA_UI_SIZE_Y);                          		/*Set its size*/
	lv_obj_set_event_cb_mks(buttonDupli, event_handler, ID_X_MODE_DUPLICATION, NULL, 0);
	lv_btn_set_style(buttonDupli, LV_BTN_STYLE_REL, &tft_style_label_rel);    					/*Set the button's released style*/
	lv_btn_set_style(buttonDupli, LV_BTN_STYLE_PR, &tft_style_label_sel_pre);      				/*Set the button's pressed style*/
	lv_btn_set_layout(buttonDupli, LV_LAYOUT_OFF);
	labelDupli = lv_label_create(buttonDupli, NULL);          									/*Add a label to the button*/
	
	buttonDupliNarrow = lv_imgbtn_create(scr, NULL);
	lv_obj_set_pos(buttonDupliNarrow, PARA_UI_POS_X+PARA_UI_SIZE_X, PARA_UI_POS_Y*3+PARA_UI_ARROW_V);
	lv_obj_set_event_cb_mks(buttonDupliNarrow, event_handler, ID_X_MODE_DUPLICATION_ARROW, "bmp_arrow.bin", 0);	
    lv_imgbtn_set_src(buttonDupliNarrow, LV_BTN_STATE_REL, &bmp_para_arrow);
    lv_imgbtn_set_src(buttonDupliNarrow, LV_BTN_STATE_PR, &bmp_para_arrow);	
	lv_imgbtn_set_style(buttonDupliNarrow, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonDupliNarrow, LV_BTN_STATE_REL, &tft_style_label_rel);
	lv_btn_set_layout(buttonDupliNarrow, LV_LAYOUT_OFF);

	line3 = lv_line_create(scr, NULL);
	lv_ex_line(line3, line_points[2]);
	
	buttonMirror = lv_btn_create(scr, NULL);     												/*Add a button the current screen*/
	lv_obj_set_pos(buttonMirror, PARA_UI_POS_X, PARA_UI_POS_Y*4);                            	/*Set its position*/
	lv_obj_set_size(buttonMirror, PARA_UI_SIZE_X, PARA_UI_SIZE_Y);                          	/*Set its size*/
	lv_obj_set_event_cb_mks(buttonMirror, event_handler, ID_X_MODE_MIRROR, NULL, 0);
	lv_btn_set_style(buttonMirror, LV_BTN_STYLE_REL, &tft_style_label_rel);    					/*Set the button's released style*/
	lv_btn_set_style(buttonMirror, LV_BTN_STYLE_PR, &tft_style_label_sel_pre);      			/*Set the button's pressed style*/
	lv_btn_set_layout(buttonMirror, LV_LAYOUT_OFF);
	labelMirror = lv_label_create(buttonMirror, NULL);          								/*Add a label to the button*/
	
	buttonMirrorNarrow = lv_imgbtn_create(scr, NULL);
	lv_obj_set_pos(buttonMirrorNarrow, PARA_UI_POS_X+PARA_UI_SIZE_X, PARA_UI_POS_Y*4+PARA_UI_ARROW_V);
	lv_obj_set_event_cb_mks(buttonMirrorNarrow, event_handler, ID_X_MODE_MIRROR_ARROW, "bmp_arrow.bin", 0);	
    lv_imgbtn_set_src(buttonMirrorNarrow, LV_BTN_STATE_REL, &bmp_para_arrow);
    lv_imgbtn_set_src(buttonMirrorNarrow, LV_BTN_STATE_PR, &bmp_para_arrow);	
	lv_imgbtn_set_style(buttonMirrorNarrow, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonMirrorNarrow, LV_BTN_STATE_REL, &tft_style_label_rel);
	lv_btn_set_layout(buttonMirrorNarrow, LV_LAYOUT_OFF);

	line4 = lv_line_create(scr, NULL);
	lv_ex_line(line4, line_points[3]);

	buttonBack = lv_imgbtn_create(scr, NULL);
	lv_obj_set_event_cb_mks(buttonBack, event_handler, ID_X_MODE_RETURN, "bmp_back70x40.bin", 0);	
    lv_imgbtn_set_src(buttonBack, LV_BTN_STATE_REL, &bmp_para_back);
    lv_imgbtn_set_src(buttonBack, LV_BTN_STATE_PR, &bmp_para_back);	
	lv_imgbtn_set_style(buttonBack, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonBack, LV_BTN_STATE_REL, &tft_style_label_rel);

	lv_obj_set_pos(buttonBack, PARA_UI_BACL_POS_X, PARA_UI_BACL_POS_Y);
	lv_btn_set_layout(buttonBack, LV_LAYOUT_OFF);
	label_Back = lv_label_create(buttonBack, NULL);
	
	if(gCfgItems.multiple_language !=0)
	{
		lv_label_set_text(label_Back, common_menu.text_back);
		lv_obj_align(label_Back, buttonBack, LV_ALIGN_CENTER, 0, 0);

		lv_label_set_text(labelFullControl, x_mode_menu.fullControl);
		lv_obj_align(labelFullControl, buttonFullControl, LV_ALIGN_IN_LEFT_MID, 0, 0);

		lv_label_set_text(labelAutoPark, x_mode_menu.autoPark);
		lv_obj_align(labelAutoPark, buttonAutoPark, LV_ALIGN_IN_LEFT_MID, 0, 0);

		lv_label_set_text(labelDupli, x_mode_menu.duplication);
		lv_obj_align(labelDupli, buttonDupli, LV_ALIGN_IN_LEFT_MID, 0, 0);

		lv_label_set_text(labelMirror, x_mode_menu.mirrored);
		lv_obj_align(labelMirror, buttonMirror, LV_ALIGN_IN_LEFT_MID, 0, 0);
	}

	switch (dual_x_carriage_mode)
	{
        case DXC_FULL_CONTROL_MODE:
			lv_btn_set_style(buttonFullControl, LV_BTN_STYLE_REL, &tft_style_label_sel_rel);
			break;
        case DXC_AUTO_PARK_MODE:
			lv_btn_set_style(buttonAutoPark, LV_BTN_STYLE_REL, &tft_style_label_sel_rel);
			break;
        case DXC_DUPLICATION_MODE:
         	lv_btn_set_style(buttonDupli, LV_BTN_STYLE_REL, &tft_style_label_sel_rel);
			break;
		case DXC_MIRRORED_MODE:
         	lv_btn_set_style(buttonMirror, LV_BTN_STYLE_REL, &tft_style_label_sel_rel);
          	break;
        default:
          	break;
    }
}

void lv_clear_x_mode()
{
	lv_obj_del(scr);
}
#endif
#endif
