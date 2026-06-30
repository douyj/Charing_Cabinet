#ifndef UI_CABINET_CARD_H
#define UI_CABINET_CARD_H

#include <lvgl.h>

typedef enum {
    SLOT_STATE_CHARGING = 0,
    SLOT_STATE_IDLE,
    SLOT_STATE_ERROR,
    SLOT_STATE_FULL
} slot_state_t;

void ui_create_slot_area(lv_obj_t *parent);

#endif /* UI_CABINET_CARD_H */
