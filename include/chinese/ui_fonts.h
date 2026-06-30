#ifndef CHINESE_UI_FONTS_H
#define CHINESE_UI_FONTS_H

#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

void ui_fonts_init(void);
const lv_font_t *ui_font_zh_12(void);
const lv_font_t *ui_font_zh_16(void);

#ifdef __cplusplus
}
#endif

#endif
