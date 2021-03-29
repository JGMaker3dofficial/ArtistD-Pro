#include "../../../../MarlinCore.h"
#if ENABLED(TFT_LITTLE_VGL_UI)
#include "draw_ui.h"
#include "../../../../gcode/queue.h"
#include "../../../../module/motion.h"
#include "../../../../gcode/gcode.h"


#define ID_M_X_P		1
#define ID_M_X_N		2
#define ID_M_Y_P		3
#define ID_M_Y_N		4
#define ID_M_Z_P		5
#define ID_M_Z_N		6
#define ID_M_STEP		7
#define ID_M_RETURN		8
#define ID_M_X_TYPE		9

static lv_obj_t *scr;
static lv_obj_t *labelV, *buttonV;//, *labelZpos;
#if ENABLED(DUAL_X_CARRIAGE)
lv_obj_t *buttonXtype;
lv_obj_t *label_Xtype;
volatile uint8_t switch_motor_flag = 0;

static void disp_x_axis_type(void)
{
	if(uiCfg.curSprayerChoose == 1)
	{			
		//lv_obj_set_event_cb_mks(buttonXtype, event_handler,ID_M_X_TYPE,"bmp_Extru2.bin",0);
		if(gCfgItems.multiple_language != 0)
		{
			lv_label_set_text(label_Xtype, move_menu.x2);
			lv_obj_align(label_Xtype, buttonXtype, LV_ALIGN_CENTER, 0, 0);
		}
	}
	else
	{
		//lv_obj_set_event_cb_mks(buttoType, event_handler,ID_M_X_TYPE,"bmp_Extru1.bin",0);
		if(gCfgItems.multiple_language != 0)
		{
			lv_label_set_text(label_Xtype, move_menu.x1);
			lv_obj_align(label_Xtype, buttonXtype, LV_ALIGN_CENTER, 0, 0);
		}
	}	
}
#endif

static void event_handler(lv_obj_t *obj, lv_event_t event)
{
	switch(obj->mks_obj_id)
	{
		case ID_M_X_P:
			if(event == LV_EVENT_CLICKED) {	

			}
			else if(event == LV_EVENT_RELEASED) {
				if(queue.length <= (BUFSIZE-3))
				{
					memset(public_buf_l, 0, sizeof(public_buf_l));
					queue.enqueue_one_P(PSTR("G91"));
					sprintf(public_buf_l, "G1 X%3.1f F%d", uiCfg.move_dist, uiCfg.moveSpeed);
					queue.enqueue_one_P(PSTR(public_buf_l));
					queue.enqueue_one_P(PSTR("G90"));
				}
			}
			break;
		case ID_M_X_N:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				if(queue.length <= (BUFSIZE-3))
				{
					memset(public_buf_l, 0, sizeof(public_buf_l));
					queue.enqueue_one_P(PSTR("G91"));
					sprintf(public_buf_l, "G1 X-%3.1f F%d", uiCfg.move_dist, uiCfg.moveSpeed);
					queue.enqueue_one_P(PSTR(public_buf_l));
					queue.enqueue_one_P(PSTR("G90"));	
				}
			}
			break;
		case ID_M_Y_P:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				if(queue.length <= (BUFSIZE-3))
				{
					memset(public_buf_l, 0, sizeof(public_buf_l));
					queue.enqueue_one_P(PSTR("G91"));
					sprintf(public_buf_l, "G1 Y%3.1f F%d", uiCfg.move_dist, uiCfg.moveSpeed);
					queue.enqueue_one_P(PSTR(public_buf_l));
					queue.enqueue_one_P(PSTR("G90"));
				}
			}
			break;
		case ID_M_Y_N:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				if(queue.length <= (BUFSIZE-3))
				{
					memset(public_buf_l, 0, sizeof(public_buf_l));
					queue.enqueue_one_P(PSTR("G91"));
					sprintf(public_buf_l, "G1 Y-%3.1f F%d", uiCfg.move_dist, uiCfg.moveSpeed);
					queue.enqueue_one_P(PSTR(public_buf_l));
					queue.enqueue_one_P(PSTR("G90"));
				}
			}
			break;
		case ID_M_Z_P:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				if(queue.length <= (BUFSIZE-3))
				{
					memset(public_buf_l, 0, sizeof(public_buf_l));
					queue.enqueue_one_P(PSTR("G91"));
					sprintf(public_buf_l, "G1 Z%3.1f F%d", uiCfg.move_dist, uiCfg.moveSpeed);
					queue.enqueue_one_P(PSTR(public_buf_l));
					queue.enqueue_one_P(PSTR("G90"));
				}
			}
			break;
		case ID_M_Z_N:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				if(queue.length <= (BUFSIZE-3))
				{
					memset(public_buf_l, 0, sizeof(public_buf_l));
					queue.enqueue_one_P(PSTR("G91"));
					sprintf(public_buf_l, "G1 Z-%3.1f F%d", uiCfg.move_dist, uiCfg.moveSpeed);
					queue.enqueue_one_P(PSTR(public_buf_l));
					queue.enqueue_one_P(PSTR("G90"));
				}
			}
			break;
		case ID_M_STEP:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				if(abs(10*(int)uiCfg.move_dist) == 100)
				{
					uiCfg.move_dist = 0.1;
				}
				else
				{
					uiCfg.move_dist *= (float)10;
				}
				
				disp_move_dist();
			}
			break;
		case ID_M_RETURN:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				switch_motor_flag = 0;
				lv_clear_move_motor();
				draw_return_ui();
			}
			break;
		#if ENABLED(DUAL_X_CARRIAGE)
		case ID_M_X_TYPE:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				if(EXTRUDERS == 2)
				{
					if(uiCfg.curSprayerChoose == 0)
					{
						uiCfg.curSprayerChoose = 1;
						gcode.process_subcommands_now_P(PSTR("T1"));
					}
					else
					{
						uiCfg.curSprayerChoose = 0;
						gcode.process_subcommands_now_P(PSTR("T0"));
					}
				}
				else
				{
					uiCfg.curSprayerChoose = 0;
				}
				disp_x_axis_type();
			}
			break;
		#endif
	}
}

