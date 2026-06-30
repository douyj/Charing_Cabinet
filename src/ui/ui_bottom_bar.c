#include "ui/ui_bottom_bar.h"

static lv_obj_t *g_btn_start_charge = NULL;
static lv_obj_t *g_btn_stop_charge  = NULL;
static lv_obj_t *g_btn_open_door    = NULL;
static lv_obj_t *g_btn_clear_alarm  = NULL;

static lv_obj_t *ui_create_bottom_button(lv_obj_t *parent, int x, int y, int w, int h, const char *icon_text, const char *btn_text, lv_color_t icon_color, bool primary)
{
    /*按钮*/
    lv_obj_t *btn = lv_btn_create(parent);
    lv_obj_set_size(btn, w, h);
    lv_obj_set_pos(btn, x, y);

    lv_obj_set_style_radius(btn, 6, 0);
    lv_obj_set_style_shadow_width(btn, 0, 0);
    lv_obj_set_style_border_width(btn, 1, 0);
    lv_obj_set_style_pad_all(btn, 0, 0);

    if (primary) {
        lv_obj_set_style_bg_color(btn, lv_color_hex(0x1677FF), 0);
        lv_obj_set_style_bg_opa(btn, LV_OPA_COVER, 0);
        lv_obj_set_style_border_color(btn, lv_color_hex(0x1677FF), 0);
    } else {
        lv_obj_set_style_bg_color(btn, lv_color_hex(0xFFFFFF), 0);
        lv_obj_set_style_bg_opa(btn, LV_OPA_COVER, 0);
        lv_obj_set_style_border_color(btn, lv_color_hex(0xCBD5E1), 0);
    }

    /*图标*/
    lv_obj_t *icon = lv_label_create(btn);
    lv_label_set_text(icon, icon_text);

    if (primary) {
        lv_obj_set_style_text_color(icon, lv_color_hex(0xFFFFFF), 0);
    } else {
        lv_obj_set_style_text_color(icon, icon_color, 0);
    }

    lv_obj_set_style_text_font(icon, &lv_font_montserrat_18, 0);
    lv_obj_set_pos(icon, 42, 11);

    /*文字*/
    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, btn_text);

    if (primary) {
        lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), 0);
    } else {
        lv_obj_set_style_text_color(label, lv_color_hex(0x0F172A), 0);
    }

    lv_obj_set_style_text_font(label, ui_font_zh_12(), 0);
    lv_obj_set_pos(label, 72, 11);

    return btn;

}

/*底部栏函数*/
void ui_create_bottom_area(lv_obj_t *parent)
{
    /*
     * 底部白色容器
     */
    lv_obj_t *bottom_panel = lv_obj_create(parent);
    lv_obj_set_size(bottom_panel, 764, 65);
    lv_obj_set_pos(bottom_panel, 18, 408);

    lv_obj_set_style_bg_color(bottom_panel, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_bg_opa(bottom_panel, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(bottom_panel, 8, 0);
    lv_obj_set_style_border_width(bottom_panel, 1, 0);
    lv_obj_set_style_border_color(bottom_panel, lv_color_hex(0xE5EAF2), 0);

    lv_obj_set_style_shadow_width(bottom_panel, 5, 0);
    lv_obj_set_style_shadow_opa(bottom_panel, LV_OPA_10, 0);
    lv_obj_set_style_shadow_color(bottom_panel, lv_color_hex(0x94A3B8), 0);

    lv_obj_set_style_pad_all(bottom_panel, 0, 0);

    /*
     * 四个按钮
     */
    g_btn_start_charge = ui_create_bottom_button(bottom_panel,
                                                 17,
                                                 14,
                                                 165,
                                                 42,
                                                 LV_SYMBOL_PLAY,
                                                 "开始充电",
                                                 lv_color_hex(0xFFFFFF),
                                                 true);

    g_btn_stop_charge = ui_create_bottom_button(bottom_panel,
                                                207,
                                                14,
                                                165,
                                                42,
                                                LV_SYMBOL_STOP,
                                                "停止充电",
                                                lv_color_hex(0xEF4444),
                                                false);

    g_btn_open_door = ui_create_bottom_button(bottom_panel,
                                              397,
                                              14,
                                              165,
                                              42,
                                              LV_SYMBOL_HOME,
                                              "打开仓门",
                                              lv_color_hex(0x1677FF),
                                              false);

    g_btn_clear_alarm = ui_create_bottom_button(bottom_panel,
                                                587,
                                                14,
                                                155,
                                                42,
                                                LV_SYMBOL_WARNING,
                                                "清除告警",
                                                lv_color_hex(0xF59E0B),
                                                false);
}