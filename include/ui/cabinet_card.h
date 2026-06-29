#ifndef CABINET_CARD_H
#define CABINET_CARD_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct cabinet_card {
    lv_obj_t * container;
    lv_obj_t * title;
    lv_obj_t * status;
    lv_obj_t * percent;
    lv_obj_t * voltage;
    lv_obj_t * current;
    lv_obj_t * temperature;
} cabinet_card_t;

cabinet_card_t * cabinet_card_create(lv_obj_t *parent, const char *title_text, const char *status_text);
void cabinet_card_update(cabinet_card_t *card, const char *percent_text,
                         const char *voltage_text, const char *current_text,
                         const char *temperature_text);

#ifdef __cplusplus
}
#endif

#endif // CABINET_CARD_H