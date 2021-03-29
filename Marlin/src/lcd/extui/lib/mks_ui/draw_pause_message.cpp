#include "../../../../MarlinCore.h"
#if ENABLED(TFT_LITTLE_VGL_UI)
#include "draw_ui.h"
#if ENABLED(ADVANCED_PAUSE_FEATURE)
#include "../../../../feature/pause.h"


extern uint8_t flash_preview_begin;
extern uint8_t default_preview_flg;

void lv_draw_pause_message(const PauseMessage msg)
{
    switch (msg) {
    case PAUSE_MESSAGE_PAUSING:  clear_cur_ui();lv_draw_dialog(DIALOG_PAUSE_MESSAGE_PAUSING);break;
    case PAUSE_MESSAGE_CHANGING: clear_cur_ui();lv_draw_dialog(DIALOG_PAUSE_MESSAGE_CHANGING);break;
    case PAUSE_MESSAGE_UNLOAD:   clear_cur_ui();lv_draw_dialog(DIALOG_PAUSE_MESSAGE_UNLOAD);break;
    case PAUSE_MESSAGE_WAITING:  clear_cur_ui();lv_draw_dialog(DIALOG_PAUSE_MESSAGE_WAITING);break;
    case PAUSE_MESSAGE_INSERT:   clear_cur_ui();lv_draw_dialog(DIALOG_PAUSE_MESSAGE_INSERT);break;
    case PAUSE_MESSAGE_LOAD:     clear_cur_ui();lv_draw_dialog(DIALOG_PAUSE_MESSAGE_LOAD);break;
    case PAUSE_MESSAGE_PURGE:    clear_cur_ui();lv_draw_dialog(DIALOG_PAUSE_MESSAGE_PURGE);break;
    case PAUSE_MESSAGE_RESUME:   
      clear_cur_ui();
      /*lv_draw_dialog(DIALOG_PAUSE_MESSAGE_RESUME);*/
      if(gCfgItems.from_flash_pic == 1)
        flash_preview_begin = 1;
      else
        default_preview_flg = 1;
      lv_draw_printing();
      break;
    case PAUSE_MESSAGE_HEAT:     clear_cur_ui();lv_draw_dialog(DIALOG_PAUSE_MESSAGE_HEAT);break;
    case PAUSE_MESSAGE_HEATING:  clear_cur_ui();lv_draw_dialog(DIALOG_PAUSE_MESSAGE_HEATING);break;
    case PAUSE_MESSAGE_OPTION:   pause_menu_response = PAUSE_RESPONSE_WAIT_FOR;
                                 clear_cur_ui();lv_draw_dialog(DIALOG_PAUSE_MESSAGE_OPTION);break;
    case PAUSE_MESSAGE_STATUS:
    default: break;
  }
}
#endif

#endif
