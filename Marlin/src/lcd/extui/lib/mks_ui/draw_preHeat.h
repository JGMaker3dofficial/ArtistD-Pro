#ifndef _LV_DRAW_PREHEAT_
#define _LV_DRAW_PREHEAT_


#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

extern void lv_draw_preHeat(void);
extern void lv_clear_preHeat(void);
extern void disp_temp_type(void);
extern void disp_step_heat(void);
extern void disp_desire_temp(void);


//extern void disp_temp_ready_print();
#if defined(__cplusplus)
}    /* Make sure we have C-declarations in C++ programs */
#endif

#endif
