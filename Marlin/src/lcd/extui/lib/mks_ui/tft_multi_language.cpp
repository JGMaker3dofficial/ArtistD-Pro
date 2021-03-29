#include "../../../../MarlinCore.h"
#if ENABLED(TFT_LITTLE_VGL_UI)
#include "draw_ui.h"
#include "tft_multi_language.h"


common_menu_def common_menu;
main_menu_def main_menu;
preheat_menu_def preheat_menu;
move_menu_def move_menu;
home_menu_def home_menu;
file_menu_def file_menu;
extrude_menu_def extrude_menu;
leveling_menu_def leveling_menu;
set_menu_def set_menu;
language_menu_def language_menu;
fan_menu_def fan_menu;
about_menu_def about_menu;
t_offset_def t_offset_menu;
MotorSettings_menu_def motor_settings_menu;
filament_menu_def filament_menu;
x_mode_def x_mode_menu;
printing_menu_def printing_menu;
operation_menu_def operation_menu;
speed_menu_def speed_menu;
print_file_dialog_menu_def print_file_dialog_menu;
pause_msg_def pause_msg_menu;
machine_common_def machine_menu;

void disp_language_init(void)
{
	preheat_menu.value_state = TEXT_VALUE;
	preheat_menu.step_1c = TEXT_1C;
	preheat_menu.step_5c = TEXT_5C;
	preheat_menu.step_10c = TEXT_10C;
	preheat_menu.step_50c = TEXT_50C;

	move_menu.x_add = AXIS_X_ADD_TEXT;
	move_menu.x_dec = AXIS_X_DEC_TEXT;
	move_menu.y_add = AXIS_Y_ADD_TEXT;
	move_menu.y_dec = AXIS_Y_DEC_TEXT;
	move_menu.z_add = AXIS_Z_ADD_TEXT;
	move_menu.z_dec = AXIS_Z_DEC_TEXT;

	move_menu.step_001mm = TEXT_001MM;
	move_menu.step_005mm = TEXT_005MM;
	move_menu.step_01mm = TEXT_01MM;
	move_menu.step_1mm = TEXT_1MM;
	move_menu.step_10mm = TEXT_10MM;
	move_menu.x1 = TEXT_X1;
	move_menu.x2 = TEXT_X2;

	home_menu.home_x = HOME_X_TEXT;
	home_menu.home_y = HOME_Y_TEXT;
	home_menu.home_z = HOME_Z_TEXT;
	home_menu.home_all = HOME_ALL_TEXT;

	extrude_menu.temp_value = TEXT_VALUE_T;
	extrude_menu.count_value_mm = TEXT_VALUE_mm;
	extrude_menu.count_value_cm = TEXT_VALUE_cm;
	extrude_menu.count_value_m = TEXT_VALUE_m;
	extrude_menu.step_1mm = EXTRUDE_1MM_TEXT;
	extrude_menu.step_5mm = EXTRUDE_5MM_TEXT;
	extrude_menu.step_10mm = EXTRUDE_10MM_TEXT;

	fan_menu.full = FAN_OPEN_TEXT;
	fan_menu.half = FAN_HALF_TEXT;
	fan_menu.off = FAN_CLOSE_TEXT;

	speed_menu.step_1percent = STEP_1PERCENT;
	speed_menu.step_5percent = STEP_5PERCENT;
	speed_menu.step_10percent = STEP_10PERCENT;

	language_menu.chinese_s = LANGUAGE_S_CN;
	language_menu.english = LANGUAGE_EN;
	language_menu.russian = LANGUAGE_RU;
	language_menu.spanish = LANGUAGE_SP;
	language_menu.german = LANGUAGE_GE;
	language_menu.italy = LANGUAGE_IT;
	language_menu.french = LANGUAGE_FR;
    
	about_menu.type_name= ABOUT_TYPE_TEXT;
	about_menu.firmware_v= ABOUT_VERSION_TEXT;

	printing_menu.temp1 = TEXT_VALUE;
	printing_menu.temp2 = TEXT_VALUE;
	printing_menu.bed_temp = TEXT_VALUE;

	filament_menu.stat_temp = TEXT_VALUE;

	machine_menu.key_0 = KEYBOARD_KEY0_EN;
	machine_menu.key_1 = KEYBOARD_KEY1_EN;
	machine_menu.key_2 = KEYBOARD_KEY2_EN;
	machine_menu.key_3 = KEYBOARD_KEY3_EN;
	machine_menu.key_4 = KEYBOARD_KEY4_EN;
	machine_menu.key_5 = KEYBOARD_KEY5_EN;
	machine_menu.key_6 = KEYBOARD_KEY6_EN;
	machine_menu.key_7 = KEYBOARD_KEY7_EN;
	machine_menu.key_8 = KEYBOARD_KEY8_EN;
	machine_menu.key_9 = KEYBOARD_KEY9_EN;
	machine_menu.key_point= KEYBOARD_KEY_POINT_EN;
	machine_menu.negative=KEYBOARD_KEY_NEGATIVE_EN;

	if (gCfgItems.language != LANG_SIMPLE_CHINESE)
    {
		machine_menu.key_back = KEY_BACK_EN;
		machine_menu.key_reset = KEY_REST_EN;
		machine_menu.key_confirm = KEY_CONFIRM_EN;

    	common_menu.next = NEXT_EN;
    	common_menu.previous = PREVIOUS_EN;

		set_menu.motorsettings = MOTOR_SETTINGS_EN;

		motor_settings_menu.title = MOTOR_CONF_TITLE_EN;
		motor_settings_menu.X_Steps = X_STEPS_EN;
		motor_settings_menu.Y_Steps = Y_STEPS_EN;
		motor_settings_menu.Z_Steps = Z_STEPS_EN;
		motor_settings_menu.E_Steps = E_STEPS_EN;

		filament_menu.InLength = FILAMENT_IN_LENGTH_EN;
		filament_menu.InSpeed = FILAMENT_IN_SPEED_EN;
		filament_menu.FilamentTemperature = FILAMENT_TEMPERATURE_EN;
		filament_menu.OutLength = FILAMENT_OUT_LENGTH_EN;
		filament_menu.OutSpeed = FILAMENT_OUT_SPEED_EN;
    }
    
	switch(gCfgItems.language)
	{
		case LANG_SIMPLE_CHINESE:
			machine_menu.key_back = KEY_BACK_CN;
			machine_menu.key_reset = KEY_REST_CN;
			machine_menu.key_confirm = KEY_CONFIRM_CN;

			common_menu.dialog_confirm_title = TITLE_DIALOG_CONFIRM_CN;
			common_menu.text_back = BACK_TEXT_CN;
			common_menu.close_machine_tips = DIALOG_CLOSE_MACHINE_CN;
			common_menu.unbind_printer_tips = DIALOG_UNBIND_PRINTER_CN;
			common_menu.print_special_title = PRINTING_GBK;
			common_menu.pause_special_title = PRINTING_PAUSE_GBK;
			common_menu.operate_special_title = PRINTING_OPERATION_GBK;
			common_menu.next = NEXT_CN;
    		common_menu.previous = PREVIOUS_CN;	

			main_menu.title = TITLE_READYPRINT_CN;
			main_menu.preheat = PREHEAT_TEXT_CN;
			main_menu.move = MOVE_TEXT_CN;
			main_menu.home = HOME_TEXT_CN;
			main_menu.print = PRINT_TEXT_CN;
			main_menu.extrude = EXTRUDE_TEXT_CN;
			main_menu.leveling = LEVELING_TEXT_CN;
			main_menu.set = SET_TEXT_CN;

			preheat_menu.adjust_title = TITLE_ADJUST_CN;
			preheat_menu.title = TITLE_PREHEAT_CN;
			preheat_menu.add = ADD_TEXT_CN;
			preheat_menu.dec = DEC_TEXT_CN;
			preheat_menu.ext1 = EXTRUDER_1_TEXT_CN;
			preheat_menu.ext2 = EXTRUDER_2_TEXT_CN;
			preheat_menu.hotbed = HEATBED_TEXT_CN;
			preheat_menu.off = CLOSE_TEXT_CN;
        	preheat_menu.value_state = TEXT_VALUE_CN;         

			move_menu.title = MOVE_TEXT_CN;

			home_menu.title = TITLE_HOME_CN;
			home_menu.stopmove = HOME_STOPMOVE_CN;

			file_menu.title = TITLE_CHOOSEFILE_CN;
			file_menu.page_up = PAGE_UP_TEXT_CN;
			file_menu.page_down = PAGE_DOWN_TEXT_CN;
			file_menu.file_loading = FILE_LOADING_CN;
			file_menu.no_file = NO_FILE_CN;
			file_menu.no_file_and_check = NO_FILE_CN;

			extrude_menu.title = TITLE_EXTRUDE_CN;
			extrude_menu.in = EXTRUDER_IN_TEXT_CN;
			extrude_menu.out = EXTRUDER_OUT_TEXT_CN;
			extrude_menu.ext1 = EXTRUDER_1_TEXT_CN;
			extrude_menu.ext2 = EXTRUDER_2_TEXT_CN;
			extrude_menu.low = EXTRUDE_LOW_SPEED_TEXT_CN;
			extrude_menu.normal = EXTRUDE_MEDIUM_SPEED_TEXT_CN;
			extrude_menu.high = EXTRUDE_HIGH_SPEED_TEXT_CN;
			extrude_menu.temper_text = EXTRUDER_TEMP_TEXT_CN;
            extrude_menu.temp_value = EXTRUDE_TEXT_VALUE_T_CN;

			leveling_menu.title = TITLE_LEVELING_CN;
			leveling_menu.position1 = LEVELING_POINT1_TEXT_CN;
			leveling_menu.position2 = LEVELING_POINT2_TEXT_CN;
			leveling_menu.position3 = LEVELING_POINT3_TEXT_CN;
			leveling_menu.position4 = LEVELING_POINT4_TEXT_CN;
			leveling_menu.position5 = LEVELING_POINT5_TEXT_CN;

			set_menu.title = TITLE_SET_CN;
			set_menu.about = ABOUT_TEXT_CN;
			set_menu.fan = FAN_TEXT_CN;
			set_menu.filament = FILAMENT_TEXT_CN;
			set_menu.breakpoint = BREAK_POINT_TEXT_CN;
			set_menu.motoroff = MOTOR_OFF_TEXT_CN;
			set_menu.motoroffXY = MOTOR_OFF_XY_TEXT_CN;
			set_menu.language = LANGUAGE_TEXT_CN;
			set_menu.shutdown = SHUTDOWN_TEXT_CN;
			set_menu.Xmode = X_MODE_TEXT_CN;
            set_menu.motorsettings = MOTOR_SETTINGS_CN;
        	set_menu.eepromSet = EEPROM_SETTINGS_CN;
			set_menu.eepromTitle = EEPROM_SETTINGS_TITLE_CN;
			set_menu.revert = EEPROM_SETTINGS_REVERT_CN;
			set_menu.revertTips = EEPROM_REVERT_TIPS_CN;
			set_menu.Toffset = TOOL_OFFSET_CN;

			motor_settings_menu.title = MOTOR_CONF_TITLE_CN;
			motor_settings_menu.X_Steps = X_STEPS_CN;
			motor_settings_menu.Y_Steps = Y_STEPS_CN;
			motor_settings_menu.Z_Steps = Z_STEPS_CN;
			motor_settings_menu.E_Steps = E_STEPS_CN;

			about_menu.title = ABOUT_TEXT_CN;
			about_menu.type = ABOUT_TYPE_TEXT_CN;
			about_menu.version = ABOUT_VERSION_TEXT_CN;

			fan_menu.title = FAN_TEXT_CN;
			fan_menu.add = FAN_ADD_TEXT_CN;
			fan_menu.dec = FAN_DEC_TEXT_CN;
			fan_menu.state = FAN_TIPS1_TEXT_CN;

			filament_menu.title = TITLE_FILAMENT_CN;
			filament_menu.in = FILAMENT_IN_TEXT_CN;
			filament_menu.out = FILAMENT_OUT_TEXT_CN;
			filament_menu.ext1 = FILAMENT_EXT0_TEXT_CN;
			filament_menu.ext2 = FILAMENT_EXT1_TEXT_CN;
			filament_menu.ready_replace = FILAMENT_CHANGE_TEXT_CN;
			filament_menu.filament_dialog_load_heat = FILAMENT_DIALOG_LOAD_HEAT_TIPS_CN;
			filament_menu.filament_dialog_load_heat_confirm = FILAMENT_DIALOG_LOAD_CONFIRM1_TIPS_CN;
			filament_menu.filament_dialog_loading = FILAMENT_DIALOG_LOADING_TIPS_CN;
			filament_menu.filament_dialog_load_completed = FILAMENT_DIALOG_LOAD_COMPLETE_TIPS_CN;
			filament_menu.filament_dialog_unload_heat = FILAMENT_DIALOG_UNLOAD_HEAT_TIPS_CN;
			filament_menu.filament_dialog_unload_heat_confirm = FILAMENT_DIALOG_UNLOAD_CONFIRM_TIPS_CN;
			filament_menu.filament_dialog_unloading = FILAMENT_DIALOG_UNLOADING_TIPS_CN;
			filament_menu.filament_dialog_unload_completed = FILAMENT_DIALOG_UNLOAD_COMPLETE_TIPS_CN;
			filament_menu.InLength = FILAMENT_IN_LENGTH_CN;
    		filament_menu.InSpeed = FILAMENT_IN_SPEED_CN;
    		filament_menu.FilamentTemperature = FILAMENT_TEMPERATURE_CN;
    		filament_menu.OutLength = FILAMENT_OUT_LENGTH_CN;
    		filament_menu.OutSpeed = FILAMENT_OUT_SPEED_CN;

			language_menu.title = TITLE_LANGUAGE_CN;
			
			printing_menu.title = TITLE_PRINTING_CN;
			printing_menu.option = PRINTING_OPERATION_CN;
			printing_menu.stop = PRINTING_STOP_CN;
			printing_menu.pause = PRINTING_PAUSE_CN;
			printing_menu.resume = PRINTING_RESUME_CN;

			operation_menu.title = TITLE_OPERATION_CN;
			operation_menu.pause = PRINTING_PAUSE_CN;
			operation_menu.stop = PRINTING_STOP_CN;
			operation_menu.temp = PRINTING_TEMP_CN;
			operation_menu.fan = FAN_TEXT_CN;
			operation_menu.filament= FILAMENT_TEXT_CN;
			operation_menu.extr = PRINTING_EXTRUDER_CN;
			operation_menu.speed = PRINTING_CHANGESPEED_CN;
			operation_menu.move = PRINTING_MOVE_CN;

			speed_menu.title = PRINTING_CHANGESPEED_CN;
			speed_menu.add = ADD_TEXT_CN;
			speed_menu.dec = DEC_TEXT_CN;
			speed_menu.move = MOVE_SPEED_CN;
			speed_menu.extrude = EXTRUDER_SPEED_CN;
			speed_menu.extrude_speed = EXTRUDER_SPEED_STATE_CN;
			speed_menu.move_speed = MOVE_SPEED_STATE_CN;

			print_file_dialog_menu.confirm = DIALOG_CONFIRM_CN;
			print_file_dialog_menu.cancle = DIALOG_CANCLE_CN;
			print_file_dialog_menu.print_file = DIALOG_PRINT_MODEL_CN;
			print_file_dialog_menu.cancle_print = DIALOG_CANCEL_PRINT_CN;
			print_file_dialog_menu.retry = DIALOG_RETRY_CN;
			print_file_dialog_menu.stop = DIALOG_STOP_CN;
			print_file_dialog_menu.no_file_print_tips = DIALOG_ERROR_TIPS1_CN;	
			print_file_dialog_menu.print_from_breakpoint = DIALOG_REPRINT_FROM_BREAKPOINT_CN;

			print_file_dialog_menu.close_machine_error = DIALOG_ERROR_TIPS2_CN;
            print_file_dialog_menu.filament_no_press = DIALOG_FILAMENT_NO_PRESS_CN;

			print_file_dialog_menu.print_finish = DIALOG_PRINT_FINISH_CN;
			print_file_dialog_menu.print_time = DIALOG_PRINT_TIME_CN;
			print_file_dialog_menu.reprint = DIALOG_REPRINT_CN;
			print_file_dialog_menu.wifi_enable_tips = DIALOG_WIFI_ENABLE_TIPS_CN;

			pause_msg_menu.pausing = MESSEGE_PAUSING_CN;
			pause_msg_menu.changing = MESSEGE_CHANGING_CN;
			pause_msg_menu.unload = MESSEGE_UNLOAD_CN;
			pause_msg_menu.waiting = MESSEGE_WAITING_CN;
			pause_msg_menu.insert = MESSEGE_INSERT_CN;
			pause_msg_menu.load = MESSEGE_LOAD_CN;
			pause_msg_menu.purge = MESSEGE_PURGE_CN;
			pause_msg_menu.resume = MESSEGE_RESUME_CN;
			pause_msg_menu.heat = MESSEGE_HEAT_CN;
			pause_msg_menu.heating = MESSEGE_HEATING_CN;
			pause_msg_menu.option = MESSEGE_OPTION_CN;
			pause_msg_menu.purgeMore = MESSEGE_PURGE_MORE_CN;
			pause_msg_menu.continuePrint = MESSEGE_CONTINUE_PRINT_CN;

			x_mode_menu.title = MODE_INDEX_CN;
			x_mode_menu.fullControl = FULL_CONTROL_CN;
			x_mode_menu.autoPark = AUTO_PARK_CN;
			x_mode_menu.duplication = DUPLICATION_CN;
			x_mode_menu.mirrored = MIRRORED_CN;

			t_offset_menu.title = TOOL_OFFSET_TITLE_CN;
			t_offset_menu.xOffset = TOOL_X_OFSSET_CN;
			t_offset_menu.yOffset = TOOL_Y_OFSSET_CN;
			t_offset_menu.zOffset = TOOL_Z_OFSSET_CN;
			break;

		case LANG_GERMAN:
			common_menu.dialog_confirm_title = TITLE_DIALOG_CONFIRM_GE;
			common_menu.text_back = BACK_TEXT_GE;
			common_menu.close_machine_tips = DIALOG_CLOSE_MACHINE_GE;
			common_menu.unbind_printer_tips = DIALOG_UNBIND_PRINTER_GE;
			common_menu.print_special_title = TITLE_PRINTING_GE;
			common_menu.pause_special_title = TITLE_PAUSE_GE;
			common_menu.operate_special_title = TITLE_OPERATION_GE;			

			main_menu.title = TITLE_READYPRINT_GE;
			main_menu.preheat = PREHEAT_TEXT_GE;
			main_menu.move = MOVE_TEXT_GE;
			main_menu.home = HOME_TEXT_GE;
			main_menu.print = PRINT_TEXT_GE;
			main_menu.extrude = EXTRUDE_TEXT_GE;
			main_menu.leveling = LEVELING_TEXT_GE;
			main_menu.set = SET_TEXT_GE;

			preheat_menu.adjust_title = TITLE_ADJUST_GE;
			preheat_menu.title = TITLE_PREHEAT_GE;
			preheat_menu.add = ADD_TEXT_GE;
			preheat_menu.dec = DEC_TEXT_GE;
			preheat_menu.ext1 = EXTRUDER_1_TEXT_GE;
			preheat_menu.ext2 = EXTRUDER_2_TEXT_GE;
			preheat_menu.hotbed = HEATBED_TEXT_GE;
			preheat_menu.off = CLOSE_TEXT_GE;           

			move_menu.title = MOVE_TEXT_GE;

			home_menu.title = TITLE_HOME_GE;
			home_menu.stopmove = HOME_STOPMOVE_GE;

			file_menu.title = TITLE_CHOOSEFILE_GE;
			file_menu.page_up = PAGE_UP_TEXT_GE;
			file_menu.page_down = PAGE_DOWN_TEXT_GE;
			file_menu.file_loading = FILE_LOADING_GE;
			file_menu.no_file = NO_FILE_GE;
			file_menu.no_file_and_check = NO_FILE_AND_CHECK_GE;

			extrude_menu.title = TITLE_EXTRUDE_GE;
			extrude_menu.in = EXTRUDER_IN_TEXT_GE;
			extrude_menu.out = EXTRUDER_OUT_TEXT_GE;
			extrude_menu.ext1 = EXTRUDER_1_TEXT_GE;
			extrude_menu.ext2 = EXTRUDER_2_TEXT_GE;
			extrude_menu.low = EXTRUDE_LOW_SPEED_TEXT_GE;
			extrude_menu.normal = EXTRUDE_MEDIUM_SPEED_TEXT_GE;
			extrude_menu.high = EXTRUDE_HIGH_SPEED_TEXT_GE;
			extrude_menu.temper_text = EXTRUDER_TEMP_TEXT_GE;

			leveling_menu.title = TITLE_LEVELING_GE;
			leveling_menu.position1 = LEVELING_POINT1_TEXT_GE;
			leveling_menu.position2 = LEVELING_POINT2_TEXT_GE;
			leveling_menu.position3 = LEVELING_POINT3_TEXT_GE;
			leveling_menu.position4 = LEVELING_POINT4_TEXT_GE;
			leveling_menu.position5 = LEVELING_POINT5_TEXT_GE;

			set_menu.title = TITLE_SET_GE;
			set_menu.about = ABOUT_TEXT_GE;
			set_menu.fan = FAN_TEXT_GE;
			set_menu.filament = FILAMENT_TEXT_GE;
			set_menu.breakpoint = BREAK_POINT_TEXT_GE;
			set_menu.motoroff = MOTOR_OFF_TEXT_GE;
			set_menu.motoroffXY = MOTOR_OFF_XY_TEXT_GE;
			set_menu.language = LANGUAGE_TEXT_GE;
			set_menu.shutdown = SHUTDOWN_TEXT_GE;
			set_menu.Xmode = X_MODE_TEXT_GE;
            set_menu.eepromSet = EEPROM_SETTINGS_GE;
			set_menu.eepromTitle = EEPROM_SETTINGS_TITLE_GE;
			set_menu.revert = EEPROM_SETTINGS_REVERT_GE;
			set_menu.revertTips = EEPROM_REVERT_TIPS_GE;
			set_menu.Toffset = TOOL_OFFSET_GE;
			set_menu.motorsettings = MOTOR_SETTINGS_GE;

			about_menu.title = ABOUT_TEXT_GE;
			about_menu.type = ABOUT_TYPE_TEXT_GE;
			about_menu.version = ABOUT_VERSION_TEXT_GE;

			fan_menu.title = FAN_TEXT_GE;
			fan_menu.add = FAN_ADD_TEXT_GE;
			fan_menu.dec = FAN_DEC_TEXT_GE;
			fan_menu.state = FAN_TIPS1_TEXT_GE;

			filament_menu.title = TITLE_FILAMENT_GE;
			filament_menu.in = FILAMENT_IN_TEXT_GE;
			filament_menu.out = FILAMENT_OUT_TEXT_GE;
			filament_menu.ext1 = FILAMENT_EXT0_TEXT_GE;
			filament_menu.ext2 = FILAMENT_EXT1_TEXT_GE;
			filament_menu.ready_replace = FILAMENT_CHANGE_TEXT_GE;
			filament_menu.filament_dialog_load_heat = FILAMENT_DIALOG_LOAD_HEAT_TIPS_GE;
			filament_menu.filament_dialog_load_heat_confirm = FILAMENT_DIALOG_LOAD_CONFIRM1_TIPS_GE;
			filament_menu.filament_dialog_loading = FILAMENT_DIALOG_LOADING_TIPS_GE;
			filament_menu.filament_dialog_load_completed = FILAMENT_DIALOG_LOAD_COMPLETE_TIPS_GE;
			filament_menu.filament_dialog_unload_heat = FILAMENT_DIALOG_UNLOAD_HEAT_TIPS_GE;
			filament_menu.filament_dialog_unload_heat_confirm = FILAMENT_DIALOG_UNLOAD_CONFIRM_TIPS_GE;
			filament_menu.filament_dialog_unloading = FILAMENT_DIALOG_UNLOADING_TIPS_GE;
			filament_menu.filament_dialog_unload_completed = FILAMENT_DIALOG_UNLOAD_COMPLETE_TIPS_GE;

			language_menu.title = TITLE_LANGUAGE_GE;

			printing_menu.title = TITLE_PRINTING_GE;
			printing_menu.option = PRINTING_OPERATION_GE;
			printing_menu.stop = PRINTING_STOP_GE;
			printing_menu.pause = PRINTING_PAUSE_GE;
			printing_menu.resume = PRINTING_RESUME_GE;

			operation_menu.title = TITLE_OPERATION_GE;
			operation_menu.pause = PRINTING_PAUSE_GE;
			operation_menu.stop = PRINTING_STOP_GE;
			operation_menu.temp = PRINTING_TEMP_GE;
			operation_menu.fan = FAN_TEXT_GE;
			operation_menu.extr = PRINTING_EXTRUDER_GE;
			operation_menu.speed = PRINTING_CHANGESPEED_GE;			
			operation_menu.filament= FILAMENT_TEXT_GE;
			operation_menu.move = PRINTING_MOVE_GE;

			speed_menu.title = PRINTING_CHANGESPEED_GE;
			speed_menu.add = ADD_TEXT_GE;
			speed_menu.dec = DEC_TEXT_GE;
			speed_menu.move = MOVE_SPEED_GE;
			speed_menu.extrude = EXTRUDER_SPEED_GE;
			speed_menu.extrude_speed = EXTRUDER_SPEED_STATE_GE;
			speed_menu.move_speed = MOVE_SPEED_STATE_GE;

			//print_file_dialog_menu.title = TITLE_DIALOG_CONFIRM_CN;
			print_file_dialog_menu.confirm = DIALOG_CONFIRM_GE;
			print_file_dialog_menu.cancle = DIALOG_CANCLE_GE;
			print_file_dialog_menu.print_file = DIALOG_PRINT_MODEL_GE;
			print_file_dialog_menu.cancle_print = DIALOG_CANCEL_PRINT_GE;
			print_file_dialog_menu.retry = DIALOG_RETRY_GE;
			print_file_dialog_menu.stop = DIALOG_STOP_GE;
			print_file_dialog_menu.no_file_print_tips = DIALOG_ERROR_TIPS1_GE;		
			print_file_dialog_menu.print_from_breakpoint = DIALOG_REPRINT_FROM_BREAKPOINT_GE;

			print_file_dialog_menu.close_machine_error = DIALOG_ERROR_TIPS2_GE;
            print_file_dialog_menu.filament_no_press = DIALOG_FILAMENT_NO_PRESS_GE;
			print_file_dialog_menu.print_finish = DIALOG_PRINT_FINISH_GE;
			print_file_dialog_menu.print_time = DIALOG_PRINT_TIME_GE;
			print_file_dialog_menu.reprint = DIALOG_REPRINT_GE;
			print_file_dialog_menu.wifi_enable_tips = DIALOG_WIFI_ENABLE_TIPS_GE;

			pause_msg_menu.pausing = MESSEGE_PAUSING_GE;
			pause_msg_menu.changing = MESSEGE_CHANGING_GE;
			pause_msg_menu.unload = MESSEGE_UNLOAD_GE;
			pause_msg_menu.waiting = MESSEGE_WAITING_GE;
			pause_msg_menu.insert = MESSEGE_INSERT_GE;
			pause_msg_menu.load = MESSEGE_LOAD_GE;
			pause_msg_menu.purge = MESSEGE_PURGE_GE;
			pause_msg_menu.resume = MESSEGE_RESUME_GE;
			pause_msg_menu.heat = MESSEGE_HEAT_GE;
			pause_msg_menu.heating = MESSEGE_HEATING_GE;
			pause_msg_menu.option = MESSEGE_OPTION_GE;
			pause_msg_menu.purgeMore = MESSEGE_PURGE_MORE_GE;
			pause_msg_menu.continuePrint = MESSEGE_CONTINUE_PRINT_GE;

			x_mode_menu.title = MODE_INDEX_GE;
			x_mode_menu.fullControl = FULL_CONTROL_GE;
			x_mode_menu.autoPark = AUTO_PARK_GE;
			x_mode_menu.duplication = DUPLICATION_GE;
			x_mode_menu.mirrored = MIRRORED_GE;

			t_offset_menu.title = TOOL_OFFSET_TITLE_GE;
			t_offset_menu.xOffset = TOOL_X_OFSSET_GE;
			t_offset_menu.yOffset = TOOL_Y_OFSSET_GE;
			t_offset_menu.zOffset = TOOL_Z_OFSSET_GE;
			break;

		case LANG_RUSSIAN:
			common_menu.dialog_confirm_title = TITLE_DIALOG_CONFIRM_RU;
			common_menu.text_back = BACK_TEXT_RU;
			common_menu.close_machine_tips = DIALOG_CLOSE_MACHINE_RU;
			common_menu.unbind_printer_tips = DIALOG_UNBIND_PRINTER_RU;
			common_menu.print_special_title = PRINTING_OTHER_LANGUGE;
			common_menu.pause_special_title = PRINTING_PAUSE_OTHER_LANGUGE;
			common_menu.operate_special_title = PRINTING_OPERATION_OTHER_LANGUGE;			

			main_menu.title = TITLE_READYPRINT_RU;
			main_menu.preheat = PREHEAT_TEXT_RU;
			main_menu.move = MOVE_TEXT_RU;
			main_menu.home = HOME_TEXT_RU;
			main_menu.print = PRINT_TEXT_RU;
			main_menu.extrude = EXTRUDE_TEXT_RU;
			main_menu.leveling = LEVELING_TEXT_RU;
			main_menu.set = SET_TEXT_RU;

			preheat_menu.adjust_title = TITLE_ADJUST_RU;
			preheat_menu.title = TITLE_PREHEAT_RU;
			preheat_menu.add = ADD_TEXT_RU;
			preheat_menu.dec = DEC_TEXT_RU;
			preheat_menu.ext1 = EXTRUDER_1_TEXT_RU;
			preheat_menu.ext2 = EXTRUDER_2_TEXT_RU;
			preheat_menu.hotbed = HEATBED_TEXT_RU;
			preheat_menu.off = CLOSE_TEXT_RU;

			move_menu.title = MOVE_TEXT_RU;

			home_menu.title = TITLE_HOME_RU;
			home_menu.stopmove = HOME_STOPMOVE_RU;

			file_menu.title = TITLE_CHOOSEFILE_RU;
			file_menu.page_up = PAGE_UP_TEXT_RU;
			file_menu.page_down = PAGE_DOWN_TEXT_RU;
			file_menu.file_loading = FILE_LOADING_RU;
			file_menu.no_file = NO_FILE_RU;
			file_menu.no_file_and_check = NO_FILE_RU;//NO_FILE_AND_CHECK_RU;			

			extrude_menu.title = TITLE_EXTRUDE_RU;
			extrude_menu.in = EXTRUDER_IN_TEXT_RU;
			extrude_menu.out = EXTRUDER_OUT_TEXT_RU;
			extrude_menu.ext1 = EXTRUDER_1_TEXT_RU;
			extrude_menu.ext2 = EXTRUDER_2_TEXT_RU;
			extrude_menu.low = EXTRUDE_LOW_SPEED_TEXT_RU;
			extrude_menu.normal = EXTRUDE_MEDIUM_SPEED_TEXT_RU;
			extrude_menu.high = EXTRUDE_HIGH_SPEED_TEXT_RU;
			extrude_menu.temper_text = EXTRUDER_TEMP_TEXT_RU;

			leveling_menu.title = TITLE_LEVELING_RU;
			leveling_menu.position1 = LEVELING_POINT1_TEXT_RU;
			leveling_menu.position2 = LEVELING_POINT2_TEXT_RU;
			leveling_menu.position3 = LEVELING_POINT3_TEXT_RU;
			leveling_menu.position4 = LEVELING_POINT4_TEXT_RU;
			leveling_menu.position5 = LEVELING_POINT5_TEXT_RU;

			set_menu.title = TITLE_SET_RU;
			set_menu.about = ABOUT_TEXT_RU;
			set_menu.fan = FAN_TEXT_RU;
			set_menu.filament = FILAMENT_TEXT_RU;
			set_menu.breakpoint = BREAK_POINT_TEXT_RU;
			set_menu.motoroff = MOTOR_OFF_TEXT_RU;
			set_menu.motoroffXY = MOTOR_OFF_XY_TEXT_RU;
			set_menu.language = LANGUAGE_TEXT_RU;
			set_menu.shutdown = SHUTDOWN_TEXT_RU;
			set_menu.Xmode = X_MODE_TEXT_RU;
			set_menu.eepromSet = EEPROM_SETTINGS_RU;
			set_menu.eepromTitle = EEPROM_SETTINGS_TITLE_RU;
			set_menu.revert = EEPROM_SETTINGS_REVERT_RU;
			set_menu.revertTips =  EEPROM_REVERT_TIPS_RU;
			set_menu.Toffset = TOOL_OFFSET_RU;		

			about_menu.title = ABOUT_TEXT_RU;
			about_menu.type = ABOUT_TYPE_TEXT_RU;
			about_menu.version = ABOUT_VERSION_TEXT_RU;			

			fan_menu.title = FAN_TEXT_RU;
			fan_menu.add = FAN_ADD_TEXT_RU;
			fan_menu.dec = FAN_DEC_TEXT_RU;
			fan_menu.state = FAN_TIPS1_TEXT_RU;

			filament_menu.title = TITLE_FILAMENT_RU;
			filament_menu.in = FILAMENT_IN_TEXT_RU;
			filament_menu.out = FILAMENT_OUT_TEXT_RU;
			filament_menu.ext1 = FILAMENT_EXT0_TEXT_RU;
			filament_menu.ext2 = FILAMENT_EXT1_TEXT_RU;
			filament_menu.ready_replace = FILAMENT_CHANGE_TEXT_RU;
			filament_menu.filament_dialog_load_heat = FILAMENT_DIALOG_LOAD_HEAT_TIPS_RU;
			filament_menu.filament_dialog_load_heat_confirm = FILAMENT_DIALOG_LOAD_CONFIRM1_TIPS_RU;
			filament_menu.filament_dialog_loading = FILAMENT_DIALOG_LOADING_TIPS_RU;
			filament_menu.filament_dialog_load_completed = FILAMENT_DIALOG_LOAD_COMPLETE_TIPS_RU;
			filament_menu.filament_dialog_unload_heat = FILAMENT_DIALOG_UNLOAD_HEAT_TIPS_RU;
			filament_menu.filament_dialog_unload_heat_confirm = FILAMENT_DIALOG_UNLOAD_CONFIRM_TIPS_RU;
			filament_menu.filament_dialog_unloading = FILAMENT_DIALOG_UNLOADING_TIPS_RU;
			filament_menu.filament_dialog_unload_completed = FILAMENT_DIALOG_UNLOAD_COMPLETE_TIPS_RU;

			language_menu.title = LANGUAGE_TEXT_RU;

			printing_menu.title = TITLE_PRINTING_RU;
			printing_menu.option = PRINTING_OPERATION_RU;
			printing_menu.stop = PRINTING_STOP_RU;
			printing_menu.pause = PRINTING_PAUSE_RU;
			printing_menu.resume = PRINTING_RESUME_RU;

			operation_menu.title = TITLE_OPERATION_RU;
			operation_menu.pause = PRINTING_PAUSE_RU;
			operation_menu.stop = PRINTING_STOP_RU;
			operation_menu.temp = PRINTING_TEMP_RU;
			operation_menu.fan = FAN_TEXT_RU;
			operation_menu.extr = PRINTING_EXTRUDER_RU;
			operation_menu.speed = PRINTING_CHANGESPEED_RU;			
			operation_menu.filament= FILAMENT_TEXT_RU;
			operation_menu.move = PRINTING_MOVE_RU;

			speed_menu.title = PRINTING_CHANGESPEED_RU;
			speed_menu.add = ADD_TEXT_RU;
			speed_menu.dec = DEC_TEXT_RU;
			speed_menu.move = MOVE_SPEED_RU;
			speed_menu.extrude = EXTRUDER_SPEED_RU;
			speed_menu.extrude_speed = EXTRUDER_SPEED_STATE_RU;
			speed_menu.move_speed = MOVE_SPEED_STATE_RU;

			//print_file_dialog_menu.title = TITLE_DIALOG_CONFIRM_RU;
			print_file_dialog_menu.confirm = DIALOG_CONFIRM_RU;
			print_file_dialog_menu.cancle = DIALOG_CANCLE_RU;
			print_file_dialog_menu.print_file = DIALOG_PRINT_MODEL_RU;
			print_file_dialog_menu.cancle_print = DIALOG_CANCEL_PRINT_RU;
			print_file_dialog_menu.retry = DIALOG_RETRY_RU;
			print_file_dialog_menu.stop = DIALOG_STOP_RU;
			print_file_dialog_menu.no_file_print_tips = DIALOG_ERROR_TIPS1_RU;		
			print_file_dialog_menu.print_from_breakpoint = DIALOG_REPRINT_FROM_BREAKPOINT_RU;
			print_file_dialog_menu.close_machine_error = DIALOG_ERROR_TIPS2_RU;
            print_file_dialog_menu.filament_no_press = DIALOG_FILAMENT_NO_PRESS_RU;
			print_file_dialog_menu.print_finish = DIALOG_PRINT_FINISH_RU;
			print_file_dialog_menu.print_time = DIALOG_PRINT_TIME_RU;
			print_file_dialog_menu.reprint = DIALOG_REPRINT_RU;
			print_file_dialog_menu.wifi_enable_tips = DIALOG_WIFI_ENABLE_TIPS_RU;

			pause_msg_menu.pausing = MESSEGE_PAUSING_RU;
			pause_msg_menu.changing = MESSEGE_CHANGING_RU;
			pause_msg_menu.unload = MESSEGE_UNLOAD_RU;
			pause_msg_menu.waiting = MESSEGE_WAITING_RU;
			pause_msg_menu.insert = MESSEGE_INSERT_RU;
			pause_msg_menu.load = MESSEGE_LOAD_RU;
			pause_msg_menu.purge = MESSEGE_PURGE_RU;
			pause_msg_menu.resume = MESSEGE_RESUME_RU;
			pause_msg_menu.heat = MESSEGE_HEAT_RU;
			pause_msg_menu.heating = MESSEGE_HEATING_RU;
			pause_msg_menu.option = MESSEGE_OPTION_RU;
			pause_msg_menu.purgeMore = MESSEGE_PURGE_MORE_RU;
			pause_msg_menu.continuePrint = MESSEGE_CONTINUE_PRINT_RU;

			x_mode_menu.title = MODE_INDEX_RU;
			x_mode_menu.fullControl = FULL_CONTROL_RU;
			x_mode_menu.autoPark = AUTO_PARK_RU;
			x_mode_menu.duplication = DUPLICATION_RU;
			x_mode_menu.mirrored = MIRRORED_RU;

			t_offset_menu.title = TOOL_OFFSET_TITLE_RU;
			t_offset_menu.xOffset = TOOL_X_OFSSET_RU;
			t_offset_menu.yOffset = TOOL_Y_OFSSET_RU;
			t_offset_menu.zOffset = TOOL_Z_OFSSET_RU;
			break;

		case LANG_SPANISH:
			common_menu.dialog_confirm_title = TITLE_DIALOG_CONFIRM_SP;
			common_menu.text_back = BACK_TEXT_SP;
			common_menu.close_machine_tips = DIALOG_CLOSE_MACHINE_SP;
			common_menu.unbind_printer_tips = DIALOG_UNBIND_PRINTER_SP;
			common_menu.print_special_title = PRINTING_SP;
			common_menu.pause_special_title = PRINTING_PAUSAR_SP;
			common_menu.operate_special_title = PRINTING_AJUSTES_SP;			

			main_menu.title = TITLE_READYPRINT_SP;
			main_menu.preheat = PREHEAT_TEXT_SP;
			main_menu.move = MOVE_TEXT_SP;
			main_menu.home = HOME_TEXT_SP;
			main_menu.print = PRINT_TEXT_SP;
			main_menu.extrude = EXTRUDE_TEXT_SP;
			main_menu.leveling = LEVELING_TEXT_SP;
			main_menu.set = SET_TEXT_SP;

			preheat_menu.adjust_title = TITLE_ADJUST_SP;
			preheat_menu.title = TITLE_PREHEAT_SP;
			preheat_menu.add = ADD_TEXT_SP;
			preheat_menu.dec = DEC_TEXT_SP;
			preheat_menu.ext1 = EXTRUDER_1_TEXT_SP;
			preheat_menu.ext2 = EXTRUDER_2_TEXT_SP;
			preheat_menu.hotbed = HEATBED_TEXT_SP;
			preheat_menu.off = CLOSE_TEXT_SP;

			move_menu.title = MOVE_TEXT_SP;

			home_menu.title =TITLE_HOME_SP;
			home_menu.home_x = HOME_X_TEXT_SP;
			home_menu.home_y = HOME_Y_TEXT_SP;
			home_menu.home_z = HOME_Z_TEXT_SP;
			home_menu.home_all = HOME_ALL_TEXT_SP;
			home_menu.stopmove = HOME_STOPMOVE_SP;

			file_menu.title = TITLE_CHOOSEFILE_SP;
			file_menu.page_up = PAGE_UP_TEXT_SP;
			file_menu.page_down = PAGE_DOWN_TEXT_SP;
			file_menu.file_loading = FILE_LOADING_SP;
			file_menu.no_file = NO_FILE_SP;
			file_menu.no_file_and_check = NO_FILE_SP;//NO_FILE_AND_CHECK_SP;			

			extrude_menu.title = TITLE_EXTRUDE_SP;
			extrude_menu.in = EXTRUDER_IN_TEXT_SP;
			extrude_menu.out = EXTRUDER_OUT_TEXT_SP;
			extrude_menu.ext1 = EXTRUDER_1_TEXT_SP;
			extrude_menu.ext2 = EXTRUDER_2_TEXT_SP;
			extrude_menu.low = EXTRUDE_LOW_SPEED_TEXT_SP;
			extrude_menu.normal = EXTRUDE_MEDIUM_SPEED_TEXT_SP;
			extrude_menu.high = EXTRUDE_HIGH_SPEED_TEXT_SP;
			extrude_menu.temper_text = EXTRUDER_TEMP_TEXT_SP;

			leveling_menu.title = TITLE_LEVELING_SP;
			leveling_menu.position1 = LEVELING_POINT1_TEXT_SP;
			leveling_menu.position2 = LEVELING_POINT2_TEXT_SP;
			leveling_menu.position3 = LEVELING_POINT3_TEXT_SP;
			leveling_menu.position4 = LEVELING_POINT4_TEXT_SP;
			leveling_menu.position5 = LEVELING_POINT5_TEXT_SP;

			set_menu.title = TITLE_SET_SP;
			set_menu.about = ABOUT_TEXT_SP;
			set_menu.fan = FAN_TEXT_SP;
			set_menu.filament = FILAMENT_TEXT_SP;
			set_menu.breakpoint = BREAK_POINT_TEXT_SP;
			set_menu.motoroff = MOTOR_OFF_TEXT_SP;
			set_menu.motoroffXY = MOTOR_OFF_XY_TEXT_SP;
			set_menu.language = LANGUAGE_TEXT_SP;
			set_menu.shutdown = SHUTDOWN_TEXT_SP;
			set_menu.Xmode = X_MODE_TEXT_SP;
			set_menu.eepromSet = EEPROM_SETTINGS_SP;
			set_menu.eepromTitle = EEPROM_SETTINGS_TITLE_SP;
			set_menu.revert = EEPROM_SETTINGS_REVERT_SP;
			set_menu.revertTips = EEPROM_REVERT_TIPS_SP;
			set_menu.Toffset = TOOL_OFFSET_SP;	
			
			about_menu.title = ABOUT_TEXT_SP;
			about_menu.type = ABOUT_TYPE_TEXT_SP;
			about_menu.version = ABOUT_VERSION_TEXT_SP;			

			fan_menu.title = FAN_TEXT_SP;
			fan_menu.add = FAN_ADD_TEXT_SP;
			fan_menu.dec = FAN_DEC_TEXT_SP;
			fan_menu.state = FAN_TIPS1_TEXT_SP;

			filament_menu.title = TITLE_FILAMENT_SP;
			filament_menu.in = FILAMENT_IN_TEXT_SP;
			filament_menu.out = FILAMENT_OUT_TEXT_SP;
			filament_menu.ext1 = FILAMENT_EXT0_TEXT_SP;
			filament_menu.ext2 = FILAMENT_EXT1_TEXT_SP;
			filament_menu.ready_replace = FILAMENT_CHANGE_TEXT_SP;
			filament_menu.filament_dialog_load_heat = FILAMENT_DIALOG_LOAD_HEAT_TIPS_SP;
			filament_menu.filament_dialog_load_heat_confirm = FILAMENT_DIALOG_LOAD_CONFIRM1_TIPS_SP;
			filament_menu.filament_dialog_loading = FILAMENT_DIALOG_LOADING_TIPS_SP;
			filament_menu.filament_dialog_load_completed = FILAMENT_DIALOG_LOAD_COMPLETE_TIPS_SP;
			filament_menu.filament_dialog_unload_heat = FILAMENT_DIALOG_UNLOAD_HEAT_TIPS_SP;
			filament_menu.filament_dialog_unload_heat_confirm = FILAMENT_DIALOG_UNLOAD_CONFIRM_TIPS_SP;
			filament_menu.filament_dialog_unloading = FILAMENT_DIALOG_UNLOADING_TIPS_SP;
			filament_menu.filament_dialog_unload_completed = FILAMENT_DIALOG_UNLOAD_COMPLETE_TIPS_SP;

			language_menu.title = LANGUAGE_TEXT_SP;

			printing_menu.title = TITLE_PRINTING_SP;
			printing_menu.option = PRINTING_OPERATION_SP;
			printing_menu.stop = PRINTING_STOP_SP;
			printing_menu.pause = PRINTING_PAUSE_SP;
			printing_menu.resume = PRINTING_RESUME_SP;

			operation_menu.title = TITLE_OPERATION_SP;
			operation_menu.pause = PRINTING_PAUSE_SP;
			operation_menu.stop = PRINTING_STOP_SP;
			operation_menu.temp = PRINTING_TEMP_SP;
			operation_menu.fan = FAN_TEXT_SP;
			operation_menu.extr = PRINTING_EXTRUDER_SP;
			operation_menu.speed = PRINTING_CHANGESPEED_SP;			
			operation_menu.filament = FILAMENT_TEXT_SP;
			operation_menu.move = PRINTING_MOVE_SP;

			speed_menu.title = PRINTING_CHANGESPEED_SP;
			speed_menu.add = ADD_TEXT_SP;
			speed_menu.dec = DEC_TEXT_SP;
			speed_menu.move = MOVE_SPEED_SP;
			speed_menu.extrude = EXTRUDER_SPEED_SP;
			speed_menu.extrude_speed = EXTRUDER_SPEED_STATE_SP;
			speed_menu.move_speed = MOVE_SPEED_STATE_SP;

			//print_file_dialog_menu.title = TITLE_DIALOG_CONFIRM_SP;
			print_file_dialog_menu.confirm = DIALOG_CONFIRM_SP;
			print_file_dialog_menu.cancle = DIALOG_CANCLE_SP;
			print_file_dialog_menu.print_file = DIALOG_PRINT_MODEL_SP;
			print_file_dialog_menu.cancle_print = DIALOG_CANCEL_PRINT_SP;
			print_file_dialog_menu.retry = DIALOG_RETRY_SP;
			print_file_dialog_menu.stop = DIALOG_STOP_SP;
			print_file_dialog_menu.no_file_print_tips = DIALOG_ERROR_TIPS1_SP;
			print_file_dialog_menu.print_from_breakpoint = DIALOG_REPRINT_FROM_BREAKPOINT_SP;
			print_file_dialog_menu.close_machine_error = DIALOG_ERROR_TIPS2_SP;
            print_file_dialog_menu.filament_no_press = DIALOG_FILAMENT_NO_PRESS_SP;
			print_file_dialog_menu.print_finish = DIALOG_PRINT_FINISH_SP;
			print_file_dialog_menu.print_time = DIALOG_PRINT_TIME_SP;
			print_file_dialog_menu.reprint = DIALOG_REPRINT_SP;
			print_file_dialog_menu.wifi_enable_tips = DIALOG_WIFI_ENABLE_TIPS_SP;

			pause_msg_menu.pausing = MESSEGE_PAUSING_SP;
			pause_msg_menu.changing = MESSEGE_CHANGING_SP;
			pause_msg_menu.unload = MESSEGE_UNLOAD_SP;
			pause_msg_menu.waiting = MESSEGE_WAITING_SP;
			pause_msg_menu.insert = MESSEGE_INSERT_SP;
			pause_msg_menu.load = MESSEGE_LOAD_SP;
			pause_msg_menu.purge = MESSEGE_PURGE_SP;
			pause_msg_menu.resume = MESSEGE_RESUME_SP;
			pause_msg_menu.heat = MESSEGE_HEAT_SP;
			pause_msg_menu.heating = MESSEGE_HEATING_SP;
			pause_msg_menu.option = MESSEGE_OPTION_SP;
			pause_msg_menu.purgeMore = MESSEGE_PURGE_MORE_SP;
			pause_msg_menu.continuePrint = MESSEGE_CONTINUE_PRINT_SP;

			x_mode_menu.title = MODE_INDEX_SP;
			x_mode_menu.fullControl = FULL_CONTROL_SP;
			x_mode_menu.autoPark = AUTO_PARK_SP;
			x_mode_menu.duplication = DUPLICATION_SP;
			x_mode_menu.mirrored = MIRRORED_SP;

			t_offset_menu.title = TOOL_OFFSET_TITLE_SP;
			t_offset_menu.xOffset = TOOL_X_OFSSET_SP;
			t_offset_menu.yOffset = TOOL_Y_OFSSET_SP;
			t_offset_menu.zOffset = TOOL_Z_OFSSET_SP;
			break;

		case LANG_FRENCH:
			common_menu.dialog_confirm_title = TITLE_DIALOG_CONFIRM_FR;
			common_menu.text_back = BACK_TEXT_FR;
			common_menu.close_machine_tips = DIALOG_CLOSE_MACHINE_FR;
			common_menu.unbind_printer_tips = DIALOG_UNBIND_PRINTER_FR;			
			common_menu.print_special_title = PRINTING_OTHER_LANGUGE;
			common_menu.pause_special_title = PRINTING_PAUSE_OTHER_LANGUGE;
			common_menu.operate_special_title = PRINTING_OPERATION_OTHER_LANGUGE;

			main_menu.title = TITLE_READYPRINT_FR;
			main_menu.preheat = PREHEAT_TEXT_FR;
			main_menu.move = MOVE_TEXT_FR;
			main_menu.home = HOME_TEXT_FR;
			main_menu.print = PRINT_TEXT_FR;
			main_menu.extrude = EXTRUDE_TEXT_FR;
			main_menu.leveling = LEVELING_TEXT_FR;
			main_menu.set = SET_TEXT_FR;

			preheat_menu.adjust_title = TITLE_ADJUST_FR;
			preheat_menu.title = TITLE_PREHEAT_FR;
			preheat_menu.add = ADD_TEXT_FR;
			preheat_menu.dec = DEC_TEXT_FR;
			preheat_menu.ext1 = EXTRUDER_1_TEXT_FR;
			preheat_menu.ext2 = EXTRUDER_2_TEXT_FR;
			preheat_menu.hotbed = HEATBED_TEXT_FR;
			preheat_menu.off = CLOSE_TEXT_FR;

			move_menu.title = MOVE_TEXT_FR;

			home_menu.title = TITLE_HOME_FR;
			home_menu.stopmove = HOME_STOPMOVE_FR;

			file_menu.title = TITLE_CHOOSEFILE_FR;
			file_menu.page_up = PAGE_UP_TEXT_FR;
			file_menu.page_down = PAGE_DOWN_TEXT_FR;

			extrude_menu.title = TITLE_EXTRUDE_FR;
			extrude_menu.in = EXTRUDER_IN_TEXT_FR;
			extrude_menu.out = EXTRUDER_OUT_TEXT_FR;
			extrude_menu.ext1 = EXTRUDER_1_TEXT_FR;
			extrude_menu.ext2 = EXTRUDER_2_TEXT_FR;
			extrude_menu.low = EXTRUDE_LOW_SPEED_TEXT_FR;
			extrude_menu.normal = EXTRUDE_MEDIUM_SPEED_TEXT_FR;
			extrude_menu.high = EXTRUDE_HIGH_SPEED_TEXT_FR;
			extrude_menu.temper_text = EXTRUDER_TEMP_TEXT_FR;

			leveling_menu.title = TITLE_LEVELING_FR;
			leveling_menu.position1 = LEVELING_POINT1_TEXT_FR;
			leveling_menu.position2 = LEVELING_POINT2_TEXT_FR;
			leveling_menu.position3 = LEVELING_POINT3_TEXT_FR;
			leveling_menu.position4 = LEVELING_POINT4_TEXT_FR;
			leveling_menu.position5 = LEVELING_POINT5_TEXT_FR;

			set_menu.title = TITLE_SET_FR;
			set_menu.about = ABOUT_TEXT_FR;
			set_menu.fan = FAN_TEXT_FR;
			set_menu.filament = FILAMENT_TEXT_FR;
			set_menu.breakpoint = BREAK_POINT_TEXT_FR;
			set_menu.motoroff = MOTOR_OFF_TEXT_FR;
			set_menu.motoroffXY = MOTOR_OFF_XY_TEXT_FR;
			set_menu.language = LANGUAGE_TEXT_FR;
			set_menu.shutdown = SHUTDOWN_TEXT_FR;
			set_menu.Xmode = X_MODE_TEXT_FR;
			set_menu.eepromSet = EEPROM_SETTINGS_FR;
			set_menu.eepromTitle = EEPROM_SETTINGS_TITLE_FR;
			set_menu.revert = EEPROM_SETTINGS_REVERT_FR;
			set_menu.revertTips =  EEPROM_REVERT_TIPS_FR;
			set_menu.Toffset = TOOL_OFFSET_FR;

			file_menu.file_loading = FILE_LOADING_FR;
			file_menu.no_file = NO_FILE_FR;
			file_menu.no_file_and_check = NO_FILE_FR;//NO_FILE_AND_CHECK_FR;				

			about_menu.title = ABOUT_TEXT_FR;
			about_menu.type = ABOUT_TYPE_TEXT_FR;
			about_menu.version = ABOUT_VERSION_TEXT_FR;				

			fan_menu.title = FAN_TEXT_FR;
			fan_menu.add = FAN_ADD_TEXT_FR;
			fan_menu.dec = FAN_DEC_TEXT_FR;
			fan_menu.state = FAN_TIPS1_TEXT_FR;

			filament_menu.title = TITLE_FILAMENT_FR;
			filament_menu.in = FILAMENT_IN_TEXT_FR;
			filament_menu.out = FILAMENT_OUT_TEXT_FR;
			filament_menu.ext1 = FILAMENT_EXT0_TEXT_FR;
			filament_menu.ext2 = FILAMENT_EXT1_TEXT_FR;
			filament_menu.ready_replace = FILAMENT_CHANGE_TEXT_FR;
			filament_menu.filament_dialog_load_heat = FILAMENT_DIALOG_LOAD_HEAT_TIPS_FR;
			filament_menu.filament_dialog_load_heat_confirm = FILAMENT_DIALOG_LOAD_CONFIRM1_TIPS_FR;
			filament_menu.filament_dialog_loading = FILAMENT_DIALOG_LOADING_TIPS_FR;
			filament_menu.filament_dialog_load_completed = FILAMENT_DIALOG_LOAD_COMPLETE_TIPS_FR;
			filament_menu.filament_dialog_unload_heat = FILAMENT_DIALOG_UNLOAD_HEAT_TIPS_FR;
			filament_menu.filament_dialog_unload_heat_confirm = FILAMENT_DIALOG_UNLOAD_CONFIRM_TIPS_FR;
			filament_menu.filament_dialog_unloading = FILAMENT_DIALOG_UNLOADING_TIPS_FR;
			filament_menu.filament_dialog_unload_completed = FILAMENT_DIALOG_UNLOAD_COMPLETE_TIPS_FR;

			language_menu.title = LANGUAGE_TEXT_FR;
			
			printing_menu.title = TITLE_PRINTING_FR;
			printing_menu.option = PRINTING_OPERATION_FR;
			printing_menu.stop = PRINTING_STOP_FR;
			printing_menu.pause = PRINTING_PAUSE_FR;
			printing_menu.resume = PRINTING_RESUME_FR;

			operation_menu.title = TITLE_OPERATION_FR;
			operation_menu.pause = PRINTING_PAUSE_FR;
			operation_menu.stop = PRINTING_STOP_FR;
			operation_menu.temp = PRINTING_TEMP_FR;
			operation_menu.fan = FAN_TEXT_FR;
			operation_menu.extr = PRINTING_EXTRUDER_FR;
			operation_menu.speed = PRINTING_CHANGESPEED_FR;
			operation_menu.filament = FILAMENT_TEXT_FR;
			operation_menu.move = PRINTING_MOVE_FR;	

			speed_menu.title = PRINTING_CHANGESPEED_FR;
			speed_menu.add = ADD_TEXT_FR;
			speed_menu.dec = DEC_TEXT_FR;
			speed_menu.move = MOVE_SPEED_FR;
			speed_menu.extrude = EXTRUDER_SPEED_FR;
			speed_menu.extrude_speed = EXTRUDER_SPEED_STATE_FR;
			speed_menu.move_speed = MOVE_SPEED_STATE_FR;

			//print_file_dialog_menu.title = TITLE_DIALOG_CONFIRM_SP;
			print_file_dialog_menu.confirm = DIALOG_CONFIRM_FR;
			print_file_dialog_menu.cancle = DIALOG_CANCLE_FR;
			print_file_dialog_menu.print_file = DIALOG_PRINT_MODEL_FR;
			print_file_dialog_menu.cancle_print = DIALOG_CANCEL_PRINT_FR;
			print_file_dialog_menu.retry = DIALOG_RETRY_FR;
			print_file_dialog_menu.stop = DIALOG_STOP_FR;
			print_file_dialog_menu.no_file_print_tips = DIALOG_ERROR_TIPS1_FR;
			print_file_dialog_menu.print_from_breakpoint = DIALOG_REPRINT_FROM_BREAKPOINT_FR;		
			print_file_dialog_menu.close_machine_error = DIALOG_ERROR_TIPS2_FR;
            print_file_dialog_menu.filament_no_press = DIALOG_FILAMENT_NO_PRESS_FR;
			print_file_dialog_menu.print_finish = DIALOG_PRINT_FINISH_FR;
			print_file_dialog_menu.print_time = DIALOG_PRINT_TIME_FR;
			print_file_dialog_menu.reprint = DIALOG_REPRINT_FR;
			print_file_dialog_menu.wifi_enable_tips = DIALOG_WIFI_ENABLE_TIPS_FR;

			pause_msg_menu.pausing = MESSEGE_PAUSING_FR;
			pause_msg_menu.changing = MESSEGE_CHANGING_FR;
			pause_msg_menu.unload = MESSEGE_UNLOAD_FR;
			pause_msg_menu.waiting = MESSEGE_WAITING_FR;
			pause_msg_menu.insert = MESSEGE_INSERT_FR;
			pause_msg_menu.load = MESSEGE_LOAD_FR;
			pause_msg_menu.purge = MESSEGE_PURGE_FR;
			pause_msg_menu.resume = MESSEGE_RESUME_FR;
			pause_msg_menu.heat = MESSEGE_HEAT_FR;
			pause_msg_menu.heating = MESSEGE_HEATING_FR;
			pause_msg_menu.option = MESSEGE_OPTION_FR;
			pause_msg_menu.purgeMore = MESSEGE_PURGE_MORE_FR;
			pause_msg_menu.continuePrint = MESSEGE_CONTINUE_PRINT_FR;

			x_mode_menu.title = MODE_INDEX_FR;
			x_mode_menu.fullControl = FULL_CONTROL_FR;
			x_mode_menu.autoPark = AUTO_PARK_FR;
			x_mode_menu.duplication = DUPLICATION_FR;
			x_mode_menu.mirrored = MIRRORED_FR;

			t_offset_menu.title = TOOL_OFFSET_TITLE_FR;
			t_offset_menu.xOffset = TOOL_X_OFSSET_FR;
			t_offset_menu.yOffset = TOOL_Y_OFSSET_FR;
			t_offset_menu.zOffset = TOOL_Z_OFSSET_FR;
			break;
			
		case LANG_ITALY:
			common_menu.dialog_confirm_title = TITLE_DIALOG_CONFIRM_IT;
			common_menu.text_back = BACK_TEXT_IT;
			common_menu.close_machine_tips = DIALOG_CLOSE_MACHINE_IT;
			common_menu.unbind_printer_tips = DIALOG_UNBIND_PRINTER_IT;
			common_menu.print_special_title = PRINTING_OTHER_LANGUGE;
			common_menu.pause_special_title = PRINTING_PAUSE_OTHER_LANGUGE;
			common_menu.operate_special_title = PRINTING_OPERATION_OTHER_LANGUGE;

			main_menu.title = TITLE_READYPRINT_IT;
			main_menu.preheat = PREHEAT_TEXT_IT;
			main_menu.move = MOVE_TEXT_IT;
			main_menu.home = HOME_TEXT_IT;
			main_menu.print = PRINT_TEXT_IT;
			main_menu.extrude = EXTRUDE_TEXT_IT;
			main_menu.leveling = LEVELING_TEXT_IT;
			main_menu.set = SET_TEXT_IT;

			preheat_menu.adjust_title = TITLE_ADJUST_IT;
			preheat_menu.title = TITLE_PREHEAT_IT;
			preheat_menu.add = ADD_TEXT_IT;
			preheat_menu.dec = DEC_TEXT_IT;
			preheat_menu.ext1 = EXTRUDER_1_TEXT_IT;
			preheat_menu.ext2 = EXTRUDER_2_TEXT_IT;
			preheat_menu.hotbed = HEATBED_TEXT_IT;
			preheat_menu.off = CLOSE_TEXT_IT;

			move_menu.title = MOVE_TEXT_IT;

			home_menu.title = TITLE_HOME_IT;
			home_menu.stopmove = HOME_STOPMOVE_IT;

			file_menu.title = TITLE_CHOOSEFILE_IT;
			file_menu.page_up = PAGE_UP_TEXT_IT;
			file_menu.page_down = PAGE_DOWN_TEXT_IT;
			file_menu.file_loading = FILE_LOADING_IT;
			file_menu.no_file = NO_FILE_IT;
			file_menu.no_file_and_check = NO_FILE_IT;//NO_FILE_AND_CHECK_IT;				

			extrude_menu.title = TITLE_EXTRUDE_IT;
			extrude_menu.in = EXTRUDER_IN_TEXT_IT;
			extrude_menu.out = EXTRUDER_OUT_TEXT_IT;
			extrude_menu.ext1 = EXTRUDER_1_TEXT_IT;
			extrude_menu.ext2 = EXTRUDER_2_TEXT_IT;
			extrude_menu.low = EXTRUDE_LOW_SPEED_TEXT_IT;
			extrude_menu.normal = EXTRUDE_MEDIUM_SPEED_TEXT_IT;
			extrude_menu.high = EXTRUDE_HIGH_SPEED_TEXT_IT;
			extrude_menu.temper_text = EXTRUDER_TEMP_TEXT_IT;

			leveling_menu.title = TITLE_LEVELING_IT;
			leveling_menu.position1 = LEVELING_POINT1_TEXT_IT;
			leveling_menu.position2 = LEVELING_POINT2_TEXT_IT;
			leveling_menu.position3 = LEVELING_POINT3_TEXT_IT;
			leveling_menu.position4 = LEVELING_POINT4_TEXT_IT;
			leveling_menu.position5 = LEVELING_POINT5_TEXT_IT;

			set_menu.title = TITLE_SET_IT;
			set_menu.about = ABOUT_TEXT_IT;
			set_menu.fan = FAN_TEXT_IT;
			set_menu.filament = FILAMENT_TEXT_IT;
			set_menu.breakpoint = BREAK_POINT_TEXT_IT;
			set_menu.motoroff = MOTOR_OFF_TEXT_IT;
			set_menu.motoroffXY = MOTOR_OFF_XY_TEXT_IT;
			set_menu.language = LANGUAGE_TEXT_IT;
			set_menu.shutdown = SHUTDOWN_TEXT_IT;
			set_menu.Xmode = X_MODE_TEXT_IT;
			set_menu.eepromSet = EEPROM_SETTINGS_IT;
			set_menu.eepromTitle = EEPROM_SETTINGS_TITLE_IT;
			set_menu.revert = EEPROM_SETTINGS_REVERT_IT;
			set_menu.revertTips =  EEPROM_REVERT_TIPS_IT;
			set_menu.Toffset = TOOL_OFFSET_IT;

			about_menu.title = ABOUT_TEXT_IT;
			about_menu.type = ABOUT_TYPE_TEXT_IT;
			about_menu.version = ABOUT_VERSION_TEXT_IT;				

			fan_menu.title = FAN_TEXT_IT;
			fan_menu.add = FAN_ADD_TEXT_IT;
			fan_menu.dec = FAN_DEC_TEXT_IT;
			fan_menu.state = FAN_TIPS1_TEXT_IT;

			filament_menu.title = TITLE_FILAMENT_IT;
			filament_menu.in = FILAMENT_IN_TEXT_IT;
			filament_menu.out = FILAMENT_OUT_TEXT_IT;
			filament_menu.ext1 = FILAMENT_EXT0_TEXT_IT;
			filament_menu.ext2 = FILAMENT_EXT1_TEXT_IT;
			filament_menu.ready_replace = FILAMENT_CHANGE_TEXT_IT;
			filament_menu.filament_dialog_load_heat = FILAMENT_DIALOG_LOAD_HEAT_TIPS_IT;
			filament_menu.filament_dialog_load_heat_confirm = FILAMENT_DIALOG_LOAD_CONFIRM1_TIPS_IT;
			filament_menu.filament_dialog_loading = FILAMENT_DIALOG_LOADING_TIPS_IT;
			filament_menu.filament_dialog_load_completed = FILAMENT_DIALOG_LOAD_COMPLETE_TIPS_IT;
			filament_menu.filament_dialog_unload_heat = FILAMENT_DIALOG_UNLOAD_HEAT_TIPS_IT;
			filament_menu.filament_dialog_unload_heat_confirm = FILAMENT_DIALOG_UNLOAD_CONFIRM_TIPS_IT;
			filament_menu.filament_dialog_unloading = FILAMENT_DIALOG_UNLOADING_TIPS_IT;
			filament_menu.filament_dialog_unload_completed = FILAMENT_DIALOG_UNLOAD_COMPLETE_TIPS_IT;

			language_menu.title = LANGUAGE_TEXT_IT;

			printing_menu.title = TITLE_PRINTING_IT;
			printing_menu.option = PRINTING_OPERATION_IT;
			printing_menu.stop = PRINTING_STOP_IT;
			printing_menu.pause = PRINTING_PAUSE_IT;
			printing_menu.resume = PRINTING_RESUME_IT;

			operation_menu.title = TITLE_OPERATION_IT;
			operation_menu.pause = PRINTING_PAUSE_IT;
			operation_menu.stop = PRINTING_STOP_IT;
			operation_menu.temp = PRINTING_TEMP_IT;
			operation_menu.fan = FAN_TEXT_IT;
			operation_menu.extr = PRINTING_EXTRUDER_IT;
			operation_menu.speed = PRINTING_CHANGESPEED_IT;			
			operation_menu.filament = FILAMENT_TEXT_IT;
			operation_menu.move = PRINTING_MOVE_IT;

			speed_menu.title = PRINTING_CHANGESPEED_IT;
			speed_menu.add = ADD_TEXT_IT;
			speed_menu.dec = DEC_TEXT_IT;
			speed_menu.move = MOVE_SPEED_IT;
			speed_menu.extrude = EXTRUDER_SPEED_IT;
			speed_menu.extrude_speed = EXTRUDER_SPEED_STATE_IT;
			speed_menu.move_speed = MOVE_SPEED_STATE_IT;

			//print_file_dialog_menu.title = TITLE_DIALOG_CONFIRM_SP;
			print_file_dialog_menu.confirm = DIALOG_CONFIRM_IT;
			print_file_dialog_menu.cancle = DIALOG_CANCLE_IT;
			print_file_dialog_menu.print_file = DIALOG_PRINT_MODEL_IT;
			print_file_dialog_menu.cancle_print = DIALOG_CANCEL_PRINT_IT;
			print_file_dialog_menu.retry = DIALOG_RETRY_IT;
			print_file_dialog_menu.stop = DIALOG_STOP_IT;
			print_file_dialog_menu.no_file_print_tips = DIALOG_ERROR_TIPS1_IT;
			print_file_dialog_menu.print_from_breakpoint = DIALOG_REPRINT_FROM_BREAKPOINT_IT;
			print_file_dialog_menu.close_machine_error = DIALOG_ERROR_TIPS2_IT;
            print_file_dialog_menu.filament_no_press = DIALOG_FILAMENT_NO_PRESS_IT;
			print_file_dialog_menu.print_finish = DIALOG_PRINT_FINISH_IT;
			print_file_dialog_menu.print_time = DIALOG_PRINT_TIME_IT;
			print_file_dialog_menu.reprint = DIALOG_REPRINT_IT;
			print_file_dialog_menu.wifi_enable_tips = DIALOG_WIFI_ENABLE_TIPS_IT;

			pause_msg_menu.pausing = MESSEGE_PAUSING_IT;
			pause_msg_menu.changing = MESSEGE_CHANGING_IT;
			pause_msg_menu.unload = MESSEGE_UNLOAD_IT;
			pause_msg_menu.waiting = MESSEGE_WAITING_IT;
			pause_msg_menu.insert = MESSEGE_INSERT_IT;
			pause_msg_menu.load = MESSEGE_LOAD_IT;
			pause_msg_menu.purge = MESSEGE_PURGE_IT;
			pause_msg_menu.resume = MESSEGE_RESUME_IT;
			pause_msg_menu.heat = MESSEGE_HEAT_IT;
			pause_msg_menu.heating = MESSEGE_HEATING_IT;
			pause_msg_menu.option = MESSEGE_OPTION_IT;
			pause_msg_menu.purgeMore = MESSEGE_PURGE_MORE_IT;
			pause_msg_menu.continuePrint = MESSEGE_CONTINUE_PRINT_IT;

			x_mode_menu.title = MODE_INDEX_IT;
			x_mode_menu.fullControl = FULL_CONTROL_IT;
			x_mode_menu.autoPark = AUTO_PARK_IT;
			x_mode_menu.duplication = DUPLICATION_IT;
			x_mode_menu.mirrored = MIRRORED_IT;

			t_offset_menu.title = TOOL_OFFSET_TITLE_IT;
			t_offset_menu.xOffset = TOOL_X_OFSSET_IT;
			t_offset_menu.yOffset = TOOL_Y_OFSSET_IT;
			t_offset_menu.zOffset = TOOL_Z_OFSSET_IT;
			break;
     
		default:
			common_menu.dialog_confirm_title = TITLE_DIALOG_CONFIRM_EN;
			common_menu.text_back = BACK_TEXT_EN;
			common_menu.close_machine_tips = DIALOG_CLOSE_MACHINE_EN;
			common_menu.unbind_printer_tips = DIALOG_UNBIND_PRINTER_EN;
			common_menu.print_special_title = PRINTING_OTHER_LANGUGE;
			common_menu.pause_special_title = PRINTING_PAUSE_OTHER_LANGUGE;
			common_menu.operate_special_title = PRINTING_OPERATION_OTHER_LANGUGE;			

			main_menu.title = TITLE_READYPRINT_EN;
			main_menu.preheat = PREHEAT_TEXT_EN;
			main_menu.move = MOVE_TEXT_EN;
			main_menu.home = HOME_TEXT_EN;
			main_menu.print = PRINT_TEXT_EN;
			main_menu.extrude = EXTRUDE_TEXT_EN;
			main_menu.leveling = LEVELING_TEXT_EN;
			main_menu.set = SET_TEXT_EN;

			preheat_menu.adjust_title = TITLE_ADJUST_EN;
			preheat_menu.title = TITLE_PREHEAT_EN;
			preheat_menu.add = ADD_TEXT_EN;
			preheat_menu.dec = DEC_TEXT_EN;
			preheat_menu.ext1 = EXTRUDER_1_TEXT_EN;
			preheat_menu.ext2 = EXTRUDER_2_TEXT_EN;
			preheat_menu.hotbed = HEATBED_TEXT_EN;
			preheat_menu.off = CLOSE_TEXT_EN;

			move_menu.title = TITLE_MOVE_EN;

			home_menu.title = TITLE_HOME_EN;
			home_menu.stopmove = HOME_STOPMOVE_EN;

			file_menu.title = TITLE_CHOOSEFILE_EN;
			file_menu.page_up = PAGE_UP_TEXT_EN;
			file_menu.page_down = PAGE_DOWN_TEXT_EN;
			file_menu.file_loading = FILE_LOADING_EN;
			file_menu.no_file = NO_FILE_EN;
			file_menu.no_file_and_check = NO_FILE_EN;//NO_FILE_AND_CHECK_EN;			

			extrude_menu.title = TITLE_EXTRUDE_EN;
			extrude_menu.in = EXTRUDER_IN_TEXT_EN;
			extrude_menu.out = EXTRUDER_OUT_TEXT_EN;
			extrude_menu.ext1 = EXTRUDER_1_TEXT_EN;
			extrude_menu.ext2 = EXTRUDER_2_TEXT_EN;
			extrude_menu.low = EXTRUDE_LOW_SPEED_TEXT_EN;
			extrude_menu.normal = EXTRUDE_MEDIUM_SPEED_TEXT_EN;
			extrude_menu.high = EXTRUDE_HIGH_SPEED_TEXT_EN;
			extrude_menu.temper_text = EXTRUDER_TEMP_TEXT_EN;

			leveling_menu.title = TITLE_LEVELING_EN;
			leveling_menu.position1 = LEVELING_POINT1_TEXT_EN;
			leveling_menu.position2 = LEVELING_POINT2_TEXT_EN;
			leveling_menu.position3 = LEVELING_POINT3_TEXT_EN;
			leveling_menu.position4 = LEVELING_POINT4_TEXT_EN;
			leveling_menu.position5 = LEVELING_POINT5_TEXT_EN;

			set_menu.title = TITLE_SET_EN;
			set_menu.about = ABOUT_TEXT_EN;
			set_menu.fan = FAN_TEXT_EN;
			set_menu.filament = FILAMENT_TEXT_EN;
			set_menu.breakpoint = BREAK_POINT_TEXT_EN;
			set_menu.motoroff = MOTOR_OFF_TEXT_EN;
			set_menu.motoroffXY = MOTOR_OFF_XY_TEXT_EN;
			set_menu.language = LANGUAGE_TEXT_EN;
			set_menu.shutdown = SHUTDOWN_TEXT_EN;
			set_menu.Xmode = X_MODE_TEXT_EN;
            set_menu.eepromSet = EEPROM_SETTINGS_EN;
			set_menu.eepromTitle = EEPROM_SETTINGS_TITLE_EN;
			set_menu.revert = EEPROM_SETTINGS_REVERT_EN;
			set_menu.revertTips =  EEPROM_REVERT_TIPS_EN;
			set_menu.Toffset = TOOL_OFFSET_EN;

			about_menu.title = TITLE_ABOUT_EN;
			about_menu.type = ABOUT_TYPE_TEXT_EN;
			about_menu.version = ABOUT_VERSION_TEXT_EN;		

			fan_menu.title = TITLE_FAN_EN;
			fan_menu.add = FAN_ADD_TEXT_EN;
			fan_menu.dec = FAN_DEC_TEXT_EN;
			fan_menu.state = FAN_TIPS1_TEXT_EN;

			filament_menu.title = TITLE_FILAMENT_EN;
			filament_menu.in = FILAMENT_IN_TEXT_EN;
			filament_menu.out = FILAMENT_OUT_TEXT_EN;
			filament_menu.ext1 = FILAMENT_EXT0_TEXT_EN;
			filament_menu.ext2 = FILAMENT_EXT1_TEXT_EN;
			filament_menu.ready_replace = FILAMENT_CHANGE_TEXT_EN;
			filament_menu.filament_dialog_load_heat = FILAMENT_DIALOG_LOAD_HEAT_TIPS_EN;
			filament_menu.filament_dialog_load_heat_confirm = FILAMENT_DIALOG_LOAD_CONFIRM1_TIPS_EN;
			filament_menu.filament_dialog_loading = FILAMENT_DIALOG_LOADING_TIPS_EN;
			filament_menu.filament_dialog_load_completed = FILAMENT_DIALOG_LOAD_COMPLETE_TIPS_EN;
			filament_menu.filament_dialog_unload_heat = FILAMENT_DIALOG_UNLOAD_HEAT_TIPS_EN;
			filament_menu.filament_dialog_unload_heat_confirm = FILAMENT_DIALOG_UNLOAD_CONFIRM_TIPS_EN;
			filament_menu.filament_dialog_unloading = FILAMENT_DIALOG_UNLOADING_TIPS_EN;
			filament_menu.filament_dialog_unload_completed = FILAMENT_DIALOG_UNLOAD_COMPLETE_TIPS_EN;

			language_menu.title = TITLE_LANGUAGE_EN;		

			printing_menu.title = TITLE_PRINTING_EN;
			printing_menu.option = PRINTING_OPERATION_EN;
			printing_menu.stop = PRINTING_STOP_EN;
			printing_menu.pause = PRINTING_PAUSE_EN;
			printing_menu.resume = PRINTING_RESUME_EN;

			operation_menu.title = TITLE_OPERATION_EN;
			operation_menu.pause = PRINTING_PAUSE_EN;
			operation_menu.stop = PRINTING_STOP_EN;
			operation_menu.temp = PRINTING_TEMP_EN;
			operation_menu.fan = FAN_TEXT_EN;
			operation_menu.extr = PRINTING_EXTRUDER_EN;
			operation_menu.speed = PRINTING_CHANGESPEED_EN;			
			operation_menu.filament= FILAMENT_TEXT_EN;
			operation_menu.move = PRINTING_MOVE_EN;	

			speed_menu.title = TITLE_CHANGESPEED_EN;
			speed_menu.add = ADD_TEXT_EN;
			speed_menu.dec = DEC_TEXT_EN;
			speed_menu.move = MOVE_SPEED_EN;
			speed_menu.extrude = EXTRUDER_SPEED_EN;
			speed_menu.extrude_speed = EXTRUDER_SPEED_STATE_EN;
			speed_menu.move_speed = MOVE_SPEED_STATE_EN;

			//print_file_dialog_menu.title = TITLE_DIALOG_CONFIRM_EN;
			print_file_dialog_menu.confirm = DIALOG_CONFIRM_EN;
			print_file_dialog_menu.cancle = DIALOG_CANCLE_EN;
			print_file_dialog_menu.print_file = DIALOG_PRINT_MODEL_EN;
			print_file_dialog_menu.cancle_print = DIALOG_CANCEL_PRINT_EN;
			print_file_dialog_menu.retry = DIALOG_RETRY_EN;
			print_file_dialog_menu.stop = DIALOG_STOP_EN;
			print_file_dialog_menu.no_file_print_tips = DIALOG_ERROR_TIPS1_EN;	
			print_file_dialog_menu.print_from_breakpoint = DIALOG_REPRINT_FROM_BREAKPOINT_EN;
			print_file_dialog_menu.close_machine_error = DIALOG_ERROR_TIPS2_EN;
            print_file_dialog_menu.filament_no_press = DIALOG_FILAMENT_NO_PRESS_EN;
			print_file_dialog_menu.print_finish = DIALOG_PRINT_FINISH_EN;
			print_file_dialog_menu.print_time = DIALOG_PRINT_TIME_EN;
			print_file_dialog_menu.reprint = DIALOG_REPRINT_EN;
			print_file_dialog_menu.wifi_enable_tips = DIALOG_WIFI_ENABLE_TIPS_EN;

			pause_msg_menu.pausing = MESSEGE_PAUSING_EN;
			pause_msg_menu.changing = MESSEGE_CHANGING_EN;
			pause_msg_menu.unload = MESSEGE_UNLOAD_EN;
			pause_msg_menu.waiting = MESSEGE_WAITING_EN;
			pause_msg_menu.insert = MESSEGE_INSERT_EN;
			pause_msg_menu.load = MESSEGE_LOAD_EN;
			pause_msg_menu.purge = MESSEGE_PURGE_EN;
			pause_msg_menu.resume = MESSEGE_RESUME_EN;
			pause_msg_menu.heat = MESSEGE_HEAT_EN;
			pause_msg_menu.heating = MESSEGE_HEATING_EN;
			pause_msg_menu.option = MESSEGE_OPTION_EN;
			pause_msg_menu.purgeMore = MESSEGE_PURGE_MORE_EN;
			pause_msg_menu.continuePrint = MESSEGE_CONTINUE_PRINT_EN;

			x_mode_menu.title = MODE_INDEX_EN;
			x_mode_menu.fullControl = FULL_CONTROL_EN;
			x_mode_menu.autoPark = AUTO_PARK_EN;
			x_mode_menu.duplication = DUPLICATION_EN;
			x_mode_menu.mirrored = MIRRORED_EN;

			t_offset_menu.title = TOOL_OFFSET_TITLE_EN;
			t_offset_menu.xOffset = TOOL_X_OFSSET_EN;
			t_offset_menu.yOffset = TOOL_Y_OFSSET_EN;
			t_offset_menu.zOffset = TOOL_Z_OFSSET_EN;
			break;
	}
}

#endif
