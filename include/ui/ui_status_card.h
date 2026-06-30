#ifndef UI_STATUS_CARD_H
#define UI_STATUS_CARD_H

#include "lvgl.h"

static lv_obj_t *ui_create_status_card(lv_obj_t *parent,
                                       int x,
                                       int y,
                                       int w,
                                       int h,
                                       const char *icon_text,
                                       const char *title_text,
                                       const char *value_text,
                                       lv_color_t main_color,
                                       lv_color_t light_color);

void ui_create_status_overview(lv_obj_t *parent);

#endif