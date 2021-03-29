#include "../../../../MarlinCore.h"
#if ENABLED(TFT_LITTLE_VGL_UI)
#include "draw_ui.h"


#define ID_O_PRE_HEAT		1
#define ID_O_EXTRUCT		2
#define ID_O_MOV			3
#define ID_O_FILAMENT		4
#define ID_O_SPEED			5
#define ID_O_FAN			6
#define ID_O_RETURN			8

static lv_obj_t *scr;

static void event_handler(lv_obj_t *obj, lv_event_t event)
{
	switch(obj->mks_obj_id)
	{
		case ID_O_PRE_HEAT:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				lv_clear_opration();
				lv_draw_preHeat();
			}
			break;
		case ID_O_EXTRUCT:
			if(event == LV_EVENT_CLICKED) {

			}
			else if(event == LV_EVENT_RELEASED) {
				lv_clear_opration();
				lv_draw_extrusion();
			}
			break;
		case ID_O_MOV:
			if(event == LV_EVENT_CLICKED) {

			}
			else if(event == LV_EVENT_RELEASED) {
				lv_clear_opration();
				lv_draw_move_motor();
			}
			break;
		case ID_O_FILAMENT:
			if(event == LV_EVENT_CLICKED) {

			}
			else if(event == LV_EVENT_RELEASED) {
				
			}
			break;
		case ID_O_FAN:
			if(event == LV_EVENT_CLICKED) {

			}
			else if(event == LV_EVENT_RELEASED) {
				lv_clear_opration();
				lv_draw_fan();
			}
			break;
		case ID_O_SPEED:
			if(event == LV_EVENT_CLICKED) {	
				
			}
			else if(event == LV_EVENT_RELEASED) {
				lv_clear_opration();
				lv_draw_change_speed();
			}
			break;
		case ID_O_RETURN:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				lv_clear_opration();
				draw_return_ui();
			}
			break;
	}
}

