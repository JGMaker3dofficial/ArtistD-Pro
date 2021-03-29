#ifndef _TFT_MULTI_LANGUAGE_H
#define _TFT_MULTI_LANGUAGE_H

#include "tft_Language_s_cn.h"
#include "tft_Language_ge.h"
#include "tft_Language_en.h"
#include "tft_Language_ru.h"
#include "tft_Language_sp.h"
#include "tft_Language_fr.h"
#include "tft_Language_it.h"


#define LANG_SIMPLE_CHINESE				1
#define LANG_GERMAN						2
#define LANG_ENGLISH					3
#define LANG_RUSSIAN					4
#define LANG_SPANISH					5
#define LANG_FRENCH						6
#define LANG_ITALY						7

#define MULTI_LANGUAGE_ENABLE			1
#define MULTI_LANGUAGE_DISABLE			0

#define TEXT_VALUE                  	"%d/%d"
#define TEXT_VALUE_T                  	": %d℃"
#define TEXT_VALUE_mm                 	": %dmm"
#define TEXT_VALUE_cm                 	": %dcm"
#define TEXT_VALUE_m                  	": %dm"

#define TEMP_UNIT_SYBOL               	"%d℃"
#define FLOAT_TEMP_UNIT_SYBOL         	"%.1f℃"

#define TEXT_1C							"1℃"
#define TEXT_5C							"5℃"
#define TEXT_10C						"10℃"
#define TEXT_50C						"50℃"

#define AXIS_X_ADD_TEXT			    	"X+"
#define AXIS_X_DEC_TEXT			    	"X-"
#define AXIS_Y_ADD_TEXT			    	"Y+"
#define AXIS_Y_DEC_TEXT			    	"Y-"
#define AXIS_Z_ADD_TEXT			    	"Z+"
#define AXIS_Z_DEC_TEXT			    	"Z-"
#define TEXT_001MM						"0.01mm"
#define TEXT_005MM						"0.05mm"
#define TEXT_01MM						"0.1mm"
#define TEXT_1MM						"1mm"
#define TEXT_10MM						"10mm"

#define TEXT_X1							"X1"
#define TEXT_X2							"X2"

#define EXTRUDE_1MM_TEXT				"1mm"
#define EXTRUDE_5MM_TEXT				"5mm"
#define EXTRUDE_10MM_TEXT		    	"10mm"

#define STEP_1PERCENT					"1%"
#define STEP_5PERCENT					"5%"
#define STEP_10PERCENT					"10%"

#define LANGUAGE_S_CN					"简体"
#define LANGUAGE_T_CN					"繁体"
#define LANGUAGE_EN						"English"
#define LANGUAGE_JP						"日本語"
#define LANGUAGE_GE						"Deutsch"
#define LANGUAGE_FR						"français"
#define LANGUAGE_IT                 	"Italia"
#define LANGUAGE_PR                 	"português"
#define LANGUAGE_KR                 	"Korean"
#define LANGUAGE_BR                 	"Brazil"
#define LANGUAGE_RU                		"русский"
#define LANGUAGE_SP                 	"español"

#define HOME_X_TEXT						"X"
#define HOME_Y_TEXT						"Y"
#define HOME_Z_TEXT						"Z"
#define HOME_ALL_TEXT					"All"
#define ABOUT_TYPE_TEXT					"MKS Robin Pro"
#define ABOUT_VERSION_TEXT				"1.0.0"

#define FAN_OPEN_TEXT					"100%"
#define FAN_HALF_TEXT					"50%"
#define FAN_CLOSE_TEXT					"0%"

#define WIFI_TEXT						"WIFI"
#define WIFI_IP_TEXT					"IP: "
#define WIFI_NAME_TEXT					"WiFi: "
#define WIFI_KEY_TEXT					"Key: "
#define WIFI_STATE_AP_TEXT				"State: AP"
#define WIFI_STATE_STA_TEXT				"State: STA"
#define WIFI_CONNECTED_TEXT				"Connected"
#define WIFI_DISCONNECTED_TEXT  		"Disconnected"
#define WIFI_EXCEPTION_TEXT				"Exception"

#define FILAMENT_TIPS2_TEXT					"T:"

