#include "../../../../MarlinCore.h"
#if ENABLED(TFT_LITTLE_VGL_UI)
#include "draw_ui.h"


#define ID_EEPROM_IN_LENGTH   		1
#define ID_EEPROM_IN_SPEED    		2
#define ID_EEPROM_OUT_LENGTH  		3
#define ID_EEPROM_OUT_SPEED   		4
#define ID_EEPROM_TEMP        		5
#define ID_EEPROM_REVERT			6
#define ID_EEPROM_REVERT_ARROW		7
#define ID_EEPROM_UP         		8
#define ID_EEPROM_DOWN        		9
#define ID_EEPROM_RETURN			10

static lv_obj_t *scr;

static void event_handler(lv_obj_t *obj, lv_event_t event)
{
	switch(obj->mks_obj_id)
	{
		case ID_EEPROM_TEMP:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				value = filament_temp;
        		clear_cur_ui();
       			lv_draw_number_key();
			}
			break;
		case ID_EEPROM_IN_SPEED:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				value = load_speed;
        		clear_cur_ui();
       			lv_draw_number_key();
			}
			break;
		case ID_EEPROM_IN_LENGTH:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				value = load_length;
        		clear_cur_ui();
       			lv_draw_number_key();
			}
			break;
		case ID_EEPROM_OUT_SPEED:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				value = unload_speed;
        		clear_cur_ui();
       			lv_draw_number_key();
			}
			break;
		case ID_EEPROM_OUT_LENGTH:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				value = unload_length;
        		clear_cur_ui();
       			lv_draw_number_key();
			}
			break;
		case ID_EEPROM_REVERT:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				clear_cur_ui();
				lv_draw_dialog(DIALOG_REVERT_EEPROM_TIPS);
			}
			break;
		case ID_EEPROM_REVERT_ARROW:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				clear_cur_ui();
				lv_draw_dialog(DIALOG_REVERT_EEPROM_TIPS);
			}
			break;
		case ID_EEPROM_UP:
			if (event == LV_EVENT_CLICKED) {

			}
			else if (event == LV_EVENT_RELEASED) {
				uiCfg.ui_page = 0;
				clear_cur_ui();
				lv_draw_eeprom_settings();
			}
			break;
		case ID_EEPROM_DOWN:
			if (event == LV_EVENT_CLICKED) {

			}
			else if (event == LV_EVENT_RELEASED) {
				uiCfg.ui_page = 1;
				clear_cur_ui();
				lv_draw_eeprom_settings();
			}
			break;
		case ID_EEPROM_RETURN:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				clear_cur_ui();
				draw_return_ui();
			}
			break;
	}
}

