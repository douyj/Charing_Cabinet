#include "ui/ui_system_log.h"
#include "chinese/ui_fonts.h"

static void ui_create_log_item(lv_obj_t *parent, int y, const char *time_text, const char *msg_text, bool is_error)
{
    /*蓝色圆点*/
    lv_obj_t *dot = lv_obj_create(parent);
    lv_obj_set_size(dot, 6, 6);
    lv_obj_set_pos(dot, 18, y + 8);
    lv_obj_set_style_radius(dot, 3, 0);
    lv_obj_set_style_bg_color(dot, lv_color_hex(0x1677FF), 0);
    lv_obj_set_style_bg_opa(dot, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(dot, 0, 0);

    /*时间*/
    lv_obj_t *time_label = lv_label_create(parent);
    lv_label_set_text(time_label, time_text);
    lv_obj_set_pos(time_label, 34, y);
    lv_obj_set_style_text_color(time_label, lv_color_hex(0x64748B), 0);
    lv_obj_set_style_text_font(time_label, ui_font_zh_12(), 0);

    /*日志内容*/
    lv_obj_t *msg_label = lv_label_create(parent);
    lv_label_set_text(msg_label, msg_text);
    lv_obj_set_pos(msg_label, 88, y);

    if (is_error) {
        lv_obj_set_style_text_color(msg_label, lv_color_hex(0xEF4444), 0);
    } else {
        lv_obj_set_style_text_color(msg_label, lv_color_hex(0x475569), 0);
    }

    lv_obj_set_style_text_font(msg_label, ui_font_zh_12(), 0);

}


/*创建日志面板*/
void ui_create_log_panel(lv_obj_t *parent)
{
    lv_obj_t *panel = lv_obj_create(parent);
    lv_obj_set_size(panel, 224, 248);
    lv_obj_set_pos(panel, 558, 153);

    lv_obj_set_style_bg_color(panel, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_bg_opa(panel, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(panel, 8, 0);
    lv_obj_set_style_border_width(panel, 1, 0);
    lv_obj_set_style_border_color(panel, lv_color_hex(0xE5EAF2), 0);

    lv_obj_set_style_shadow_width(panel, 5, 0);
    lv_obj_set_style_shadow_opa(panel, LV_OPA_10, 0);
    lv_obj_set_style_shadow_color(panel, lv_color_hex(0x94A3B8), 0);

    lv_obj_set_style_pad_all(panel, 0, 0);

    /*
     * 标题图标
     */
    lv_obj_t *icon = lv_label_create(panel);
    lv_label_set_text(icon, LV_SYMBOL_LIST);
    lv_obj_set_pos(icon, 18, 18);
    lv_obj_set_style_text_color(icon, lv_color_hex(0x1677FF), 0);
    lv_obj_set_style_text_font(icon, &lv_font_montserrat_18, 0);

    /*
     * 标题
     */
    lv_obj_t *title = lv_label_create(panel);
    lv_label_set_text(title, "系统日志");
    lv_obj_set_pos(title, 44, 17);
    lv_obj_set_style_text_color(title, lv_color_hex(0x0F172A), 0);
    lv_obj_set_style_text_font(title, ui_font_zh_16(), 0);

    /*
     * 日志内容
     */
    ui_create_log_item(panel, 58, "[15:30]", "1号仓开始充电", false);
    ui_create_log_item(panel, 88, "[15:31]", "4号仓充电完成", false);
    ui_create_log_item(panel, 118, "[15:31]", "3号仓温度异常", true);
    ui_create_log_item(panel, 148, "[15:32]", "后台连接正常", false);

    /*
     * 底部分割线
     */
    lv_obj_t *line = lv_obj_create(panel);
    lv_obj_set_size(line, 188, 1);
    lv_obj_set_pos(line, 18, 215);
    lv_obj_set_style_bg_color(line, lv_color_hex(0xE5EAF2), 0);
    lv_obj_set_style_bg_opa(line, LV_OPA_COVER, 0);
    lv_obj_set_style_border_width(line, 0, 0);
    lv_obj_set_style_radius(line, 0, 0);

    /*
     * 查看更多
     */
    lv_obj_t *more = lv_label_create(panel);
    lv_label_set_text(more, "查看更多 >");
    lv_obj_set_pos(more, 82, 225);
    lv_obj_set_style_text_color(more, lv_color_hex(0x1677FF), 0);
    lv_obj_set_style_text_font(more, ui_font_zh_12(), 0);
}