#define DIALOG_UPLOAD_ING_EN				"Uploading......"
#define DIALOG_UPLOAD_ERROR_EN				"Upload error"
#define DIALOG_UPLOAD_FINISH_EN				"Upload finished"
#define DIALOG_UPLOAD_SIZE_EN				"Size"
#define DIALOG_UPLOAD_TIME_EN				"Time"
#define DIALOG_UPLOAD_SPEED_EN				"Speed"
#define DIALOG_UPDATE_WIFI_FIRMWARE_EN		"Updating wifi model firmware"
#define DIALOG_UPDATE_WIFI_WEB_EN			"Updating wifi model web data"

#define ZOFFSET_STEP001      				"0.01mm"
#define ZOFFSET_STEP01      				"0.1mm"
#define ZOFFSET_STEP1      					"1mm"

typedef struct common_menu_disp
{
	const char *text_back;
	const char *dialog_confirm_title;
	const char *close_machine_tips;
	const char *unbind_printer_tips;
	const char *print_special_title;
	const char *pause_special_title;
	const char *operate_special_title;
	const char *next;
	const char *previous;
}common_menu_def;
extern common_menu_def common_menu;

typedef struct main_menu_disp
{
	const char *title;
	const char *preheat;
	const char *move;
	const char *home;
	const char *print;
	const char *extrude;
	const char *leveling;
	const char *set;
}main_menu_def;
extern main_menu_def main_menu;

typedef struct preheat_menu_disp
{
	const char *adjust_title;
	const char *title;
	const char *add;
	const char *dec;
	const char *ext1;
	const char *ext2;
	const char *hotbed;
	const char *off;
	const char *step_1c;
	const char *step_5c;
	const char *step_10c;
	const char *step_50c;
	const char *back;
	const char *value_state;	
	const char *dialog_tips;
}preheat_menu_def;
extern preheat_menu_def preheat_menu;

typedef struct move_menu_disp
{
	const char *title;
	const char *x_add;
	const char *x_dec;
	const char *y_add;
	const char *y_dec;
	const char *z_add;
	const char *z_dec;
	const char *step_001mm;
	const char *step_005mm;
	const char *step_01mm;
	const char *step_1mm;
	const char *step_10mm;
	const char *x1;
	const char *x2;
	const char *back;
}move_menu_def;
extern move_menu_def move_menu;

typedef struct home_menu_disp
{
	const char *title;
	const char *home_all;
	const char *home_x;
	const char *home_y;
	const char *home_z;
	const char *stopmove;
	const char *back;
}home_menu_def;
extern home_menu_def home_menu;

typedef struct file_menu_disp
{
	const char *title;
	const char *page_up;
	const char *page_down;
	const char *back;
	const char *file_loading;
	const char *no_file;
	const char *no_file_and_check;
}file_menu_def;
extern file_menu_def file_menu;

typedef struct extrude_menu_disp
{
	const char *title;
	const char *in;
	const char *out;
	const char *ext1;
	const char *ext2;
	const char *step_1mm;
	const char *step_5mm;
	const char *step_10mm;
	const char *low;
	const char *normal;
	const char *high;
	const char *back;

	const char *count_value_mm;
	const char *count_value_cm;
	const char *count_value_m;
	const char *temp_value;
	const char *temper_text;
}extrude_menu_def;
extern extrude_menu_def extrude_menu;

typedef struct leveling_menu_disp
{
	const char *title;
	const char *position1;
	const char *position2;
	const char *position3;
	const char *position4;
	const char *position5;
	char *back;
}leveling_menu_def;
extern leveling_menu_def leveling_menu;

typedef struct set_menu_disp
{
	const char *title;
	const char *language;
	const char *fan;
	const char *about;
	const char *filament;
	const char *breakpoint;
	const char *motoroff;
	const char *motoroffXY;
	const char *shutdown;
	const char *back;
	const char *Xmode;
	const char *eepromSet;
	const char *revert;
	const char *revertTips;
	const char *eepromTitle;
	const char *Toffset;
	const char *motorsettings;
}set_menu_def;
extern set_menu_def set_menu;

typedef struct language_menu
{
	const char *title;
	const char *chinese_s;
	const char *german;
	const char *english;
	const char *russian;
	const char *spanish;
	const char *french;
	const char *italy;
	const char *back;
}language_menu_def;
extern language_menu_def language_menu;

typedef struct fan_menu_disp
{
	const char *title;
	const char *add;
	const char *dec; 
	const char *full;
	const char *half;
	const char *off;
	const char *back;
	const char *state;
	const char *state_value;
}fan_menu_def;
extern fan_menu_def fan_menu;