void lv_draw_move_motor(void)
{
	if(disp_state_stack._disp_state[disp_state_stack._disp_index] != MOVE_MOTOR_UI)
	{
		disp_state_stack._disp_index++;
		disp_state_stack._disp_state[disp_state_stack._disp_index] = MOVE_MOTOR_UI;
	}
	disp_state = MOVE_MOTOR_UI;

	scr = lv_obj_create(NULL, NULL);

	switch_motor_flag = 1;
	
	lv_obj_set_style(scr, &tft_style_scr);
  	lv_scr_load(scr);
  	lv_obj_clean(scr);

  	lv_obj_t *title = lv_label_create(scr, NULL);
	lv_obj_set_style(title, &tft_style_label_rel);
	lv_obj_set_pos(title, TITLE_XPOS, TITLE_YPOS);
	lv_label_set_text(title, creat_title_text());
  
  	lv_refr_now(lv_refr_get_disp_refreshing());
	
	LV_IMG_DECLARE(bmp_pic);
	LV_IMG_DECLARE(bmp_pic_117x92);
	
	
    /*Create an Image button*/
    lv_obj_t *buttonXI = lv_imgbtn_create(scr, NULL);
	lv_obj_t *buttonXD = lv_imgbtn_create(scr, NULL);
	lv_obj_t *buttonYI = lv_imgbtn_create(scr, NULL);
	lv_obj_t *buttonYD = lv_imgbtn_create(scr, NULL);
	lv_obj_t *buttonZI = lv_imgbtn_create(scr, NULL);
	lv_obj_t *buttonZD = lv_imgbtn_create(scr, NULL);
	#if ENABLED(DUAL_X_CARRIAGE)
	buttonV = lv_imgbtn_create(scr, NULL);
	buttonXtype = lv_imgbtn_create(scr, NULL);
	lv_obj_t *buttonBack = lv_imgbtn_create(scr, NULL);
	#else
	buttonV = lv_imgbtn_create(scr, NULL);
	buttonBack = lv_imgbtn_create(scr, NULL);
	#endif

	lv_obj_set_event_cb_mks(buttonXI, event_handler, ID_M_X_P, "bmp_xAdd.bin",0);
	lv_imgbtn_set_src(buttonXI, LV_BTN_STATE_REL, &bmp_pic);
	lv_imgbtn_set_src(buttonXI, LV_BTN_STATE_PR, &bmp_pic);
	lv_imgbtn_set_style(buttonXI, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonXI, LV_BTN_STATE_REL, &tft_style_label_rel);
	lv_obj_clear_protect(buttonXI, LV_PROTECT_FOLLOW);

	lv_obj_set_event_cb_mks(buttonXD, event_handler, ID_M_X_N, "bmp_xDec.bin",0);
	lv_imgbtn_set_src(buttonXD, LV_BTN_STATE_REL, &bmp_pic);
	lv_imgbtn_set_src(buttonXD, LV_BTN_STATE_PR, &bmp_pic);
	lv_imgbtn_set_style(buttonXD, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonXD, LV_BTN_STATE_REL, &tft_style_label_rel);

	lv_obj_set_event_cb_mks(buttonYI, event_handler, ID_M_Y_P, "bmp_yAdd.bin",0);	
    lv_imgbtn_set_src(buttonYI, LV_BTN_STATE_REL, &bmp_pic);
    lv_imgbtn_set_src(buttonYI, LV_BTN_STATE_PR, &bmp_pic);	
	lv_imgbtn_set_style(buttonYI, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonYI, LV_BTN_STATE_REL, &tft_style_label_rel);

	lv_obj_set_event_cb_mks(buttonYD, event_handler, ID_M_Y_N, "bmp_yDec.bin",0);	
    lv_imgbtn_set_src(buttonYD, LV_BTN_STATE_REL, &bmp_pic);
    lv_imgbtn_set_src(buttonYD, LV_BTN_STATE_PR, &bmp_pic);	
	lv_imgbtn_set_style(buttonYD, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonYD, LV_BTN_STATE_REL, &tft_style_label_rel);

	lv_obj_set_event_cb_mks(buttonZI, event_handler, ID_M_Z_P, "bmp_zAdd.bin",0);	
    lv_imgbtn_set_src(buttonZI, LV_BTN_STATE_REL, &bmp_pic);
    lv_imgbtn_set_src(buttonZI, LV_BTN_STATE_PR, &bmp_pic);	
	lv_imgbtn_set_style(buttonZI, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonZI, LV_BTN_STATE_REL, &tft_style_label_rel);

	lv_obj_set_event_cb_mks(buttonZD, event_handler, ID_M_Z_N, "bmp_zDec.bin",0);	
    lv_imgbtn_set_src(buttonZD, LV_BTN_STATE_REL, &bmp_pic);
    lv_imgbtn_set_src(buttonZD, LV_BTN_STATE_PR, &bmp_pic);	
	lv_imgbtn_set_style(buttonZD, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonZD, LV_BTN_STATE_REL, &tft_style_label_rel);

	#if ENABLED(DUAL_X_CARRIAGE)
	lv_obj_set_event_cb_mks(buttonV, event_handler, ID_M_STEP, "bmp_Move_step.bin",0);	
    lv_imgbtn_set_src(buttonV, LV_BTN_STATE_REL, &bmp_pic_117x92);
    lv_imgbtn_set_src(buttonV, LV_BTN_STATE_PR, &bmp_pic_117x92);	
	lv_imgbtn_set_style(buttonV, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonV, LV_BTN_STATE_REL, &tft_style_label_rel);

	lv_obj_set_event_cb_mks(buttonXtype, event_handler, ID_M_X_TYPE, "bmp_X_type.bin",0);
    lv_imgbtn_set_src(buttonXtype, LV_BTN_STATE_REL, &bmp_pic_117x92);
    lv_imgbtn_set_src(buttonXtype, LV_BTN_STATE_PR, &bmp_pic_117x92);	
	lv_imgbtn_set_style(buttonXtype, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonXtype, LV_BTN_STATE_REL, &tft_style_label_rel);

	lv_obj_set_event_cb_mks(buttonBack, event_handler, ID_M_RETURN, "bmp_Back.bin",0);	
    lv_imgbtn_set_src(buttonBack, LV_BTN_STATE_REL, &bmp_pic_117x92);
    lv_imgbtn_set_src(buttonBack, LV_BTN_STATE_PR, &bmp_pic_117x92);	
	lv_imgbtn_set_style(buttonBack, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonBack, LV_BTN_STATE_REL, &tft_style_label_rel);
	
	#else
	//lv_obj_set_event_cb_mks(buttonV, event_handler,ID_T_MORE,"bmp_More.bin",0);	
    lv_imgbtn_set_src(buttonV, LV_BTN_STATE_REL, &bmp_pic);
    lv_imgbtn_set_src(buttonV, LV_BTN_STATE_PR, &bmp_pic);	
	lv_imgbtn_set_style(buttonV, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonV, LV_BTN_STATE_REL, &tft_style_label_rel);

	lv_obj_set_event_cb_mks(buttonBack, event_handler,ID_M_RETURN,"bmp_Return.bin",0);	
    lv_imgbtn_set_src(buttonBack, LV_BTN_STATE_REL, &bmp_pic);
    lv_imgbtn_set_src(buttonBack, LV_BTN_STATE_PR, &bmp_pic);	
	lv_imgbtn_set_style(buttonBack, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonBack, LV_BTN_STATE_REL, &tft_style_label_rel);
	#endif
	
	lv_obj_set_pos(buttonXI, INTERVAL_V, titleHeight);
	lv_obj_set_pos(buttonYI, BTN_X_PIXEL+INTERVAL_V*2, titleHeight);
	lv_obj_set_pos(buttonZI, BTN_X_PIXEL*2+INTERVAL_V*3, titleHeight);
	lv_obj_set_pos(buttonXD, INTERVAL_V, BTN_Y_PIXEL+INTERVAL_H+titleHeight);
	lv_obj_set_pos(buttonYD, BTN_X_PIXEL+INTERVAL_V*2, BTN_Y_PIXEL+INTERVAL_H+titleHeight);
	lv_obj_set_pos(buttonZD, BTN_X_PIXEL*2+INTERVAL_V*3, BTN_Y_PIXEL+INTERVAL_H+titleHeight);
	#if ENABLED(DUAL_X_CARRIAGE)
	lv_obj_set_pos(buttonV, OTHER_BTN_XPIEL*3+INTERVAL_V*4, titleHeight);
	lv_obj_set_pos(buttonXtype, OTHER_BTN_XPIEL*3+INTERVAL_V*4, titleHeight+OTHER_BTN_YPIEL+INTERVAL_H+1);
	lv_obj_set_pos(buttonBack, OTHER_BTN_XPIEL*3+INTERVAL_V*4, titleHeight+OTHER_BTN_YPIEL*2+(INTERVAL_H+1)*2);
	#else
	lv_obj_set_pos(buttonV,BTN_X_PIXEL*3+INTERVAL_V*4,titleHeight);
	lv_obj_set_pos(buttonBack,BTN_X_PIXEL*3+INTERVAL_V*4,  BTN_Y_PIXEL+INTERVAL_H+titleHeight);
	#endif
	
    /*Create a label on the Image button*/
	lv_btn_set_layout(buttonXI, LV_LAYOUT_OFF);
	lv_btn_set_layout(buttonXD, LV_LAYOUT_OFF);
	lv_btn_set_layout(buttonYI, LV_LAYOUT_OFF);
	lv_btn_set_layout(buttonYD, LV_LAYOUT_OFF);
	lv_btn_set_layout(buttonZI, LV_LAYOUT_OFF);
	lv_btn_set_layout(buttonZD, LV_LAYOUT_OFF);
	#if ENABLED(DUAL_X_CARRIAGE)
	lv_btn_set_layout(buttonV, LV_LAYOUT_OFF);
	lv_btn_set_layout(buttonXtype, LV_LAYOUT_OFF);
	lv_btn_set_layout(buttonBack, LV_LAYOUT_OFF);
	#else
	lv_btn_set_layout(buttonV, LV_LAYOUT_OFF);
	lv_btn_set_layout(buttonBack, LV_LAYOUT_OFF);
	#endif
	
    lv_obj_t *labelXI = lv_label_create(buttonXI, NULL);
	lv_obj_t *labelXD = lv_label_create(buttonXD, NULL);
	lv_obj_t *labelYI = lv_label_create(buttonYI, NULL);
	lv_obj_t *labelYD = lv_label_create(buttonYD, NULL);
	lv_obj_t *labelZI = lv_label_create(buttonZI, NULL);
	lv_obj_t *labelZD = lv_label_create(buttonZD, NULL);
	
	#if ENABLED(DUAL_X_CARRIAGE)
	labelV = lv_label_create(buttonV, NULL);
	label_Xtype = lv_label_create(buttonXtype, NULL);
	#else
	labelV = lv_label_create(buttonV, NULL);
	lv_obj_t * label_Back = lv_label_create(buttonBack, NULL);
	#endif

	//labelZpos = lv_label_create(scr, NULL);
	//lv_obj_set_style(labelZpos, &tft_style_label_rel);
	//lv_obj_set_pos(labelZpos, 380, TITLE_YPOS);

	if(gCfgItems.multiple_language != 0)
	{
	    lv_label_set_text(labelXI, move_menu.x_add);
		lv_obj_align(labelXI, buttonXI, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);

		lv_label_set_text(labelXD, move_menu.x_dec);
		lv_obj_align(labelXD, buttonXD, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);

		lv_label_set_text(labelYI, move_menu.y_add);
		lv_obj_align(labelYI, buttonYI, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);

	    lv_label_set_text(labelYD, move_menu.y_dec);
		lv_obj_align(labelYD, buttonYD, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);

		lv_label_set_text(labelZI,move_menu.z_add);
		lv_obj_align(labelZI, buttonZI, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);

		lv_label_set_text(labelZD, move_menu.z_dec);
		lv_obj_align(labelZD, buttonZD, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);
		#if DISABLED(DUAL_X_CARRIAGE)
		lv_label_set_text(label_Back, common_menu.text_back);
		lv_obj_align(label_Back, buttonBack, LV_ALIGN_IN_BOTTOM_MID,0, BUTTON_TEXT_Y_OFFSET);
		#endif
	}

	disp_move_dist();
	#if ENABLED(DUAL_X_CARRIAGE)
	disp_x_axis_type();
	#endif
}