LV_IMG_DECLARE(bmp_para_bank);
LV_IMG_DECLARE(bmp_para_arrow);
LV_IMG_DECLARE(bmp_para_back);
void lv_draw_eeprom_settings(void)
{
	lv_obj_t *buttonRevert=NULL, *buttonRevertNarrow=NULL, *buttonBack=NULL;
	lv_obj_t *labelRevert=NULL, *label_Back=NULL, *buttonTurnPage=NULL, *labelTurnPage=NULL;
	lv_obj_t *line1=NULL, *line2=NULL, *line3=NULL, *line4=NULL;
	lv_obj_t *buttonTemperText=NULL, *buttonTemperValue=NULL, *labelTemperText=NULL, *labelTemperValue=NULL;
	lv_obj_t *buttonInSpeedText=NULL, *buttonInSpeedValue=NULL, *labelInSpeedText=NULL, *labelInSpeedValue=NULL;
	lv_obj_t *buttonInLengthText=NULL, *buttonInLengthValue=NULL, *labelInLengthText=NULL, *labelInLengthValue=NULL;
	lv_obj_t *buttonOutSpeedText=NULL, *buttonOutSpeedValue=NULL, *labelOutSpeedText=NULL, *labelOutSpeedValue=NULL;
	lv_obj_t *buttonOutLengthText=NULL, *buttonOutLengthValue=NULL, *labelOutLengthText=NULL, *labelOutLengthValue=NULL;


	if(disp_state_stack._disp_state[disp_state_stack._disp_index] != EEPROM_SETTINGS_UI)
	{
		disp_state_stack._disp_index++;
		disp_state_stack._disp_state[disp_state_stack._disp_index] = EEPROM_SETTINGS_UI;
	}
	disp_state = EEPROM_SETTINGS_UI;

	scr = lv_obj_create(NULL, NULL);
	
	lv_obj_set_style(scr, &tft_style_scr);
  	lv_scr_load(scr);
  	lv_obj_clean(scr);

  	lv_obj_t *title = lv_label_create(scr, NULL);
	lv_obj_set_style(title, &tft_style_label_rel);
	lv_obj_set_pos(title, TITLE_XPOS, TITLE_YPOS);
	lv_label_set_text(title, creat_title_text());
  
  	lv_refr_now(lv_refr_get_disp_refreshing());

	if (uiCfg.ui_page == 0)
	{
		buttonTemperText = lv_btn_create(scr, NULL);     													/*Add a button the current screen*/
		lv_obj_set_pos(buttonTemperText, PARA_UI_POS_X, PARA_UI_POS_Y);                           			/*Set its position*/
		lv_obj_set_size(buttonTemperText, PARA_UI_VALUE_SIZE_X, PARA_UI_SIZE_Y);                  			/*Set its size*/
		lv_obj_set_event_cb(buttonTemperText, event_handler); 
		lv_btn_set_style(buttonTemperText, LV_BTN_STYLE_REL, &tft_style_label_rel);    						/*Set the button's released style*/
		lv_btn_set_style(buttonTemperText, LV_BTN_STYLE_PR, &tft_style_label_pre);      					/*Set the button's pressed style*/
		lv_btn_set_layout(buttonTemperText, LV_LAYOUT_OFF);
		labelTemperText = lv_label_create(buttonTemperText, NULL);          								/*Add a label to the button*/
	
		buttonTemperValue = lv_imgbtn_create(scr, NULL);
		lv_obj_set_pos(buttonTemperValue, PARA_UI_VALUE_POS_X, PARA_UI_POS_Y+PARA_UI_VALUE_V);
		lv_obj_set_event_cb_mks(buttonTemperValue, event_handler, ID_EEPROM_TEMP, "bmp_Value_blank.bin", 0);	
		lv_imgbtn_set_src(buttonTemperValue, LV_BTN_STATE_REL, &bmp_para_bank);
		lv_imgbtn_set_src(buttonTemperValue, LV_BTN_STATE_PR, &bmp_para_bank);	
		lv_imgbtn_set_style(buttonTemperValue, LV_BTN_STATE_PR, &style_para_value_pre);
		lv_imgbtn_set_style(buttonTemperValue, LV_BTN_STATE_REL, &style_para_value_rel);
		lv_btn_set_layout(buttonTemperValue, LV_LAYOUT_OFF);
		labelTemperValue = lv_label_create(buttonTemperValue, NULL); 

		line1 = lv_line_create(scr, NULL);
		lv_ex_line(line1, line_points[0]);

		buttonInSpeedText = lv_btn_create(scr, NULL);     													/*Add a button the current screen*/
		lv_obj_set_pos(buttonInSpeedText, PARA_UI_POS_X, PARA_UI_POS_Y*2);                           		/*Set its position*/
		lv_obj_set_size(buttonInSpeedText, PARA_UI_VALUE_SIZE_X, PARA_UI_SIZE_Y);                  			/*Set its size*/
		lv_obj_set_event_cb(buttonInSpeedText, event_handler); 
		lv_btn_set_style(buttonInSpeedText, LV_BTN_STYLE_REL, &tft_style_label_rel);    					/*Set the button's released style*/
		lv_btn_set_style(buttonInSpeedText, LV_BTN_STYLE_PR, &tft_style_label_pre);      					/*Set the button's pressed style*/
		lv_btn_set_layout(buttonInSpeedText, LV_LAYOUT_OFF);
		labelInSpeedText = lv_label_create(buttonInSpeedText, NULL);          								/*Add a label to the button*/
	
		buttonInSpeedValue = lv_imgbtn_create(scr, NULL);
		lv_obj_set_pos(buttonInSpeedValue, PARA_UI_VALUE_POS_X, PARA_UI_POS_Y*2+PARA_UI_VALUE_V);
		lv_obj_set_event_cb_mks(buttonInSpeedValue, event_handler, ID_EEPROM_IN_SPEED, "bmp_Value_blank.bin", 0);	
		lv_imgbtn_set_src(buttonInSpeedValue, LV_BTN_STATE_REL, &bmp_para_bank);
		lv_imgbtn_set_src(buttonInSpeedValue, LV_BTN_STATE_PR, &bmp_para_bank);	
		lv_imgbtn_set_style(buttonInSpeedValue, LV_BTN_STATE_PR, &style_para_value_pre);
		lv_imgbtn_set_style(buttonInSpeedValue, LV_BTN_STATE_REL, &style_para_value_rel);
		lv_btn_set_layout(buttonInSpeedValue, LV_LAYOUT_OFF);
		labelInSpeedValue = lv_label_create(buttonInSpeedValue, NULL); 

		line2 = lv_line_create(scr, NULL);
		lv_ex_line(line2, line_points[1]);

		buttonInLengthText = lv_btn_create(scr, NULL);     													/*Add a button the current screen*/
		lv_obj_set_pos(buttonInLengthText, PARA_UI_POS_X, PARA_UI_POS_Y*3);                           		/*Set its position*/
		lv_obj_set_size(buttonInLengthText, PARA_UI_VALUE_SIZE_X, PARA_UI_SIZE_Y);                  		/*Set its size*/
		lv_obj_set_event_cb(buttonInLengthText, event_handler); 
		lv_btn_set_style(buttonInLengthText, LV_BTN_STYLE_REL, &tft_style_label_rel);    					/*Set the button's released style*/
		lv_btn_set_style(buttonInLengthText, LV_BTN_STYLE_PR, &tft_style_label_pre);      					/*Set the button's pressed style*/
		lv_btn_set_layout(buttonInLengthText, LV_LAYOUT_OFF);
		labelInLengthText = lv_label_create(buttonInLengthText, NULL);          							/*Add a label to the button*/
	
		buttonInLengthValue = lv_imgbtn_create(scr, NULL);
		lv_obj_set_pos(buttonInLengthValue, PARA_UI_VALUE_POS_X, PARA_UI_POS_Y*3+PARA_UI_VALUE_V);
		lv_obj_set_event_cb_mks(buttonInLengthValue, event_handler, ID_EEPROM_IN_LENGTH, "bmp_Value_blank.bin", 0);	
		lv_imgbtn_set_src(buttonInLengthValue, LV_BTN_STATE_REL, &bmp_para_bank);
		lv_imgbtn_set_src(buttonInLengthValue, LV_BTN_STATE_PR, &bmp_para_bank);	
		lv_imgbtn_set_style(buttonInLengthValue, LV_BTN_STATE_PR, &style_para_value_pre);
		lv_imgbtn_set_style(buttonInLengthValue, LV_BTN_STATE_REL, &style_para_value_rel);
		lv_btn_set_layout(buttonInLengthValue, LV_LAYOUT_OFF);
		labelInLengthValue = lv_label_create(buttonInLengthValue, NULL); 

		line3 = lv_line_create(scr, NULL);
		lv_ex_line(line3, line_points[2]);

		buttonOutSpeedText = lv_btn_create(scr, NULL);     													/*Add a button the current screen*/
		lv_obj_set_pos(buttonOutSpeedText, PARA_UI_POS_X, PARA_UI_POS_Y*4);                           		/*Set its position*/
		lv_obj_set_size(buttonOutSpeedText, PARA_UI_VALUE_SIZE_X, PARA_UI_SIZE_Y);                  		/*Set its size*/
		lv_obj_set_event_cb(buttonOutSpeedText, event_handler); 
		lv_btn_set_style(buttonOutSpeedText, LV_BTN_STYLE_REL, &tft_style_label_rel);    					/*Set the button's released style*/
		lv_btn_set_style(buttonOutSpeedText, LV_BTN_STYLE_PR, &tft_style_label_pre);      					/*Set the button's pressed style*/
		lv_btn_set_layout(buttonOutSpeedText, LV_LAYOUT_OFF);
		labelOutSpeedText = lv_label_create(buttonOutSpeedText, NULL);          							/*Add a label to the button*/
	
		buttonOutSpeedValue = lv_imgbtn_create(scr, NULL);
		lv_obj_set_pos(buttonOutSpeedValue, PARA_UI_VALUE_POS_X, PARA_UI_POS_Y*4+PARA_UI_VALUE_V);
		lv_obj_set_event_cb_mks(buttonOutSpeedValue, event_handler, ID_EEPROM_OUT_SPEED, "bmp_Value_blank.bin", 0);	
		lv_imgbtn_set_src(buttonOutSpeedValue, LV_BTN_STATE_REL, &bmp_para_bank);
		lv_imgbtn_set_src(buttonOutSpeedValue, LV_BTN_STATE_PR, &bmp_para_bank);	
		lv_imgbtn_set_style(buttonOutSpeedValue, LV_BTN_STATE_PR, &style_para_value_pre);
		lv_imgbtn_set_style(buttonOutSpeedValue, LV_BTN_STATE_REL, &style_para_value_rel);
		lv_btn_set_layout(buttonOutSpeedValue, LV_LAYOUT_OFF);
		labelOutSpeedValue = lv_label_create(buttonOutSpeedValue, NULL); 

		line4 = lv_line_create(scr, NULL);
		lv_ex_line(line4, line_points[3]);

		buttonTurnPage = lv_imgbtn_create(scr, NULL);
		lv_obj_set_event_cb_mks(buttonTurnPage, event_handler, ID_EEPROM_DOWN, "bmp_back70x40.bin", 0);	
	}
	else
	{
		buttonOutLengthText = lv_btn_create(scr, NULL);     													/*Add a button the current screen*/
		lv_obj_set_pos(buttonOutLengthText, PARA_UI_POS_X, PARA_UI_POS_Y);                           		/*Set its position*/
		lv_obj_set_size(buttonOutLengthText, PARA_UI_VALUE_SIZE_X, PARA_UI_SIZE_Y);                  		/*Set its size*/
		lv_obj_set_event_cb(buttonOutLengthText, event_handler); 
		lv_btn_set_style(buttonOutLengthText, LV_BTN_STYLE_REL, &tft_style_label_rel);    					/*Set the button's released style*/
		lv_btn_set_style(buttonOutLengthText, LV_BTN_STYLE_PR, &tft_style_label_pre);      					/*Set the button's pressed style*/
		lv_btn_set_layout(buttonOutLengthText, LV_LAYOUT_OFF);
		labelOutLengthText = lv_label_create(buttonOutLengthText, NULL);          							/*Add a label to the button*/
	
		buttonOutLengthValue = lv_imgbtn_create(scr, NULL);
		lv_obj_set_pos(buttonOutLengthValue, PARA_UI_VALUE_POS_X, PARA_UI_POS_Y+PARA_UI_VALUE_V);
		lv_obj_set_event_cb_mks(buttonOutLengthValue, event_handler, ID_EEPROM_OUT_LENGTH, "bmp_Value_blank.bin", 0);	
		lv_imgbtn_set_src(buttonOutLengthValue, LV_BTN_STATE_REL, &bmp_para_bank);
		lv_imgbtn_set_src(buttonOutLengthValue, LV_BTN_STATE_PR, &bmp_para_bank);	
		lv_imgbtn_set_style(buttonOutLengthValue, LV_BTN_STATE_PR, &style_para_value_pre);
		lv_imgbtn_set_style(buttonOutLengthValue, LV_BTN_STATE_REL, &style_para_value_rel);
		lv_btn_set_layout(buttonOutLengthValue, LV_LAYOUT_OFF);
		labelOutLengthValue = lv_label_create(buttonOutLengthValue, NULL); 

		line1 = lv_line_create(scr, NULL);
		lv_ex_line(line1, line_points[0]);

		buttonRevert = lv_btn_create(scr, NULL);     														/*Add a button the current screen*/
		lv_obj_set_pos(buttonRevert, PARA_UI_POS_X, PARA_UI_POS_Y*2);                          				/*Set its position*/
		lv_obj_set_size(buttonRevert, PARA_UI_SIZE_X, PARA_UI_SIZE_Y);                       				/*Set its size*/
		lv_obj_set_event_cb_mks(buttonRevert, event_handler, ID_EEPROM_REVERT, NULL, 0);
		lv_btn_set_style(buttonRevert, LV_BTN_STYLE_REL, &tft_style_label_rel);    							/*Set the button's released style*/
		lv_btn_set_style(buttonRevert, LV_BTN_STYLE_PR, &tft_style_label_pre);      						/*Set the button's pressed style*/
		lv_btn_set_layout(buttonRevert, LV_LAYOUT_OFF);
		labelRevert = lv_label_create(buttonRevert, NULL);          										/*Add a label to the button*/
		
		buttonRevertNarrow = lv_imgbtn_create(scr, NULL);
		lv_obj_set_pos(buttonRevertNarrow, PARA_UI_POS_X+PARA_UI_SIZE_X, PARA_UI_POS_Y*2+PARA_UI_ARROW_V);
		lv_obj_set_event_cb_mks(buttonRevertNarrow, event_handler, ID_EEPROM_REVERT_ARROW, "bmp_arrow.bin", 0);	
		lv_imgbtn_set_src(buttonRevertNarrow, LV_BTN_STATE_REL, &bmp_para_arrow);
		lv_imgbtn_set_src(buttonRevertNarrow, LV_BTN_STATE_PR, &bmp_para_arrow);	
		lv_imgbtn_set_style(buttonRevertNarrow, LV_BTN_STATE_PR, &tft_style_label_pre);
		lv_imgbtn_set_style(buttonRevertNarrow, LV_BTN_STATE_REL, &tft_style_label_rel);
		lv_btn_set_layout(buttonRevertNarrow, LV_LAYOUT_OFF);

		line2 = lv_line_create(scr, NULL);
		lv_ex_line(line2, line_points[1]);

		buttonTurnPage = lv_imgbtn_create(scr, NULL);
		lv_obj_set_event_cb_mks(buttonTurnPage, event_handler, ID_EEPROM_UP, "bmp_back70x40.bin", 0);	
	}

	lv_imgbtn_set_src(buttonTurnPage, LV_BTN_STATE_REL, &bmp_para_back);
	lv_imgbtn_set_src(buttonTurnPage, LV_BTN_STATE_PR, &bmp_para_back);	
	lv_imgbtn_set_style(buttonTurnPage, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonTurnPage, LV_BTN_STATE_REL, &tft_style_label_rel);
	lv_obj_set_pos(buttonTurnPage, PARA_UI_TURN_PAGE_POS_X, PARA_UI_BACL_POS_Y);
	lv_btn_set_layout(buttonTurnPage, LV_LAYOUT_OFF);
	labelTurnPage = lv_label_create(buttonTurnPage, NULL);

	buttonBack = lv_imgbtn_create(scr, NULL);
	lv_obj_set_event_cb_mks(buttonBack, event_handler, ID_EEPROM_RETURN, "bmp_back70x40.bin", 0);	
	lv_imgbtn_set_src(buttonBack, LV_BTN_STATE_REL, &bmp_para_back);
	lv_imgbtn_set_src(buttonBack, LV_BTN_STATE_PR, &bmp_para_back);	
	lv_imgbtn_set_style(buttonBack, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonBack, LV_BTN_STATE_REL, &tft_style_label_rel);
	lv_obj_set_pos(buttonBack, PARA_UI_BACL_POS_X, PARA_UI_BACL_POS_Y);
	lv_btn_set_layout(buttonBack, LV_LAYOUT_OFF);
	label_Back = lv_label_create(buttonBack, NULL);
	
	if(gCfgItems.multiple_language != 0)
	{
		if (uiCfg.ui_page == 0)
		{
			ZERO(public_buf_l);
		    sprintf_P(public_buf_l, PSTR("%d"), (int)gCfgItems.filament_limit_temper);
      		lv_label_set_text(labelTemperValue, public_buf_l);
      		lv_obj_align(labelTemperValue, buttonTemperValue, LV_ALIGN_CENTER, 0, 0);

			lv_label_set_text(labelTemperText, filament_menu.FilamentTemperature);
			lv_obj_align(labelTemperText, buttonTemperText, LV_ALIGN_IN_LEFT_MID, 0, 0);

			ZERO(public_buf_l);
			sprintf_P(public_buf_l, PSTR("%d"), (int)gCfgItems.filamentchange_load_speed);
			lv_label_set_text(labelInSpeedValue, public_buf_l);
			lv_obj_align(labelInSpeedValue, buttonInSpeedValue, LV_ALIGN_CENTER, 0, 0);

			lv_label_set_text(labelInSpeedText, filament_menu.InSpeed);
			lv_obj_align(labelInSpeedText, buttonInSpeedText, LV_ALIGN_IN_LEFT_MID, 0, 0);

			ZERO(public_buf_l);
			sprintf_P(public_buf_l, PSTR("%d"), (int)gCfgItems.filamentchange_load_length);
			lv_label_set_text(labelInLengthValue, public_buf_l);
			lv_obj_align(labelInLengthValue, buttonInLengthValue, LV_ALIGN_CENTER, 0, 0);

			lv_label_set_text(labelInLengthText, filament_menu.InLength);
			lv_obj_align(labelInLengthText, buttonInLengthText, LV_ALIGN_IN_LEFT_MID, 0, 0);

			ZERO(public_buf_l);
			sprintf_P(public_buf_l, PSTR("%d"), (int)gCfgItems.filamentchange_unload_speed);
			lv_label_set_text(labelOutSpeedValue, public_buf_l);
			lv_obj_align(labelOutSpeedValue, buttonOutSpeedValue, LV_ALIGN_CENTER, 0, 0);

			lv_label_set_text(labelOutSpeedText, filament_menu.OutSpeed);
			lv_obj_align(labelOutSpeedText, buttonOutSpeedText, LV_ALIGN_IN_LEFT_MID, 0, 0);
						
			lv_label_set_text(labelTurnPage, common_menu.next);
			lv_obj_align(labelTurnPage, buttonTurnPage, LV_ALIGN_CENTER, 0, 0);
		}
		else
		{
			ZERO(public_buf_l);
			sprintf_P(public_buf_l, PSTR("%d"), (int)gCfgItems.filamentchange_unload_length);
			lv_label_set_text(labelOutLengthValue, public_buf_l);
			lv_obj_align(labelOutLengthValue, buttonOutLengthValue, LV_ALIGN_CENTER, 0, 0);

			lv_label_set_text(labelOutLengthText, filament_menu.OutLength);
			lv_obj_align(labelOutLengthText, buttonOutLengthText, LV_ALIGN_IN_LEFT_MID, 0, 0);

			lv_label_set_text(labelRevert, set_menu.revert);
			lv_obj_align(labelRevert, buttonRevert, LV_ALIGN_IN_LEFT_MID, 0, 0);

			lv_label_set_text(labelTurnPage, common_menu.previous);
			lv_obj_align(labelTurnPage, buttonTurnPage, LV_ALIGN_CENTER, 0, 0);
		}
		
		lv_label_set_text(label_Back, common_menu.text_back);
		lv_obj_align(label_Back, buttonBack, LV_ALIGN_CENTER, 0, 0);
	}
}

void lv_clear_eeprom_settings(void)
{
	lv_obj_del(scr);
}
#endif
