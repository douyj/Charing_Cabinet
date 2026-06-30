#include "ui/ui_cabinet_card.h"
#include "chinese/ui_fonts.h"

#include <stdio.h>
#include <stdbool.h>


/*仓位卡片通用函数*/
static lv_obj_t *ui_create_pill(lv_obj_t *parent, int x, int y, const char *text, 
                                lv_color_t text_color, lv_color_t bg_color, lv_color_t border_color)
{
    lv_obj_t *pill = lv_label_create(parent);
    lv_label_set_text(pill, text);

    lv_obj_set_pos(pill, x, y);
    lv_obj_set_style_text_color(pill, text_color, 0);
    lv_obj_set_style_text_font(pill, ui_font_zh_16(), 0);

    lv_obj_set_style_bg_color(pill, bg_color, 0);
    lv_obj_set_style_bg_opa(pill, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(pill, 5, 0);
    lv_obj_set_style_pad_left(pill, 8, 0);
    lv_obj_set_style_pad_right(pill, 8, 0);
    lv_obj_set_style_pad_top(pill, 1, 0);
    lv_obj_set_style_pad_bottom(pill, 1, 0);

    lv_obj_set_style_border_width(pill, 1, 0);
    lv_obj_set_style_border_color(pill, border_color, 0);

    return pill;
}

/*一张仓位卡片函数*/
static lv_obj_t *ui_create_slot_card(lv_obj_t *parent, int x, int y, int w, int h, int slot_id,
                                        slot_state_t state, int percent, float voltage, float current, float temp, bool over_temp)
{
    lv_color_t main_color;
    lv_color_t light_color;
    const char *state_text;

    /*显示状态v*/
    if (state == SLOT_STATE_CHARGING) {
        main_color = lv_color_hex(0xF59E0B);
        light_color = lv_color_hex(0xFFF3D6);
        state_text = "充电中";
    } else if (state == SLOT_STATE_IDLE) {
        main_color = lv_color_hex(0x94A3B8);
        light_color = lv_color_hex(0xF1F5F9);
        state_text = "空闲";
    } else if (state == SLOT_STATE_ERROR) {
        main_color = lv_color_hex(0xEF4444);
        light_color = lv_color_hex(0xFEE2E2);
        state_text = "故障";
    } else {
        main_color = lv_color_hex(0x16A34A);
        light_color = lv_color_hex(0xDCFCE7);
        state_text = "已充满";
    }

    /*卡片主体*/
    lv_obj_t *card = lv_obj_create(parent);
    lv_obj_set_size(card, w, h);
    lv_obj_set_pos(card, x, y);

    lv_obj_set_style_bg_color(card, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_bg_opa(card, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(card, 8, 0);
    lv_obj_set_style_border_width(card, 0, 0);
    lv_obj_set_style_border_color(card, lv_color_hex(0xE5EAF2), 0);

    lv_obj_set_style_shadow_width(card, 5, 0);
    lv_obj_set_style_shadow_opa(card, LV_OPA_10, 0);
    lv_obj_set_style_shadow_color(card, lv_color_hex(0x94A3B8), 0);

    lv_obj_set_style_pad_all(card, 0, 0);

    /*1号仓位*/
    char title_buf[16];
    snprintf(title_buf, sizeof(title_buf), "%d号仓位", slot_id);

    lv_obj_t *title = lv_label_create(card);
    lv_label_set_text(title, title_buf);
    lv_obj_set_pos(title, 16, 8);
    lv_obj_set_style_text_color(title, lv_color_hex(0x0F172A), 0);
    lv_obj_set_style_text_font(title, ui_font_zh_16(), 0);

    /*状态标签*/
    ui_create_pill(card, 90, 5, state_text, main_color, light_color, light_color);

    /*过温标签*/
    if(over_temp){
        ui_create_pill(card, 198, 5, "过温", lv_color_hex(0xEF4444), lv_color_hex(0xFFF5F5), lv_color_hex(0xFCA5A5));
    }

    /*圆环电量*/
    lv_obj_t *arc = lv_arc_create(card);
    lv_obj_set_size(arc, 76, 76);
    lv_obj_set_pos(arc, 18, 35);

    lv_arc_set_range(arc, 0, 100);
    lv_arc_set_value(arc, percent);
    lv_arc_set_bg_angles(arc, 0, 360);
    lv_arc_set_rotation(arc, 270);

    lv_obj_remove_style(arc, NULL, LV_PART_KNOB);   //移除旋钮样式

    lv_obj_set_style_arc_width(arc, 5, LV_PART_MAIN);
    lv_obj_set_style_arc_color(arc, light_color, LV_PART_MAIN);

    lv_obj_set_style_arc_width(arc, 5, LV_PART_INDICATOR);
    lv_obj_set_style_arc_color(arc, main_color, LV_PART_INDICATOR);

    /*电池图标*/
    lv_obj_t *bat_icon = lv_label_create(card);
    lv_label_set_text(bat_icon, LV_SYMBOL_BATTERY_FULL);
    lv_obj_set_pos(bat_icon, 42, 52);
    lv_obj_set_style_text_color(bat_icon, main_color, 0);
    lv_obj_set_style_text_font(bat_icon, &lv_font_montserrat_24, 0);

    /*百分比*/
    char percent_buf[16];
    snprintf(percent_buf, sizeof(percent_buf), "%d%%", percent);

    lv_obj_t *percent_label = lv_label_create(card);
    lv_label_set_text(percent_label, percent_buf);
    lv_obj_set_pos(percent_label, 43, 78);
    lv_obj_set_style_text_color(percent_label, lv_color_hex(0x0F172A), 0);
    lv_obj_set_style_text_font(percent_label, ui_font_zh_12(), 0);

    /*数值文字*/
    lv_obj_t *v_name = lv_label_create(card);
    lv_label_set_text(v_name, "电压");
    lv_obj_set_pos(v_name, 128, 40);
    lv_obj_set_style_text_color(v_name, lv_color_hex(0x64748B), 0);
    lv_obj_set_style_text_font(v_name, ui_font_zh_16(), 0);

    lv_obj_t *a_name = lv_label_create(card);
    lv_label_set_text(a_name, "电流");
    lv_obj_set_pos(a_name, 128, 62);
    lv_obj_set_style_text_color(a_name, lv_color_hex(0x64748B), 0);
    lv_obj_set_style_text_font(a_name, ui_font_zh_16(), 0);

    lv_obj_t *t_name = lv_label_create(card);
    lv_label_set_text(t_name, "温度");
    lv_obj_set_pos(t_name, 128, 84);
    lv_obj_set_style_text_color(t_name, lv_color_hex(0x64748B), 0);
    lv_obj_set_style_text_font(t_name, ui_font_zh_16(), 0);

    /*数值*/
    char buf[32];

    lv_obj_t *v_value = lv_label_create(card);
    snprintf(buf, sizeof(buf), "%.1f V", voltage);
    lv_label_set_text(v_value, buf);
    lv_obj_set_pos(v_value, 200, 43);
    lv_obj_set_style_text_color(v_value, lv_color_hex(0x0F172A), 0);
    lv_obj_set_style_text_font(v_value, ui_font_zh_12(), 0);

    lv_obj_t *a_value = lv_label_create(card);
    snprintf(buf, sizeof(buf), "%.1f A", current);
    lv_label_set_text(a_value, buf);
    lv_obj_set_pos(a_value, 200, 65);
    lv_obj_set_style_text_color(a_value, lv_color_hex(0x0F172A), 0);
    lv_obj_set_style_text_font(a_value, ui_font_zh_12(), 0);

    lv_obj_t *t_value = lv_label_create(card);
    snprintf(buf, sizeof(buf), "%.1f ℃", temp);
    lv_label_set_text(t_value, buf);
    lv_obj_set_pos(t_value, 200, 87);

    /*过温变红*/
    if (over_temp) {
        lv_obj_set_style_text_color(t_value, lv_color_hex(0xDC2626), 0);
    } else {
        lv_obj_set_style_text_color(t_value, lv_color_hex(0x0F172A), 0);
    }

    lv_obj_set_style_text_font(t_value, ui_font_zh_12(), 0);

    return card;
}


/*创建4个仓位卡片函数*/
void ui_create_slot_area(lv_obj_t *parent)
{
    int card_w = 260;
    int card_h = 120;

    int x1 = 18;
    int x2 = 288;

    int y1 = 153;
    int y2 = 280;

    /*1号仓位*/
    ui_create_slot_card(parent,
                        x1,
                        y1,
                        card_w,
                        card_h,
                        1,
                        SLOT_STATE_CHARGING,
                        68,
                        48.6f,
                        2.1f,
                        36.8f,
                        false);

    /*2号仓位*/
    ui_create_slot_card(parent,
                        x2,
                        y1,
                        card_w,
                        card_h,
                        2,
                        SLOT_STATE_IDLE,
                        0,
                        0.0f,
                        0.0f,
                        29.4f,
                        false);

    /*3号仓位*/
    ui_create_slot_card(parent,
                        x1,
                        y2,
                        card_w,
                        card_h,
                        3,
                        SLOT_STATE_ERROR,
                        54,
                        47.2f,
                        0.0f,
                        63.5f,
                        true);
    
    /*4号仓位*/
    ui_create_slot_card(parent,
                        x2,
                        y2,
                        card_w,
                        card_h,
                        4,
                        SLOT_STATE_FULL,
                        100,
                        54.2f,
                        0.0f,
                        31.2f,
                        false);
} 