typedef struct about_menu_disp
{
	const char *title;
	const char *type_name;
	const char *firmware_v;
	const char *type;
	const char *version; 
	const char *type_robin;
	const char *type_robin_mini;
	const char *back;
}about_menu_def;
extern about_menu_def about_menu;

typedef struct t_offset_disp
{
	const char *title;
	const char *xOffset;
	const char *yOffset;
	const char *zOffset;
}t_offset_def;
extern t_offset_def t_offset_menu;

typedef struct MotorSettings_menu_disp
{
	const char *title;
	const char *X_Steps;
	const char *Y_Steps;
	const char *Z_Steps;
	const char *E_Steps;
	const char *E0_Steps;
	const char *E1_Steps;
}MotorSettings_menu_def;
extern MotorSettings_menu_def motor_settings_menu;

typedef struct filament_menu_disp
{
	const char *title;
	const char *in;
	const char *out; 
	const char *ext1;
	const char *ext2;
	const char *back;
	const char *stat_temp;
	const char *ready_replace;
	const char *replacing;
	const char *loading;
	const char *unloading;
	const char *heating;
	const char *complete_and_back;
	const char *filament_dialog_load_heat;
	const char *filament_dialog_unload_heat;
	const char *filament_dialog_load_heat_confirm;
	const char *filament_dialog_unload_heat_confirm;
	const char *filament_dialog_loading;
	const char *filament_dialog_unloading;
	const char *filament_dialog_load_completed;
	const char *filament_dialog_unload_completed;
	const char *filament_dialog_ok;
	const char *filament_dialog_back;
  	const char *InLength;
  	const char *InSpeed;
  	const char *FilamentTemperature;
  	const char *OutLength;
  	const char *OutSpeed;
}filament_menu_def;
extern filament_menu_def filament_menu;

typedef struct x_mode_disp
{
	const char *title;
	const char *fullControl;
	const char *autoPark;
	const char *duplication;
	const char *mirrored;
}x_mode_def;
extern x_mode_def x_mode_menu;

typedef struct printing_menu_disp
{
	const char *title;
	const char *option;
	const char *temp1; 
	const char *temp2;
	const char *bed_temp;
	const char *fan_speed;	
	const char *pause;
	const char *resume;
	const char *stop;
}printing_menu_def;
extern printing_menu_def printing_menu;

typedef struct operation_menu_disp
{
	const char *title;
	const char *pause;
	const char *stop; 
	const char *temp;
	const char *fan;
	const char *filament;
	const char *extr;
	const char *speed;
	const char *move;
	const char *back;
}operation_menu_def;
extern operation_menu_def operation_menu;

typedef struct speed_menu_disp
{
	const char *title;
	const char *add;
	const char *dec; 
	const char *extrude;
	const char *move;
	const char *step_1percent;
	const char *step_5percent;
	const char *step_10percent;
	const char *back;
	const char *move_speed;
	const char *extrude_speed;
}speed_menu_def;
extern speed_menu_def speed_menu;

typedef struct print_file_dialog_disp
{
    const char *title;
	const char *confirm;
	const char *cancle;
	const char *print_file;
	const char *cancle_print;
	const char *retry;
	const char *stop;
	const char *no_file_print_tips;
	const char *print_from_breakpoint;
	const char *file_name_too_long_error;
	const char *close_machine_error;
	const char *filament_no_press;
	const char *print_finish;
	const char *print_time;
	const char *reprint;
	const char *wifi_enable_tips;
}print_file_dialog_menu_def;
extern print_file_dialog_menu_def print_file_dialog_menu;

typedef struct pause_msg_disp
{
	const char *pausing;
	const char *changing;
	const char *unload;
	const char *waiting;
	const char *insert;
	const char *load;
	const char *purge;
	const char *resume;
	const char *heat;
	const char *heating;
	const char *option;
	const char *purgeMore;
	const char *continuePrint;
}pause_msg_def;
extern pause_msg_def pause_msg_menu;

typedef struct machine_common_disp
{
	const char *key_1;	
	const char *key_2;	
	const char *key_3;	
	const char *key_4;	
	const char *key_5;	
	const char *key_6;	
	const char *key_7;	
	const char *key_8;	
	const char *key_9;	
	const char *key_0;	
	const char *key_point;	
	const char *key_back;	
	const char *key_reset;	
	const char *key_confirm;	
	const char *negative;
}machine_common_def;
extern machine_common_def machine_menu;

extern void disp_language_init(void);

#endif
