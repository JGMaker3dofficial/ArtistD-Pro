#include "../../../../MarlinCore.h"
#if ENABLED(TFT_LITTLE_VGL_UI)
#include "draw_ui.h"
#include "../../../../gcode/queue.h"
#include "../../../../gcode/gcode.h"
#if ENABLED(DUAL_X_CARRIAGE)
#include "../../../../module/motion.h"


#define ID_T_OFFSET_RETURN			1
#define ID_T_OFFSET_X				2
#define ID_T_OFFSET_Y				3
#define ID_T_OFFSET_Z				4

static lv_obj_t * scr;

static void event_handler(lv_obj_t *obj, lv_event_t event)
{
	switch(obj->mks_obj_id)
	{
		case ID_T_OFFSET_RETURN:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				clear_cur_ui();
				draw_return_ui();
			}
			break;
		case ID_T_OFFSET_X:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				value = t_x_offset;
				lv_clear_tool_offset();
				lv_draw_number_key();
			}
			break;
		case ID_T_OFFSET_Y:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				value = t_y_offset;
				lv_clear_tool_offset();
				lv_draw_number_key();
			}
			break;
		case ID_T_OFFSET_Z:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				value = t_z_offset;
				lv_clear_tool_offset();
				lv_draw_number_key();
			}
			break;
	}
}

