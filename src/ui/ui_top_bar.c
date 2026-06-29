#include "ui/ui_top_bar.h"

static lv_obj_t *g_label_time = NULL;     //顶部栏时间
static lv_obj_t *g_label_server = NULL;     //服务器连接状态

void ui_create_top_bar(lv_obj_t *parent){
    //顶部栏容器
    lv_obj_t *top_bar = lv_obj_create(parent);
    lv_obj_set_size(top_bar, 800, 56);
    lv_obj_set_pos(top_bar, 0, 0);

    lv_obj_set_style_bg_color(top_bar, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_bg_opa(top_bar, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(top_bar, 0, 0);
    lv_obj_set_style_radius(top_bar, 0, 0);
    lv_obj_set_style_pad_all(top_bar, 0, 0);

    //底部分割线
    lv_obj_t *line = lv_obj_create(top_bar);
    lv_obj_set_size(line, 800, 1);
    lv_obj_set_pos(line, 0, 55);
    lv_obj_set_style_bg_color(line, lv_color_hex(0xE5EAF2), 0);
    lv_obj_set_style_bg_opa(line, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(line, 0, 0);
    lv_obj_set_style_radius(line, 0, 0);

    /*左侧蓝色设备图标背景*/
    lv_obj_t *logo_bg = lv_obj_create(top_bar);
    lv_obj_set_size(logo_bg, 30, 30);
    lv_obj_set_pos(logo_bg, 18, 13);
    lv_obj_set_style_bg_color(logo_bg, lv_color_hex(0x1677FF), 0);
    lv_obj_set_style_bg_opa(logo_bg, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(logo_bg, 0, 0);
    lv_obj_set_style_radius(logo_bg, 5, 0);
    lv_obj_set_style_pad_all(logo_bg, 0, 0);

    lv_obj_t *logo_text = lv_label_create(logo_bg);
    lv_label_set_text(logo_text, LV_SYMBOL_CHARGE);     //闪电图标
    lv_obj_set_style_text_color(logo_text, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_font(logo_text, &lv_font_montserrat_16, 0);
    lv_obj_center(logo_text);

    /*标题*/
    lv_obj_t *title = lv_label_create(top_bar);
    lv_label_set_text(title, "充电系统");
    lv_obj_set_pos(title, 60,18);
    lv_obj_set_style_text_color(title, lv_color_hex(0x111827), 0);
    lv_obj_set_style_text_font(title, &lv_font_simsun_16_cjk, 0);

    /*子控件分割线1*/
    lv_obj_t *sep1 = lv_obj_create(top_bar);
    lv_obj_set_size(sep1, 1, 20);
    lv_obj_set_pos(sep1, 535, 18);
    lv_obj_set_style_bg_color(sep1, lv_color_hex(0xD8DEE9), 0);
    lv_obj_set_style_bg_opa(sep1, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(sep1, 0, 0);
    lv_obj_set_style_radius(sep1, 0, 0);
    
    /*服务器连接状态*/
    lv_obj_t *server_icon = lv_label_create(top_bar);
    lv_label_set_text(server_icon, LV_SYMBOL_UPLOAD);
    lv_obj_set_pos(server_icon, 555, 18);
    lv_obj_set_style_text_color(server_icon, lv_color_hex(0x1677FF), 0);
    lv_obj_set_style_text_font(server_icon, &lv_font_simsun_16_cjk, 0);

    g_label_server = lv_label_create(top_bar);
    lv_label_set_text(g_label_server, "后台已连接");
    lv_obj_set_pos(g_label_server, 583, 18);
    lv_obj_set_style_text_color(g_label_server, lv_color_hex(0x334155), 0);
    lv_obj_set_style_text_font(g_label_server, &lv_font_simsun_16_cjk, 0);

    /*分割线2*/
    lv_obj_t *sep2 = lv_obj_create(top_bar);
    lv_obj_set_size(sep2, 1, 20);
    lv_obj_set_pos(sep2, 690, 18);
    lv_obj_set_style_bg_color(sep2, lv_color_hex(0xD8DEE9), 0);
    lv_obj_set_style_bg_opa(sep2, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(sep2, 0, 0);
    lv_obj_set_style_radius(sep2, 0, 0);

    /*时间*/
    g_label_time = lv_label_create(top_bar);
    lv_label_set_text(g_label_time, "15:32");
    lv_obj_set_pos(g_label_time, 720, 18);
    lv_obj_set_style_text_color(g_label_time, lv_color_hex(0x334155), 0);
    lv_obj_set_style_text_font(g_label_time, &lv_font_montserrat_16, 0);


}

