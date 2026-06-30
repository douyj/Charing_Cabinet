#include <unistd.h>
#include <lvgl.h>
#include "sdl/sdl.h"
#include "ui/ui_top_bar.h"
#include "ui/ui_status_card.h"
#include "chinese/ui_fonts.h"
#include "ui/ui_cabinet_card.h"
#include "ui/ui_system_log.h"
#include "ui/ui_bottom_bar.h"

int main(void)
{
    lv_init();

    /* Linux/Ubuntu 下使用 SDL 模拟显示器，便于直接看到界面 */
    sdl_init();

    /* 注册 SDL 显示驱动（在创建任何对象前） */
    static lv_disp_draw_buf_t draw_buf;
    static lv_color_t buf[SDL_HOR_RES * 10]; /* 缓冲 10 行 */
    lv_disp_draw_buf_init(&draw_buf, buf, NULL, SDL_HOR_RES * 10);

    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = SDL_HOR_RES;
    disp_drv.ver_res = SDL_VER_RES;
    disp_drv.flush_cb = sdl_display_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    ui_fonts_init();

    /* 在当前活动屏幕上创建顶部栏 */
    ui_create_top_bar(lv_scr_act());

    /*状态卡片*/
    ui_create_status_overview(lv_scr_act());

    ui_create_slot_area(lv_scr_act());

    ui_create_log_panel(lv_scr_act());

    ui_create_bottom_area(lv_scr_act());


    /* LVGL 主循环：不断处理定时器和事件 */
    while (1) {
        lv_tick_inc(5);
        lv_timer_handler();
        usleep(5 * 1000);
    }

    return 0;
}
