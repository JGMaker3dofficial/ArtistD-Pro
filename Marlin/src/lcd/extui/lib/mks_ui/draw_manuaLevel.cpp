#include "../../../../MarlinCore.h"
#if ENABLED(TFT_LITTLE_VGL_UI)
#include "draw_ui.h"
#include "../../../../gcode/queue.h"


#define ID_M_POINT1			1
#define ID_M_POINT2			2
#define ID_M_POINT3			3
#define ID_M_POINT4			4
#define ID_M_POINT5			5
#define ID_M_X_TYPE			6
#define ID_M_OFF_XY			7
#define ID_MANUAL_RETURN	8

static lv_obj_t *scr;
static lv_obj_t *buttoType, *labelType;

static void event_handler(lv_obj_t *obj, lv_event_t event)
{
	switch(obj->mks_obj_id)
	{
		case ID_M_POINT1:
			if(event == LV_EVENT_CLICKED) {

			}
			else if(event == LV_EVENT_RELEASED) {
				if(queue.length == 0)
				{
					if(uiCfg.leveling_first_time)
					{
						queue.enqueue_one_P(PSTR("G28"));
						uiCfg.leveling_first_time = 0;
					}

					queue.enqueue_one_P(PSTR("G1 Z10"));
					
					memset(public_buf_l, 0, sizeof(public_buf_l));
					sprintf(public_buf_l, "G1 X%d Y%d F%d", MANUAL_LEVELING_POINT_X1, MANUAL_LEVELING_POINT_Y1, HOMING_FEEDRATE_XY);
					queue.enqueue_one_P(PSTR(public_buf_l));

					if(uiCfg.curSprayerLevel == 0)
					{
						queue.enqueue_one_P(PSTR("G28 Z"));
					}
					else
					{
						queue.enqueue_one_P(PSTR("G1 Z0"));
					}
				}
			}
			break;
		case ID_M_POINT2:
			if(event == LV_EVENT_CLICKED) {

			}
			else if(event == LV_EVENT_RELEASED) {
				if(queue.length == 0)
				{
					if(uiCfg.leveling_first_time)
					{
						queue.enqueue_one_P(PSTR("G28"));
						uiCfg.leveling_first_time = 0;
					}

					queue.enqueue_one_P(PSTR("G1 Z10"));
					
					memset(public_buf_l, 0, sizeof(public_buf_l));
					sprintf(public_buf_l, "G1 X%d Y%d F%d", MANUAL_LEVELING_POINT_X2, MANUAL_LEVELING_POINT_Y2, HOMING_FEEDRATE_XY);
					queue.enqueue_one_P(PSTR(public_buf_l));
					queue.enqueue_one_P(PSTR("G1 Z0"));
				}
			}
			break;
		case ID_M_POINT3:
			if(event == LV_EVENT_CLICKED) {

			}
			else if(event == LV_EVENT_RELEASED) {
			if(queue.length == 0)
				{
					if(uiCfg.leveling_first_time)
					{
						queue.enqueue_one_P(PSTR("G28"));
						uiCfg.leveling_first_time = 0;
					}

					queue.enqueue_one_P(PSTR("G1 Z10"));
					
					memset(public_buf_l, 0, sizeof(public_buf_l));
					sprintf(public_buf_l, "G1 X%d Y%d F%d", MANUAL_LEVELING_POINT_X3, MANUAL_LEVELING_POINT_Y3, HOMING_FEEDRATE_XY);
					queue.enqueue_one_P(PSTR(public_buf_l));
					queue.enqueue_one_P(PSTR("G1 Z0"));
				}
			}
			break;
		case ID_M_POINT4:
			if(event == LV_EVENT_CLICKED) {

			}
			else if(event == LV_EVENT_RELEASED) {
				if(queue.length == 0)
				{
					if(uiCfg.leveling_first_time)
					{
						queue.enqueue_one_P(PSTR("G28"));
						uiCfg.leveling_first_time = 0;
					}

					queue.enqueue_one_P(PSTR("G1 Z10"));
					
					memset(public_buf_l, 0, sizeof(public_buf_l));
					sprintf(public_buf_l, "G1 X%d Y%d F%d", MANUAL_LEVELING_POINT_X4, MANUAL_LEVELING_POINT_Y4, HOMING_FEEDRATE_XY);
					queue.enqueue_one_P(PSTR(public_buf_l));
					queue.enqueue_one_P(PSTR("G1 Z0"));
				}
			}
			break;
		case ID_M_POINT5:
			if(event == LV_EVENT_CLICKED) {

			}
			else if(event == LV_EVENT_RELEASED) {
				if(queue.length == 0)
				{
					if(uiCfg.leveling_first_time)
					{
						queue.enqueue_one_P(PSTR("G28"));
						uiCfg.leveling_first_time = 0;
					}

					queue.enqueue_one_P(PSTR("G1 Z10"));
					
					memset(public_buf_l, 0, sizeof(public_buf_l));
					sprintf(public_buf_l, "G1 X%d Y%d F%d", MANUAL_LEVELING_POINT_X5, MANUAL_LEVELING_POINT_Y5, HOMING_FEEDRATE_XY);
					queue.enqueue_one_P(PSTR(public_buf_l));
					queue.enqueue_one_P(PSTR("G1 Z0"));
				}
			}
			break;
		#if ENABLED(DUAL_X_CARRIAGE)
		case ID_M_X_TYPE:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				if(EXTRUDERS == 2)
				{
					if(uiCfg.curSprayerLevel == 0)
					{
						uiCfg.curSprayerLevel = 1;
					}
					else
					{
						uiCfg.curSprayerLevel = 0;
					}
				}
				else
				{
					uiCfg.curSprayerLevel = 0;
				}

				disp_level_type();
			}
			break;
		#endif
		case ID_M_OFF_XY:
			if(event == LV_EVENT_CLICKED) {

			}
			else if(event == LV_EVENT_RELEASED) {
				queue.inject_P(PSTR("M84 X Y"));
			}
			break;
		case ID_MANUAL_RETURN:
			if(event == LV_EVENT_CLICKED) {

			}
			else if(event == LV_EVENT_RELEASED) {
				lv_clear_manualLevel();
				lv_draw_ready_print(1);

				// 模式喷头切换回原来状态
				#if ENABLED(DUAL_X_CARRIAGE)
				switch(gCfgItems.dual_x_mode)
				{
					case REPRINT_FULL_CONTROL:
						queue.enqueue_one_P(PSTR("M605 S0"));
						break;
					case REPRINT_AUTO_PARK:
						queue.enqueue_one_P(PSTR("M605 S1"));
						break;
					case REPRINT_DUPLICATION:
						queue.enqueue_one_P(PSTR("M605 S2"));
						break;
					case REPRINT_MIRROR:
						queue.enqueue_one_P(PSTR("M605 S2"));
						queue.enqueue_one_P(PSTR("M605 S3"));
						break;
					default:
						break;
				}

				if(uiCfg.curSprayerLevel == 0)
				{
					queue.enqueue_one_P(PSTR("T0"));
				}
				else
				{
					queue.enqueue_one_P(PSTR("T1"));
				}

				queue.enqueue_one_P(PSTR("G28"));
				#endif
			}
			break;
	}
}

