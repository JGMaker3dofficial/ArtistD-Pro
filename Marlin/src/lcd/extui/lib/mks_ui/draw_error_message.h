#ifndef _LV_DRAW_ERROR_MESSAGE_
#define _LV_DRAW_ERROR_MESSAGE_


#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

#ifndef PGM_P
  #define PGM_P const char *
#endif

extern void lv_draw_error_message(PGM_P const msg);
extern void lv_clear_error_message(void);

//extern void disp_temp_ready_print();
#if defined(__cplusplus)
}    /* Make sure we have C-declarations in C++ programs */
#endif

#endif
