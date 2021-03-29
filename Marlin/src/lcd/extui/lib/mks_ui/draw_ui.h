#ifndef _DRAW_UI_H
#define _DRAW_UI_H


#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

#include <stdint.h>
#include <string.h>
#include "lvgl.h"
#include "tft_multi_language.h"
#include "draw_ready_print.h"
#include "draw_language.h"
#include "draw_set.h"
#include "draw_print_file.h"
#include "draw_dialog.h"
#include "draw_printing.h"
#include "draw_opration.h"
#include "draw_preHeat.h"
#include "draw_extrusion.h"
#include "draw_home.h"
#include "draw_move_motor.h"
#include "draw_fan.h"
#include "draw_about.h"
#include "draw_change_speed.h"
#include "draw_manuaLevel.h"
#include "draw_error_message.h"
#include "draw_x_mode.h"
#include "draw_eeprom_settings.h"
#include "draw_tool_offset.h"
#include "draw_motor_settings.h"
#include "draw_filament_change.h"
#include "draw_number_key.h"

#define  TFT35

#ifdef TFT35
#define TFT_WIDTH   	480
#define TFT_HEIGHT   	320

#define titleHeight		36				//TFT_screen.title_high
#define INTERVAL_H		2				//TFT_screen.gap_h
#define INTERVAL_V		2				//TFT_screen.gap_v
#define BTN_X_PIXEL		117				//TFT_screen.btn_x_pixel
#define BTN_Y_PIXEL		140				//TFT_screen.btn_y_pixel

#define SIMPLE_FIRST_PAGE_GRAP		30

#define BUTTON_TEXT_Y_OFFSET		-20

#define TITLE_XPOS	 		3				//TFT_screen.title_xpos
#define TITLE_YPOS	 		5				//TFT_screen.title_ypos

#define FILE_BTN_CNT    	6

#define OTHER_BTN_XPIEL		117
#define OTHER_BTN_YPIEL		92

#define FILE_PRE_PIC_X_OFFSET	8
#define FILE_PRE_PIC_Y_OFFSET	0

#define PREVIEW_LITTLE_PIC_SIZE		40910		//400*100+9*101+1
#define PREVIEW_SIZE				202720		//(PREVIEW_LITTLE_PIC_SIZE+800*200+201*9+1)

#define GCFG_FLAG_VALUE 	0xee

#define PARA_UI_POS_X		10
#define PARA_UI_POS_Y		50

#define PARA_UI_SIZE_X		450
#define PARA_UI_SIZE_Y		40

#define PARA_UI_ARROW_V		15

#define PARA_UI_BACL_POS_X		400
#define PARA_UI_BACL_POS_Y		270

#define PARA_UI_TURN_PAGE_POS_X		320
#define PARA_UI_TURN_PAGE_POS_Y		270

#define PARA_UI_VALUE_SIZE_X	370
#define PARA_UI_VALUE_POS_X		400
#define PARA_UI_VALUE_V			5

#define PARA_UI_STATE_POS_X		380
#define PARA_UI_STATE_V			2

#else
#define TFT_WIDTH   	320
#define TFT_HEIGHT   	240
#endif

#define REPRINT_FULL_CONTROL	0
#define REPRINT_AUTO_PARK		1
#define REPRINT_DUPLICATION		2
#define REPRINT_MIRROR			3

typedef struct
{
	uint8_t spi_flash_flag;
	uint8_t multiple_language;
	uint8_t language;
	uint8_t leveling_mode;
	uint8_t from_flash_pic;
	uint8_t finish_power_off;
	uint8_t dual_x_mode;
	uint32_t curFilesize;
	int32_t filamentchange_load_length;
	int32_t filamentchange_load_speed;
	int32_t filamentchange_unload_length;
	int32_t filamentchange_unload_speed;
	int32_t	filament_limit_temper;
}CFG_ITMES;