void disp_move_dist(void)
{
	#if ENABLED(DUAL_X_CARRIAGE)
	if(gCfgItems.multiple_language != 0)
	{
		if((int)(10 * uiCfg.move_dist) == 1)
		{
			lv_label_set_text(labelV, move_menu.step_01mm);
			lv_obj_align(labelV, buttonV, LV_ALIGN_CENTER,0, 0);
		}
		else if((int)(10 * uiCfg.move_dist) == 10)
		{
			lv_label_set_text(labelV, move_menu.step_1mm);
			lv_obj_align(labelV, buttonV, LV_ALIGN_CENTER,0, 0);
		}
		else if((int)(10 * uiCfg.move_dist) == 100)
		{
			lv_label_set_text(labelV, move_menu.step_10mm);
			lv_obj_align(labelV, buttonV, LV_ALIGN_CENTER,0, 0);
		}
	}
	#else
	if((int)(10 * uiCfg.move_dist) == 1)
	{
		lv_obj_set_event_cb_mks(buttonV, event_handler,ID_M_STEP,"bmp_Step_move0_1.bin",0);
	}
	else if((int)(10 * uiCfg.move_dist) == 10)
	{
		lv_obj_set_event_cb_mks(buttonV, event_handler,ID_M_STEP,"bmp_Step_move1.bin",0);
	}
	else if((int)(10 * uiCfg.move_dist) == 100)
	{
		lv_obj_set_event_cb_mks(buttonV, event_handler,ID_M_STEP,"bmp_Step_move10.bin",0);
	}
	if(gCfgItems.multiple_language != 0)
	{
		if((int)(10 * uiCfg.move_dist) == 1)
		{
			lv_label_set_text(labelV, move_menu.step_01mm);
			lv_obj_align(labelV, buttonV, LV_ALIGN_IN_BOTTOM_MID,0, BUTTON_TEXT_Y_OFFSET);
		}
		else if((int)(10 * uiCfg.move_dist) == 10)
		{
			lv_label_set_text(labelV, move_menu.step_1mm);
			lv_obj_align(labelV, buttonV, LV_ALIGN_IN_BOTTOM_MID,0, BUTTON_TEXT_Y_OFFSET);
		}
		else if((int)(10 * uiCfg.move_dist) == 100)
		{
			lv_label_set_text(labelV, move_menu.step_10mm);
			lv_obj_align(labelV, buttonV, LV_ALIGN_IN_BOTTOM_MID,0, BUTTON_TEXT_Y_OFFSET);
		}
	}
	#endif
}

/*
void disp_move_Zpos(void)
{
	memset(public_buf_l, 0, sizeof(public_buf_l));
	sprintf(public_buf_l,"Z : %.3f", current_position[Z_AXIS]);
	lv_label_set_text(labelZpos, public_buf_l);
}*/

void lv_clear_move_motor(void)
{
	lv_obj_del(scr);
}

#endif
