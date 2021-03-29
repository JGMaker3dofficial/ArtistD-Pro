#include "../../../../MarlinCore.h"
#if ENABLED(TFT_LITTLE_VGL_UI)
#include "draw_ui.h"
#include "../../../../gcode/queue.h"
#include "../../../../module/temperature.h"


#define ID_S_FAN				1
#define ID_S_LANGUAGE			2
#define ID_S_ABOUT				3
#define ID_S_EEPROM_SET			4
#define ID_S_TOOL_OFFSET		5
#define ID_S_MOTOR_SETTINGS		6
#define ID_S_FILAMENT_CHANGE	7
#define ID_S_RETURN				8

static lv_obj_t *scr;

static void event_handler(lv_obj_t *obj, lv_event_t event)
{
	switch(obj->mks_obj_id)
	{
		case ID_S_LANGUAGE:
			if(event == LV_EVENT_CLICKED) {

			}
			else if(event == LV_EVENT_RELEASED) {
				lv_clear_set();
				lv_draw_language();
			}
			break;
		case ID_S_FAN:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				lv_clear_set();
				lv_draw_fan();
			}
			break;
		case ID_S_ABOUT:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				lv_clear_set();
				lv_draw_about();
			}
			break;
		case ID_S_EEPROM_SET:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				uiCfg.ui_page = 0;
				lv_clear_set();
				lv_draw_eeprom_settings();
			}
			break;
		case ID_S_TOOL_OFFSET:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				lv_clear_set();
				lv_draw_tool_offset();
			}
			break;
		case ID_S_MOTOR_SETTINGS:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				lv_clear_set();
				lv_draw_motor_settings();
			}
			break;
		case ID_S_FILAMENT_CHANGE:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				uiCfg.desireSprayerTempBak = thermalManager.temp_hotend[uiCfg.curSprayerChoose].target;
				lv_clear_set();
				lv_draw_filament_change();
			}
			break;
		case ID_S_RETURN:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				lv_clear_set();
				lv_draw_ready_print(1);
			}
			break;
	}
}