typedef struct
{
	uint8_t curTempType:1,
			curSprayerChoose:1,
			curSprayerLevel:2,
			curSprayerChoose_bak:4;
	uint8_t	stepHeat:6,
			ui_page:1,
			leveling_first_time:1;
	uint8_t	filament_load_heat_flg:1,
			filament_unload_heat_flg:1,
			filament_heat_completed_load:1,
			filament_heat_completed_unload:1,
			filament_loading_completed:1,
			filament_unloading_completed:1,
			filament_loading_time_flg:1,
			filament_unloading_time_flg:1;
	uint8_t extruStep;
	uint8_t extruSpeed;
	uint8_t stepPrintSpeed;
	uint8_t print_state;
	uint16_t moveSpeed;
	uint16_t moveSpeed_bak;
	uint8_t  filament_rate;
	uint32_t filament_loading_time;
	uint32_t filament_unloading_time;
	uint32_t filament_loading_time_cnt;
  	uint32_t filament_unloading_time_cnt;
	  
	float 	move_dist;
	float	desireSprayerTempBak;
	float	current_e_position_bak;
}UI_CFG;

typedef enum
{
	// MAIN
	MAIN_UI,
	PRINT_READY_UI,
	PRE_HEAT_UI,
	MOVE_MOTOR_UI,
	ZERO_UI,
	PRINT_FILE_UI,
	EXTRUSION_UI,
	LEVELING_UI,
	SET_UI,
	X_MODE_UI,
	// SET
	LANGUAGE_UI,
	FAN_UI,
	ABOUT_UI,
	EEPROM_SETTINGS_UI,
	TOOL_OFFSET_UI,
	MOTOR_SETTINGS_UI,
	FILAMENTCHANGE_UI,
	// PRINTING
	PRINTING_UI,
	OPERATE_UI,
	CHANGE_SPEED_UI,
	// OTHER
	DIALOG_UI,
	NUMBER_KEY_UI,
	ERROR_MESSAGE_UI,
} DISP_STATE;

typedef enum
{
	Xstep,
	Ystep,
	Zstep,
	E0step,
	E1step,
	t_x_offset,
	t_y_offset,
	t_z_offset,
	load_length,
	load_speed,
	unload_length,
	unload_speed,
	filament_temp,
}value_state;
extern value_state value;

typedef struct
{
	DISP_STATE _disp_state[100];
	int       _disp_index;
	
} DISP_STATE_STACK;

typedef struct
{
	int16_t  days;    
	uint16_t    hours;
	uint8_t    minutes;
	volatile int8_t    seconds;
	int8_t    ms_10;
	int8_t	start;
} PRINT_TIME;
extern PRINT_TIME  print_time;

extern lv_point_t line_points[4][2];
extern CFG_ITMES gCfgItems;
extern UI_CFG uiCfg;
extern DISP_STATE disp_state;
extern DISP_STATE last_disp_state;
extern DISP_STATE_STACK disp_state_stack;

extern lv_style_t tft_style_scr;
extern lv_style_t tft_style_label_pre;
extern lv_style_t tft_style_label_rel;
extern lv_style_t tft_style_label_sel_pre;
extern lv_style_t tft_style_label_sel_rel;
extern lv_style_t style_para_value_pre;
extern lv_style_t style_para_value_rel;
extern lv_style_t style_num_key_pre;
extern lv_style_t style_num_key_rel;
extern lv_style_t style_num_text;
extern lv_style_t lv_bar_style_indic;

extern char public_buf_m[100];
extern char public_buf_l[30];

extern void gCfgItems_init(void);
extern void ui_cfg_init(void);
extern void tft_style_init(void);
extern char *creat_title_text(void);
extern void preview_gcode_prehandle(char *path);
extern void update_spi_flash(void);
extern void disp_pre_gcode(int xpos_pixel, int ypos_pixel);
extern void GUI_RefreshPage(void);
extern void clear_cur_ui(void);
extern void draw_return_ui(void);
extern void sd_detection(void);
extern void gCfg_to_spiFlah(void);
extern void print_time_count(void);
extern void printer_action_polling(void);
extern void lv_ex_line(lv_obj_t *line, lv_point_t *points);

#if defined(__cplusplus)
}    /* Make sure we have C-declarations in C++ programs */
#endif

#endif

