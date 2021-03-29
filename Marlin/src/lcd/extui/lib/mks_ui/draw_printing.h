#ifndef _LV_DRAW_PRINTING_
#define _LV_DRAW_PRINTING_


#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

#define IDLE			0
#define WORKING			1
#define PAUSED			2		
#define REPRINTING		3
#define REPRINTED		4
#define STOP			5

extern void lv_draw_printing(void);
extern void lv_clear_printing(void);
extern void disp_ext_temp(void);
extern void disp_bed_temp(void);
extern void disp_fan_speed(void);
extern void disp_print_time(void);
extern void disp_fan_Zpos(void);
extern void reset_print_time(void);
extern void start_print_time(void);
extern void stop_print_time(void);
extern void setProBarRate(void);

//extern void disp_temp_ready_print();
#if defined(__cplusplus)
}    /* Make sure we have C-declarations in C++ programs */
#endif

#endif
