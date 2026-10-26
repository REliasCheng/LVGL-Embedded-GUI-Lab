#ifndef DASHBOARD_UI_H
#define DASHBOARD_UI_H

#include "dashboard_model.h"
#include <lvgl.h>

typedef struct {
    dashboard_model_t *model;
    lv_display_t *display;
    lv_obj_t *main_screen;
    lv_obj_t *diag_screen;
    lv_obj_t *value_label;
    lv_obj_t *level_label;
    lv_obj_t *run_label;
    lv_obj_t *error_label;
    lv_obj_t *bar;
    lv_obj_t *action_button;
    lv_obj_t *action_text;
    lv_obj_t *reset_button;
    lv_obj_t *fault_button;
    lv_obj_t *diag_button;
    lv_obj_t *back_button;
    lv_obj_t *diag_text;
    uint32_t event_count;
} dashboard_ui_t;

bool dashboard_ui_create(dashboard_ui_t *ui, dashboard_model_t *model, lv_display_t *display);
bool dashboard_ui_refresh(dashboard_ui_t *ui);
void dashboard_ui_destroy(dashboard_ui_t *ui);

#endif
