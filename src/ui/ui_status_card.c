#include "lvgl.h"
#include "chinese/ui_fonts.h"

static lv_obj_t *g_label_device_status = NULL;
static lv_obj_t *g_label_alarm_status  = NULL;
static lv_obj_t *g_label_slot_count    = NULL;
static lv_obj_t *g_label_today_order   = NULL;




/*创建单个卡片函数*/
static lv_obj_t *ui_create_status_card(lv_obj_t *parent,
                                       int x,
                                       int y,
                                       int w,
                                       int h,
                                       const char *icon_text,
                                       const char *title_text,
                                       const char *value_text,
                                       lv_color_t main_color,
                                       lv_color_t light_color)
{
    /*卡片容器*/
    lv_obj_t *card = lv_obj_create(parent);
    lv_obj_set_size(card, w, h);
    lv_obj_set_pos(card, x, y);

    lv_obj_set_style_bg_color(card, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_bg_opa(card, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(card, 8, 0);
    lv_obj_set_style_border_width(card, 1, 0);
    lv_obj_set_style_border_color(card, lv_color_hex(0xE5EAF2), 0);
    lv_obj_set_style_shadow_width(card, 6, 0);
    lv_obj_set_style_shadow_opa(card, LV_OPA_10, 0);
    lv_obj_set_style_shadow_color(card, lv_color_hex(0x94A3B8), 0);
    lv_obj_set_style_pad_all(card, 0, 0);

    /*左侧圆形浅色背景*/    
    lv_obj_t *icon_bg = lv_obj_create(card);
    lv_obj_set_size(icon_bg, 44, 44);
    lv_obj_set_pos(icon_bg, 18, 12);

    lv_obj_set_style_bg_color(icon_bg, light_color, 0);
    lv_obj_set_style_bg_opa(icon_bg, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(icon_bg, 22, 0);
    lv_obj_set_style_border_width(icon_bg, 0, 0);
    lv_obj_set_style_pad_all(icon_bg, 0, 0);

    /*左侧图标*/
    lv_obj_t *icon = lv_label_create(icon_bg);
    lv_label_set_text(icon, icon_text);
    lv_obj_set_style_text_color(icon, main_color, 0);
    lv_obj_set_style_text_font(icon, &lv_font_montserrat_16, 0);
    lv_obj_center(icon);

    /*标题*/
    lv_obj_t *title = lv_label_create(card);
    lv_label_set_text(title, title_text);
    lv_obj_set_pos(title, 82, 15);
    lv_obj_set_style_text_color(title, lv_color_hex(0x475569), 0);
    lv_obj_set_style_text_font(title, ui_font_zh_16(), 0);

    /*状态值*/
    lv_obj_t *value = lv_label_create(card);
    lv_label_set_text(value, value_text);
    lv_obj_set_pos(value, 82, 38);
    lv_obj_set_style_text_color(value, main_color, 0);
    lv_obj_set_style_text_font(value, ui_font_zh_16(), 0);

    return value;
}

/*创建四个卡片函数*/
void ui_create_status_overview(lv_obj_t *parent)
{
    int y = 70;
    int card_w = 185;
    int card_h = 70;
    int gap = 10;

    int x1 = 18;
    int x2 = x1 + card_w + gap;
    int x3 = x2 + card_w + gap;
    int x4 = x3 + card_w + gap;

    /*
     * 设备状态
     */
    g_label_device_status = ui_create_status_card(parent,
                                                  x1,
                                                  y,
                                                  card_w,
                                                  card_h,
                                                  LV_SYMBOL_CHARGE,
                                                  "设备状态",
                                                  "运行中",
                                                  lv_color_hex(0x1677FF),
                                                  lv_color_hex(0xEAF3FF));

    /*
     * 告警状态
     */
    g_label_alarm_status = ui_create_status_card(parent,
                                                 x2,
                                                 y,
                                                 card_w,
                                                 card_h,
                                                 LV_SYMBOL_OK,
                                                 "告警状态",
                                                 "正常",
                                                 lv_color_hex(0x16A34A),
                                                 lv_color_hex(0xEAF8F0));

    /*
     * 在线仓位
     */
    g_label_slot_count = ui_create_status_card(parent,
                                               x3,
                                               y,
                                               card_w,
                                               card_h,
                                               LV_SYMBOL_HOME,
                                               "在线仓位",
                                               "2/4",
                                               lv_color_hex(0x1677FF),
                                               lv_color_hex(0xEAF3FF));

    /*
     * 今日订单
     */
    g_label_today_order = ui_create_status_card(parent,
                                                x4,
                                                y,
                                                card_w,
                                                card_h,
                                                LV_SYMBOL_LIST,
                                                "今日订单",
                                                "18",
                                                lv_color_hex(0x6D5DF6),
                                                lv_color_hex(0xF1EFFF));
}