void lv_draw_tool_offset(void)
{
	lv_obj_t *buttonBack=NULL, *label_Back=NULL;
	lv_obj_t *buttonXText=NULL, *labelXText=NULL, *buttonXValue=NULL, *labelXValue=NULL;
	lv_obj_t *buttonYText=NULL, *labelYText=NULL, *buttonYValue=NULL, *labelYValue=NULL;
	lv_obj_t *buttonZText=NULL, *labelZText=NULL, *buttonZValue=NULL, *labelZValue=NULL;
	lv_obj_t *line1=NULL, *line2=NULL, *line3=NULL;

	if(disp_state_stack._disp_state[disp_state_stack._disp_index] != TOOL_OFFSET_UI)
	{
		disp_state_stack._disp_index++;
		disp_state_stack._disp_state[disp_state_stack._disp_index] = TOOL_OFFSET_UI;
	}
	disp_state = TOOL_OFFSET_UI;

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
	LV_IMG_DECLARE(bmp_para_bank);

	buttonXText = lv_btn_create(scr, NULL);     											/*Add a button the current screen*/
	lv_obj_set_pos(buttonXText, PARA_UI_POS_X, PARA_UI_POS_Y);                            	/*Set its position*/
	lv_obj_set_size(buttonXText, PARA_UI_VALUE_SIZE_X, PARA_UI_SIZE_Y);                     /*Set its size*/
	lv_obj_set_event_cb(buttonXText, event_handler); 
	lv_btn_set_style(buttonXText, LV_BTN_STYLE_REL, &tft_style_label_rel);    				/*Set the button's released style*/
	lv_btn_set_style(buttonXText, LV_BTN_STYLE_PR, &tft_style_label_pre);      				/*Set the button's pressed style*/
	lv_btn_set_layout(buttonXText, LV_LAYOUT_OFF);
	labelXText = lv_label_create(buttonXText, NULL);          								/*Add a label to the button*/

	buttonXValue = lv_imgbtn_create(scr, NULL);
	lv_obj_set_pos(buttonXValue, PARA_UI_VALUE_POS_X, PARA_UI_POS_Y+PARA_UI_VALUE_V);
	lv_obj_set_event_cb_mks(buttonXValue, event_handler, ID_T_OFFSET_X, "bmp_Value_blank.bin", 0);	
    lv_imgbtn_set_src(buttonXValue, LV_BTN_STATE_REL, &bmp_para_bank);
    lv_imgbtn_set_src(buttonXValue, LV_BTN_STATE_PR, &bmp_para_bank);	
	lv_imgbtn_set_style(buttonXValue, LV_BTN_STATE_PR, &style_para_value_pre);
	lv_imgbtn_set_style(buttonXValue, LV_BTN_STATE_REL, &style_para_value_rel);
	lv_btn_set_layout(buttonXValue, LV_LAYOUT_OFF);
	labelXValue = lv_label_create(buttonXValue, NULL); 

	line1 = lv_line_create(scr, NULL);
	lv_ex_line(line1,line_points[0]);

	buttonYText = lv_btn_create(scr, NULL);     											/*Add a button the current screen*/
	lv_obj_set_pos(buttonYText, PARA_UI_POS_X, PARA_UI_POS_Y*2);                            /*Set its position*/
	lv_obj_set_size(buttonYText, PARA_UI_VALUE_SIZE_X, PARA_UI_SIZE_Y);                     /*Set its size*/
	lv_obj_set_event_cb(buttonYText, event_handler); 
	lv_btn_set_style(buttonYText, LV_BTN_STYLE_REL, &tft_style_label_rel);    				/*Set the button's released style*/
	lv_btn_set_style(buttonYText, LV_BTN_STYLE_PR, &tft_style_label_pre);      				/*Set the button's pressed style*/
	lv_btn_set_layout(buttonYText, LV_LAYOUT_OFF);
	labelYText = lv_label_create(buttonYText, NULL);          								/*Add a label to the button*/

	buttonYValue = lv_imgbtn_create(scr, NULL);
	lv_obj_set_pos(buttonYValue, PARA_UI_VALUE_POS_X, PARA_UI_POS_Y*2+PARA_UI_VALUE_V);
	lv_obj_set_event_cb_mks(buttonYValue, event_handler, ID_T_OFFSET_Y, "bmp_Value_blank.bin",0);	
    lv_imgbtn_set_src(buttonYValue, LV_BTN_STATE_REL, &bmp_para_bank);
    lv_imgbtn_set_src(buttonYValue, LV_BTN_STATE_PR, &bmp_para_bank);	
	lv_imgbtn_set_style(buttonYValue, LV_BTN_STATE_PR, &style_para_value_pre);
	lv_imgbtn_set_style(buttonYValue, LV_BTN_STATE_REL, &style_para_value_rel);
	lv_btn_set_layout(buttonYValue, LV_LAYOUT_OFF);
	labelYValue = lv_label_create(buttonYValue, NULL);

	line2 = lv_line_create(scr, NULL);
	lv_ex_line(line2,line_points[1]);

	buttonZText = lv_btn_create(scr, NULL);     											/*Add a button the current screen*/
	lv_obj_set_pos(buttonZText, PARA_UI_POS_X, PARA_UI_POS_Y*3);                         	/*Set its position*/
	lv_obj_set_size(buttonZText, PARA_UI_VALUE_SIZE_X, PARA_UI_SIZE_Y);                  	/*Set its size*/
	lv_obj_set_event_cb(buttonZText, event_handler); 
	lv_btn_set_style(buttonZText, LV_BTN_STYLE_REL, &tft_style_label_rel);    				/*Set the button's released style*/
	lv_btn_set_style(buttonZText, LV_BTN_STYLE_PR, &tft_style_label_pre);      				/*Set the button's pressed style*/
	lv_btn_set_layout(buttonZText, LV_LAYOUT_OFF);
	labelZText = lv_label_create(buttonZText, NULL);          								/*Add a label to the button*/
	
	buttonZValue = lv_imgbtn_create(scr, NULL);
	lv_obj_set_pos(buttonZValue, PARA_UI_VALUE_POS_X, PARA_UI_POS_Y*3+PARA_UI_VALUE_V);
	lv_obj_set_event_cb_mks(buttonZValue, event_handler, ID_T_OFFSET_Z, "bmp_Value_blank.bin",0);	
   	lv_imgbtn_set_src(buttonZValue, LV_BTN_STATE_REL, &bmp_para_bank);
   	lv_imgbtn_set_src(buttonZValue, LV_BTN_STATE_PR, &bmp_para_bank);	
	lv_imgbtn_set_style(buttonZValue, LV_BTN_STATE_PR, &style_para_value_pre);
	lv_imgbtn_set_style(buttonZValue, LV_BTN_STATE_REL, &style_para_value_rel);
	lv_btn_set_layout(buttonZValue, LV_LAYOUT_OFF);
	labelZValue = lv_label_create(buttonZValue, NULL);

	line3 = lv_line_create(scr, NULL);
	lv_ex_line(line3,line_points[2]);

	buttonBack = lv_imgbtn_create(scr, NULL);
	lv_obj_set_event_cb_mks(buttonBack, event_handler, ID_T_OFFSET_RETURN, "bmp_back70x40.bin",0);	
    lv_imgbtn_set_src(buttonBack, LV_BTN_STATE_REL, &bmp_para_back);
   	lv_imgbtn_set_src(buttonBack, LV_BTN_STATE_PR, &bmp_para_back);	
	lv_imgbtn_set_style(buttonBack, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonBack, LV_BTN_STATE_REL, &tft_style_label_rel);

	lv_obj_set_pos(buttonBack, PARA_UI_BACL_POS_X, PARA_UI_BACL_POS_Y);
	lv_btn_set_layout(buttonBack, LV_LAYOUT_OFF);
	label_Back = lv_label_create(buttonBack, NULL);
	
	if(gCfgItems.multiple_language !=0)
	{
		memset(public_buf_l, 0, sizeof(public_buf_l));
	    sprintf(public_buf_l, "%.1f", hotend_offset[1].x);
		lv_label_set_text(labelXValue, public_buf_l);
		lv_obj_align(labelXValue, buttonXValue, LV_ALIGN_CENTER, 0, 0);
	        
	    memset(public_buf_l, 0, sizeof(public_buf_l));
	    sprintf(public_buf_l, "%.1f", hotend_offset[1].y);
		lv_label_set_text(labelYValue, public_buf_l);
		lv_obj_align(labelYValue, buttonYValue, LV_ALIGN_CENTER, 0, 0);
	               
	    memset(public_buf_l, 0, sizeof(public_buf_l));
	    sprintf(public_buf_l, "%.1f", hotend_offset[1].z);
		lv_label_set_text(labelZValue, public_buf_l);
		lv_obj_align(labelZValue, buttonZValue, LV_ALIGN_CENTER, 0, 0);
	         
		lv_label_set_text(labelXText, t_offset_menu.xOffset);
		lv_obj_align(labelXText, buttonXText, LV_ALIGN_IN_LEFT_MID, 0, 0);

		lv_label_set_text(labelYText, t_offset_menu.yOffset);
		lv_obj_align(labelYText, buttonYText, LV_ALIGN_IN_LEFT_MID, 0, 0);

		lv_label_set_text(labelZText, t_offset_menu.zOffset);
		lv_obj_align(labelZText, buttonZText, LV_ALIGN_IN_LEFT_MID, 0, 0);
		
		lv_label_set_text(label_Back, common_menu.text_back);
		lv_obj_align(label_Back, buttonBack, LV_ALIGN_CENTER, 0, 0);
	}
}

void lv_clear_tool_offset(void)
{
	lv_obj_del(scr);
}
#endif
#endif