void lv_draw_opration(void)
{
	//lv_obj_t *buttonMove = NULL;
	//lv_obj_t *label_Move = NULL;

	if(disp_state_stack._disp_state[disp_state_stack._disp_index] != OPERATE_UI)
	{
		disp_state_stack._disp_index++;
		disp_state_stack._disp_state[disp_state_stack._disp_index] = OPERATE_UI;
	}
	disp_state = OPERATE_UI;

	scr = lv_obj_create(NULL, NULL);

	lv_obj_set_style(scr, &tft_style_scr);
  	lv_scr_load(scr);
  	lv_obj_clean(scr);

  	/*lv_obj_t *title = lv_label_create(scr, NULL);
	lv_obj_set_style(title, &tft_style_label_rel);
	lv_obj_set_pos(title, TITLE_XPOS, TITLE_YPOS);
	lv_label_set_text(title, creat_title_text());*/

  	lv_refr_now(lv_refr_get_disp_refreshing());

	LV_IMG_DECLARE(bmp_pic);

    /*Create an Image button*/
    lv_obj_t *buttonPreHeat = lv_imgbtn_create(scr, NULL);
	lv_obj_t *buttonFan = lv_imgbtn_create(scr, NULL);
	lv_obj_t *buttonSpeed = lv_imgbtn_create(scr, NULL);
	//if(uiCfg.print_state != WORKING)
	//	buttonMove = lv_imgbtn_create(scr, NULL);
	lv_obj_t *buttonBack = lv_imgbtn_create(scr, NULL);

	lv_obj_set_event_cb_mks(buttonPreHeat, event_handler, ID_O_PRE_HEAT, "bmp_OprPreHeat.bin", 0);
	lv_imgbtn_set_src(buttonPreHeat, LV_BTN_STATE_REL, &bmp_pic);
	lv_imgbtn_set_src(buttonPreHeat, LV_BTN_STATE_PR, &bmp_pic);
	lv_imgbtn_set_style(buttonPreHeat, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonPreHeat, LV_BTN_STATE_REL, &tft_style_label_rel);
	lv_obj_clear_protect(buttonPreHeat, LV_PROTECT_FOLLOW);

	lv_obj_set_event_cb_mks(buttonFan, event_handler, ID_O_FAN, "bmp_Fan.bin",0);	
    lv_imgbtn_set_src(buttonFan, LV_BTN_STATE_REL, &bmp_pic);
    lv_imgbtn_set_src(buttonFan, LV_BTN_STATE_PR, &bmp_pic);	
	lv_imgbtn_set_style(buttonFan, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonFan, LV_BTN_STATE_REL, &tft_style_label_rel);

	lv_obj_set_event_cb_mks(buttonSpeed, event_handler, ID_O_SPEED, "bmp_Speed.bin", 0);	
    lv_imgbtn_set_src(buttonSpeed, LV_BTN_STATE_REL, &bmp_pic);
    lv_imgbtn_set_src(buttonSpeed, LV_BTN_STATE_PR, &bmp_pic);	
	lv_imgbtn_set_style(buttonSpeed, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonSpeed, LV_BTN_STATE_REL, &tft_style_label_rel);

	/*if(uiCfg.print_state != WORKING)
	{
		lv_obj_set_event_cb_mks(buttonMove, event_handler, ID_O_MOV, "bmp_Mov.bin",0);	
	    lv_imgbtn_set_src(buttonMove, LV_BTN_STATE_REL, &bmp_pic);
	    lv_imgbtn_set_src(buttonMove, LV_BTN_STATE_PR, &bmp_pic);	
		lv_imgbtn_set_style(buttonMove, LV_BTN_STATE_PR, &tft_style_label_pre);
		lv_imgbtn_set_style(buttonMove, LV_BTN_STATE_REL, &tft_style_label_rel);
	}*/

	lv_obj_set_event_cb_mks(buttonBack, event_handler, ID_O_RETURN, "bmp_Return.bin",0);	
    lv_imgbtn_set_src(buttonBack, LV_BTN_STATE_REL, &bmp_pic);
    lv_imgbtn_set_src(buttonBack, LV_BTN_STATE_PR, &bmp_pic);	
	lv_imgbtn_set_style(buttonBack, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonBack, LV_BTN_STATE_REL, &tft_style_label_rel);

	lv_obj_set_pos(buttonPreHeat, INTERVAL_V, (TFT_HEIGHT-BTN_Y_PIXEL)/2);//titleHeight);
	lv_obj_set_pos(buttonFan, BTN_X_PIXEL+INTERVAL_V*2, (TFT_HEIGHT-BTN_Y_PIXEL)/2);//titleHeight);
	lv_obj_set_pos(buttonSpeed, BTN_X_PIXEL*2+INTERVAL_V*3, (TFT_HEIGHT-BTN_Y_PIXEL)/2);//titleHeight);
	/*if(uiCfg.print_state != WORKING)
	{
		lv_obj_set_pos(buttonMove, BTN_X_PIXEL*3+INTERVAL_V*4, titleHeight);
	}*/
	lv_obj_set_pos(buttonBack, BTN_X_PIXEL*3+INTERVAL_V*4, (TFT_HEIGHT-BTN_Y_PIXEL)/2);//BTN_Y_PIXEL+INTERVAL_H+titleHeight);

    /*Create a label on the Image button*/
	lv_btn_set_layout(buttonPreHeat, LV_LAYOUT_OFF);
	lv_btn_set_layout(buttonFan, LV_LAYOUT_OFF);
	lv_btn_set_layout(buttonSpeed, LV_LAYOUT_OFF);
	/*if(uiCfg.print_state != WORKING)
	{
		lv_btn_set_layout(buttonMove, LV_LAYOUT_OFF);
	}*/
	lv_btn_set_layout(buttonBack, LV_LAYOUT_OFF);

    lv_obj_t *labelPreHeat = lv_label_create(buttonPreHeat, NULL);
	lv_obj_t *label_Fan = lv_label_create(buttonFan, NULL);
	lv_obj_t *label_Speed = lv_label_create(buttonSpeed, NULL);
	/*if(uiCfg.print_state != WORKING)
	{
		label_Move = lv_label_create(buttonMove, NULL);
	}*/
	lv_obj_t *label_Back = lv_label_create(buttonBack, NULL);

	if(gCfgItems.multiple_language != 0)
	{
	    lv_label_set_text(labelPreHeat, operation_menu.temp);
		lv_obj_align(labelPreHeat, buttonPreHeat, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);

		lv_label_set_text(label_Fan, operation_menu.fan);
		lv_obj_align(label_Fan, buttonFan, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);

		lv_label_set_text(label_Speed, operation_menu.speed);
		lv_obj_align(label_Speed, buttonSpeed, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);

		/*if(uiCfg.print_state != WORKING)
		{
			lv_label_set_text(label_Move, operation_menu.move);
			lv_obj_align(label_Move, buttonMove, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);
		}*/

		lv_label_set_text(label_Back, common_menu.text_back);
		lv_obj_align(label_Back, buttonBack, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);
	}
}

void lv_clear_opration(void)
{
	lv_obj_del(scr);
}
#endif
