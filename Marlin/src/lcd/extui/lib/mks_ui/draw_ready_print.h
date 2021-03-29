#ifndef _LV_DRAW_READY_PRINT_
#define _LV_DRAW_READY_PRINT_


#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

extern void lv_draw_ready_print(uint8_t state);
extern void disp_test(void);
extern void disp_Limit_ok(void);
extern void disp_Limit_error(void);
extern void disp_det_error(void);
extern void disp_det_ok(void);
extern void lv_clear_ready_print(void);

//extern void disp_temp_ready_print();
#if defined(__cplusplus)
}    /* Make sure we have C-declarations in C++ programs */
#endif

#endif
