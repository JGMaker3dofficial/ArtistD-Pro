#include "../../../../MarlinCore.h"
#if ENABLED(TFT_LITTLE_VGL_UI)
#include "draw_ui.h"


#define ID_A_RETURN		1

static lv_obj_t *scr;

static void event_handler(lv_obj_t * obj, lv_event_t event)
{
	switch(obj->mks_obj_id)
	{
		case ID_A_RETURN:
			if(event == LV_EVENT_CLICKED) {
				
			}
			else if(event == LV_EVENT_RELEASED) {
				clear_cur_ui();
				draw_return_ui();
			}
			break;
	}
}

void lv_draw_about(void)
{
	if(disp_state_stack._disp_state[disp_state_stack._disp_index] != ABOUT_UI)
	{
		disp_state_stack._disp_index++;
		disp_state_stack._disp_state[disp_state_stack._disp_index] = ABOUT_UI;
	}
	disp_state = ABOUT_UI;

	scr = lv_obj_create(NULL, NULL);
	
	lv_obj_set_style(scr, &tft_style_scr);
  	lv_scr_load(scr);
  	lv_obj_clean(scr);

 	lv_obj_t * title = lv_label_create(scr, NULL);
	lv_obj_set_style(title, &tft_style_label_rel);
	lv_obj_set_pos(title, TITLE_XPOS, TITLE_YPOS);
	lv_label_set_text(title, creat_title_text());
  
  	lv_refr_now(lv_refr_get_disp_refreshing());
	
	LV_IMG_DECLARE(bmp_para_back);
	
    /*Create an Image button*/
	lv_obj_t *buttonBack = lv_imgbtn_create(scr, NULL);

	lv_obj_set_event_cb_mks(buttonBack, event_handler, ID_A_RETURN, "bmp_back70x40.bin", 0);	
    lv_imgbtn_set_src(buttonBack, LV_BTN_STATE_REL, &bmp_para_back);
    lv_imgbtn_set_src(buttonBack, LV_BTN_STATE_PR, &bmp_para_back);	
	lv_imgbtn_set_style(buttonBack, LV_BTN_STATE_PR, &tft_style_label_pre);
	lv_imgbtn_set_style(buttonBack, LV_BTN_STATE_REL, &tft_style_label_rel);

	lv_obj_set_pos(buttonBack, PARA_UI_BACL_POS_X, PARA_UI_BACL_POS_Y);
	lv_btn_set_layout(buttonBack, LV_LAYOUT_OFF);
    
	/*Create a label on the Image button*/
	lv_obj_t *label_Back = lv_label_create(buttonBack, NULL);

	if(gCfgItems.multiple_language !=0)
	{
		lv_label_set_text(label_Back, common_menu.text_back);
		lv_obj_align(label_Back, buttonBack, LV_ALIGN_CENTER, 0, 0);
	}

	lv_obj_t *fw_version = lv_label_create(scr, NULL);
	lv_obj_set_style(fw_version, &tft_style_label_rel);
	lv_label_set_text(fw_version, ARTIST_D_PRO_VERSION);
	lv_obj_align(fw_version, NULL, LV_ALIGN_CENTER, 0, -60);

	lv_obj_t *fw_type = lv_label_create(scr, NULL);
	lv_obj_set_style(fw_type, &tft_style_label_rel);
	#if (MOTHERBOARD == BOARD_MKS_ROBIN_PRO)
	lv_label_set_text(fw_type, "Firmware: Robin_Pro35");
	#elif (MOTHERBOARD == BOARD_MKS_ROBIN_NANO)
	lv_label_set_text(fw_type, "Firmware: Robin_Nano35");
	#endif
	lv_obj_align(fw_type, NULL, LV_ALIGN_CENTER, 0, -20);

	lv_obj_t *board = lv_label_create(scr, NULL);
	lv_obj_set_style(board, &tft_style_label_rel);
	#if (MOTHERBOARD == BOARD_MKS_ROBIN_PRO)
	lv_label_set_text(board, "Board: MKS Robin pro");
	#elif (MOTHERBOARD == BOARD_MKS_ROBIN_NANO)
	lv_label_set_text(board, "Board: MKS Robin nano");
	#endif
	lv_obj_align(board, NULL, LV_ALIGN_CENTER, 0, 20);
}

void lv_clear_about(void)
{
	lv_obj_del(scr);
}
#endif
