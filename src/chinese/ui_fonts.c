#include "chinese/ui_fonts.h"

#include "lvgl.h"

LV_FONT_DECLARE(font_chinese_16);
LV_FONT_DECLARE(font_chinese_12);

void ui_fonts_init(void)
{
}

const lv_font_t *ui_font_zh_16(void)
{
    return &font_chinese_16;
}

const lv_font_t *ui_font_zh_12(void)
{
    return &font_chinese_12;
}