void lv_draw_set(void)
{
	if(disp_state_stack._disp_state[disp_state_stack._disp_index] != SET_UI)
	{
		disp_state_stack._disp_index++;
		disp_state_stack._disp_state[disp_state_stack._disp_index] = SET_UI;
	}
	disp_state = SET_UI;

	scr = lv_obj_create(NULL, NULL);

	//static lv_style_t tool_style;
	
	lv_obj_set_style(scr, &tft_style_scr);
  	lv_scr_load(scr);
  	lv_obj_clean(scr);

  	lv_obj_t * title = lv_label_create(scr, NULL);
	lv_obj_set_style(title, &tft_style_label_rel);
	lv_obj_set_pos(title, TITLE_XPOS, TITLE_YPOS);
	lv_label_set_text(title, creat_title_text());
  
  	lv_refr_now(lv_refr_get_disp_refreshing());
	
	LV_IMG_DECLARE(bmp_pic);
	
    /*Create an Image button*/
	lv_obj_t *buttonLanguage = lv_imgbtn_create(scr, NULL);
	lv_obj_t *buttonFan = lv_imgbtn_create(scr, NULL);
	lv_obj_t *buttonAbout = lv_imgbtn_create(scr, NULL);
	lv_obj_t *buttonEepromSet = lv_imgbtn_create(scr, NULL);
	#if ENABLED(DUAL_X_CARRIAGE)
	lv_obj_t *buttonToffset = lv_imgbtn_create(scr, NULL);
	#endif
	lv_obj_t *buttonMotorSettings = lv_imgbtn_create(scr, NULL);
	lv_obj_t *buttonFilamentChange = lv_imgbtn_create(scr, NULL);
	lv_obj_t *buttonBack = lv_imgbtn_create(scr, NULL);

	lv_obj_set_event_cb_mks(buttonLanguage, event_handler, ID_S_LANGUAGE, "bmp_Language.bin", 0);	
    lv_imgbtn_set_src(buttonLanguage, LV_BTN_STATE_REL, &bmp_pic);
    lv_imgbtn_set_src(buttonLanguage, LV_BTN_STATE_PR, &bmp_pic);	
	lv_imgbtn_set_style(buttonLanguage, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonLanguage, LV_BTN_STATE_REL, &tft_style_label_rel);

	lv_obj_set_event_cb_mks(buttonFan, event_handler, ID_S_FAN, "bmp_Fan.bin", 0);
	lv_imgbtn_set_src(buttonFan, LV_BTN_STATE_REL, &bmp_pic);
	lv_imgbtn_set_src(buttonFan, LV_BTN_STATE_PR, &bmp_pic);
	lv_imgbtn_set_style(buttonFan, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonFan, LV_BTN_STATE_REL, &tft_style_label_rel);

	lv_obj_set_event_cb_mks(buttonAbout, event_handler, ID_S_ABOUT, "bmp_About.bin", 0);	
    lv_imgbtn_set_src(buttonAbout, LV_BTN_STATE_REL, &bmp_pic);
    lv_imgbtn_set_src(buttonAbout, LV_BTN_STATE_PR, &bmp_pic);	
	lv_imgbtn_set_style(buttonAbout, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonAbout, LV_BTN_STATE_REL, &tft_style_label_rel);

	lv_obj_set_event_cb_mks(buttonEepromSet, event_handler, ID_S_EEPROM_SET, "bmp_Eeprom_settings.bin", 0);	
    lv_imgbtn_set_src(buttonEepromSet, LV_BTN_STATE_REL, &bmp_pic);
   	lv_imgbtn_set_src(buttonEepromSet, LV_BTN_STATE_PR, &bmp_pic);	
	lv_imgbtn_set_style(buttonEepromSet, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonEepromSet, LV_BTN_STATE_REL, &tft_style_label_rel);

	#if ENABLED(DUAL_X_CARRIAGE)
	lv_obj_set_event_cb_mks(buttonToffset, event_handler, ID_S_TOOL_OFFSET, "bmp_T_offset.bin", 0);	
    lv_imgbtn_set_src(buttonToffset, LV_BTN_STATE_REL, &bmp_pic);
    lv_imgbtn_set_src(buttonToffset, LV_BTN_STATE_PR, &bmp_pic);	
	lv_imgbtn_set_style(buttonToffset, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonToffset, LV_BTN_STATE_REL, &tft_style_label_rel);
	#endif

	lv_obj_set_event_cb_mks(buttonMotorSettings, event_handler, ID_S_MOTOR_SETTINGS, "bmp_Motor_settings.bin", 0);	
    lv_imgbtn_set_src(buttonMotorSettings, LV_BTN_STATE_REL, &bmp_pic);
	lv_imgbtn_set_src(buttonMotorSettings, LV_BTN_STATE_PR, &bmp_pic);	
	lv_imgbtn_set_style(buttonMotorSettings, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonMotorSettings, LV_BTN_STATE_REL, &tft_style_label_rel);

	lv_obj_set_event_cb_mks(buttonFilamentChange, event_handler, ID_S_FILAMENT_CHANGE, "bmp_Filamentchange.bin", 0);	
    lv_imgbtn_set_src(buttonFilamentChange, LV_BTN_STATE_REL, &bmp_pic);
	lv_imgbtn_set_src(buttonFilamentChange, LV_BTN_STATE_PR, &bmp_pic);	
	lv_imgbtn_set_style(buttonFilamentChange, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonFilamentChange, LV_BTN_STATE_REL, &tft_style_label_rel);

	lv_obj_set_event_cb_mks(buttonBack, event_handler, ID_S_RETURN, "bmp_Return.bin", 0);	
    lv_imgbtn_set_src(buttonBack, LV_BTN_STATE_REL, &bmp_pic);
    lv_imgbtn_set_src(buttonBack, LV_BTN_STATE_PR, &bmp_pic);	
	lv_imgbtn_set_style(buttonBack, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonBack, LV_BTN_STATE_REL, &tft_style_label_rel);
	
	lv_obj_set_pos(buttonLanguage, INTERVAL_V, titleHeight);
	lv_obj_set_pos(buttonFan, BTN_X_PIXEL+INTERVAL_V*2, titleHeight);
	lv_obj_set_pos(buttonFilamentChange, BTN_X_PIXEL*2+INTERVAL_V*3, titleHeight);
	lv_obj_set_pos(buttonAbout, BTN_X_PIXEL*3+INTERVAL_V*4, titleHeight);
	#if ENABLED(DUAL_X_CARRIAGE)
	lv_obj_set_pos(buttonToffset, INTERVAL_V, BTN_Y_PIXEL+INTERVAL_H+titleHeight);
	#endif
	lv_obj_set_pos(buttonMotorSettings, BTN_X_PIXEL+INTERVAL_V*2, BTN_Y_PIXEL+INTERVAL_H+titleHeight);
	lv_obj_set_pos(buttonEepromSet, BTN_X_PIXEL*2+INTERVAL_V*3, BTN_Y_PIXEL+INTERVAL_H+titleHeight);
	lv_obj_set_pos(buttonBack, BTN_X_PIXEL*3+INTERVAL_V*4, BTN_Y_PIXEL+INTERVAL_H+titleHeight);

    /*Create a label on the Image button*/
	lv_btn_set_layout(buttonLanguage, LV_LAYOUT_OFF);
	lv_btn_set_layout(buttonFan, LV_LAYOUT_OFF);
	lv_btn_set_layout(buttonAbout, LV_LAYOUT_OFF);
	lv_btn_set_layout(buttonEepromSet, LV_LAYOUT_OFF);
	#if ENABLED(DUAL_X_CARRIAGE)
	lv_btn_set_layout(buttonToffset, LV_LAYOUT_OFF);
	#endif
	lv_btn_set_layout(buttonMotorSettings, LV_LAYOUT_OFF);
	lv_btn_set_layout(buttonFilamentChange, LV_LAYOUT_OFF);
	lv_btn_set_layout(buttonBack, LV_LAYOUT_OFF);
	
	lv_obj_t *label_Language = lv_label_create(buttonLanguage, NULL);
	lv_obj_t *labelFan = lv_label_create(buttonFan, NULL);
	lv_obj_t *label_About = lv_label_create(buttonAbout, NULL);
	lv_obj_t *label_EepromSet = lv_label_create(buttonEepromSet, NULL);
	#if ENABLED(DUAL_X_CARRIAGE)
	lv_obj_t *label_Toffset = lv_label_create(buttonToffset, NULL);
	#endif
	lv_obj_t *label_MotorSettings = lv_label_create(buttonMotorSettings, NULL);
	lv_obj_t *label_FilamentChange = lv_label_create(buttonFilamentChange, NULL);
	lv_obj_t *label_Back = lv_label_create(buttonBack, NULL);
	
	if(gCfgItems.multiple_language != 0)
	{
		lv_label_set_text(label_Language, set_menu.language);
		lv_obj_align(label_Language, buttonLanguage, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);

		lv_label_set_text(labelFan, set_menu.fan);
		lv_obj_align(labelFan, buttonFan, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);

		lv_label_set_text(label_About, set_menu.about);
		lv_obj_align(label_About, buttonAbout, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);
		
		lv_label_set_text(label_EepromSet, set_menu.eepromSet);
		lv_obj_align(label_EepromSet, buttonEepromSet, LV_ALIGN_IN_BOTTOM_MID,0, BUTTON_TEXT_Y_OFFSET);

		#if ENABLED(DUAL_X_CARRIAGE)
		lv_label_set_text(label_Toffset, set_menu.Toffset);
		lv_obj_align(label_Toffset, buttonToffset, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);
		#endif

		lv_label_set_text(label_MotorSettings, set_menu.motorsettings);
		lv_obj_align(label_MotorSettings, buttonMotorSettings, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);

		lv_label_set_text(label_FilamentChange, set_menu.filament);
		lv_obj_align(label_FilamentChange, buttonFilamentChange, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);

		lv_label_set_text(label_Back, common_menu.text_back);
		lv_obj_align(label_Back, buttonBack, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);
	}
}

void lv_clear_set(void)
{
	lv_obj_del(scr);
}

#endif