void lv_draw_manualLevel(void)
{
	if(disp_state_stack._disp_state[disp_state_stack._disp_index] != LEVELING_UI)
	{
		disp_state_stack._disp_index++;
		disp_state_stack._disp_state[disp_state_stack._disp_index] = LEVELING_UI;
	}
	disp_state = LEVELING_UI;

	scr = lv_obj_create(NULL, NULL);

	//static lv_style_t tool_style;
	
	lv_obj_set_style(scr, &tft_style_scr);
  	lv_scr_load(scr);
  	lv_obj_clean(scr);

  	lv_obj_t *title = lv_label_create(scr, NULL);
	lv_obj_set_style(title, &tft_style_label_rel);
	lv_obj_set_pos(title, TITLE_XPOS, TITLE_YPOS);
	lv_label_set_text(title, creat_title_text());
  
  	lv_refr_now(lv_refr_get_disp_refreshing());
	
	LV_IMG_DECLARE(bmp_pic);
	
    /*Create an Image button*/
    lv_obj_t *buttonPoint1 = lv_imgbtn_create(scr, NULL);
	lv_obj_t *buttonPoint2 = lv_imgbtn_create(scr, NULL);
	lv_obj_t *buttonPoint3 = lv_imgbtn_create(scr, NULL);
	lv_obj_t *buttonPoint4 = lv_imgbtn_create(scr, NULL);
	lv_obj_t *buttonPoint5 = lv_imgbtn_create(scr, NULL);
	buttoType = lv_imgbtn_create(scr, NULL);
	lv_obj_t *buttonOffXY = lv_imgbtn_create(scr, NULL);
	lv_obj_t *buttonBack = lv_imgbtn_create(scr, NULL);
	
	lv_obj_set_event_cb_mks(buttonPoint1, event_handler, ID_M_POINT1, "bmp_Leveling1.bin", 0);
	lv_imgbtn_set_src(buttonPoint1, LV_BTN_STATE_REL, &bmp_pic);
	lv_imgbtn_set_src(buttonPoint1, LV_BTN_STATE_PR, &bmp_pic);
	lv_imgbtn_set_style(buttonPoint1, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonPoint1, LV_BTN_STATE_REL, &tft_style_label_rel);
	lv_obj_clear_protect(buttonPoint1, LV_PROTECT_FOLLOW);

	lv_obj_set_event_cb_mks(buttonPoint2, event_handler, ID_M_POINT2, "bmp_Leveling5.bin", 0);
	lv_imgbtn_set_src(buttonPoint2, LV_BTN_STATE_REL, &bmp_pic);
	lv_imgbtn_set_src(buttonPoint2, LV_BTN_STATE_PR, &bmp_pic);
	lv_imgbtn_set_style(buttonPoint2, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonPoint2, LV_BTN_STATE_REL, &tft_style_label_rel);

	lv_obj_set_event_cb_mks(buttonPoint3, event_handler, ID_M_POINT3, "bmp_Leveling4.bin", 0);	
    lv_imgbtn_set_src(buttonPoint3, LV_BTN_STATE_REL, &bmp_pic);
    lv_imgbtn_set_src(buttonPoint3, LV_BTN_STATE_PR, &bmp_pic);	
	lv_imgbtn_set_style(buttonPoint3, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonPoint3, LV_BTN_STATE_REL, &tft_style_label_rel);

	lv_obj_set_event_cb_mks(buttonPoint4, event_handler, ID_M_POINT4, "bmp_Leveling3.bin", 0);	
    lv_imgbtn_set_src(buttonPoint4, LV_BTN_STATE_REL, &bmp_pic);
    lv_imgbtn_set_src(buttonPoint4, LV_BTN_STATE_PR, &bmp_pic);	
	lv_imgbtn_set_style(buttonPoint4, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonPoint4, LV_BTN_STATE_REL, &tft_style_label_rel);

	lv_obj_set_event_cb_mks(buttonPoint5, event_handler, ID_M_POINT5, "bmp_Leveling2.bin", 0);	
    lv_imgbtn_set_src(buttonPoint5, LV_BTN_STATE_REL, &bmp_pic);
    lv_imgbtn_set_src(buttonPoint5, LV_BTN_STATE_PR, &bmp_pic);	
	lv_imgbtn_set_style(buttonPoint5, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonPoint5, LV_BTN_STATE_REL, &tft_style_label_rel);

	lv_imgbtn_set_src(buttoType, LV_BTN_STATE_REL, &bmp_pic);
    lv_imgbtn_set_src(buttoType, LV_BTN_STATE_PR, &bmp_pic);	
	lv_imgbtn_set_style(buttoType, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttoType, LV_BTN_STATE_REL, &tft_style_label_rel);

	lv_obj_set_event_cb_mks(buttonOffXY, event_handler, ID_M_OFF_XY, "bmp_MotorXY_off_blue.bin", 0);	
    lv_imgbtn_set_src(buttonOffXY, LV_BTN_STATE_REL, &bmp_pic);
    lv_imgbtn_set_src(buttonOffXY, LV_BTN_STATE_PR, &bmp_pic);	
	lv_imgbtn_set_style(buttonOffXY, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonOffXY, LV_BTN_STATE_REL, &tft_style_label_rel);

	lv_obj_set_event_cb_mks(buttonBack, event_handler, ID_MANUAL_RETURN, "bmp_Return.bin", 0);	
    lv_imgbtn_set_src(buttonBack, LV_BTN_STATE_REL, &bmp_pic);
    lv_imgbtn_set_src(buttonBack, LV_BTN_STATE_PR, &bmp_pic);	
	lv_imgbtn_set_style(buttonBack, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonBack, LV_BTN_STATE_REL, &tft_style_label_rel);
	
	lv_obj_set_pos(buttonPoint1, INTERVAL_V, titleHeight);
	lv_obj_set_pos(buttonPoint2, BTN_X_PIXEL+INTERVAL_V*2, titleHeight);
	lv_obj_set_pos(buttonPoint3, BTN_X_PIXEL*2+INTERVAL_V*3, titleHeight);
	lv_obj_set_pos(buttonPoint4, BTN_X_PIXEL*3+INTERVAL_V*4, titleHeight);
	lv_obj_set_pos(buttonPoint5, INTERVAL_V, BTN_Y_PIXEL+INTERVAL_H+titleHeight);
	lv_obj_set_pos(buttoType, BTN_X_PIXEL+INTERVAL_V*2, BTN_Y_PIXEL+INTERVAL_H+titleHeight);
	lv_obj_set_pos(buttonOffXY, BTN_X_PIXEL*2+INTERVAL_V*3, BTN_Y_PIXEL+INTERVAL_H+titleHeight);
	lv_obj_set_pos(buttonBack, BTN_X_PIXEL*3+INTERVAL_V*4, BTN_Y_PIXEL+INTERVAL_H+titleHeight);

    /*Create a label on the Image button*/
	lv_btn_set_layout(buttonPoint1, LV_LAYOUT_OFF);
	lv_btn_set_layout(buttonPoint2, LV_LAYOUT_OFF);
	lv_btn_set_layout(buttonPoint3, LV_LAYOUT_OFF);
	lv_btn_set_layout(buttonPoint4, LV_LAYOUT_OFF);
	lv_btn_set_layout(buttonPoint5, LV_LAYOUT_OFF);
	lv_btn_set_layout(buttoType, LV_LAYOUT_OFF);
	lv_btn_set_layout(buttonOffXY, LV_LAYOUT_OFF);
	lv_btn_set_layout(buttonBack, LV_LAYOUT_OFF);
	
    lv_obj_t *label_Point1 = lv_label_create(buttonPoint1, NULL);
	lv_obj_t *label_Point2 = lv_label_create(buttonPoint2, NULL);
	lv_obj_t *label_Point3 = lv_label_create(buttonPoint3, NULL);
	lv_obj_t *label_Point4 = lv_label_create(buttonPoint4, NULL);
	lv_obj_t *label_Point5 = lv_label_create(buttonPoint5, NULL);
	labelType = lv_label_create(buttoType, NULL);
	lv_obj_t * labelOffXY = lv_label_create(buttonOffXY, NULL);
	lv_obj_t *label_Back = lv_label_create(buttonBack, NULL);
	
	if(gCfgItems.multiple_language !=0)
	{
	    lv_label_set_text(label_Point1, leveling_menu.position1);
		lv_obj_align(label_Point1, buttonPoint1, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);

		lv_label_set_text(label_Point2, leveling_menu.position2);
		lv_obj_align(label_Point2, buttonPoint2, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);

		lv_label_set_text(label_Point3, leveling_menu.position3);
		lv_obj_align(label_Point3, buttonPoint3, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);

	    lv_label_set_text(label_Point4, leveling_menu.position4);
		lv_obj_align(label_Point4, buttonPoint4, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);

		lv_label_set_text(label_Point5, leveling_menu.position5);
		lv_obj_align(label_Point5, buttonPoint5, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);

		lv_label_set_text(labelOffXY, set_menu.motoroffXY);
		lv_obj_align(labelOffXY, buttonOffXY, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);

		lv_label_set_text(label_Back, common_menu.text_back);
		lv_obj_align(label_Back, buttonBack, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);
	}

	disp_level_type();
}

void disp_level_type(void)
{
	if(uiCfg.curSprayerLevel == 0)
	{
		queue.enqueue_one_P(PSTR("T0"));
		lv_obj_set_event_cb_mks(buttoType, event_handler, ID_M_X_TYPE, "bmp_Extru1.bin", 0);
		if(gCfgItems.multiple_language != 0)
		{
			lv_label_set_text(labelType, extrude_menu.ext1);
			lv_obj_align(labelType, buttoType, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);
		}
	}
	else
	{
		queue.enqueue_one_P(PSTR("T1"));
		lv_obj_set_event_cb_mks(buttoType, event_handler, ID_M_X_TYPE, "bmp_Extru2.bin", 0);
		if(gCfgItems.multiple_language != 0)
		{
			lv_label_set_text(labelType, extrude_menu.ext2);
			lv_obj_align(labelType, buttoType, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);
		}
	}
}

void lv_clear_manualLevel(void)
{
	lv_obj_del(scr);
}
#endif
