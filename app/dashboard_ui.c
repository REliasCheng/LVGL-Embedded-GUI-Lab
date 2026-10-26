#include "dashboard_ui.h"

#include <stdio.h>
#include <string.h>

static lv_obj_t *make_label(lv_obj_t *parent, const char *text, int x, int y)
{
    lv_obj_t *label = lv_label_create(parent);
    if(label == NULL) return NULL;
    lv_label_set_text(label, text);
    lv_obj_set_pos(label, x, y);
    return label;
}

static lv_obj_t *make_button(lv_obj_t *parent, const char *text, int x, int y,
                             int width, lv_event_cb_t cb, dashboard_ui_t *ui,
                             lv_obj_t **caption)
{
    lv_obj_t *button = lv_button_create(parent);
    if(button == NULL) return NULL;
    lv_obj_set_pos(button, x, y);
    lv_obj_set_size(button, width, 30);
    lv_obj_set_style_radius(button, 6, 0);
    lv_obj_set_style_bg_color(button, lv_color_hex(0x1F6D86), 0);
    *caption = lv_label_create(button);
    if(*caption == NULL) return NULL;
    lv_label_set_text(*caption, text);
    lv_obj_center(*caption);
    lv_obj_add_event_cb(button, cb, LV_EVENT_CLICKED, ui);
    return button;
}

static void on_action(lv_event_t *event)
{
    dashboard_ui_t *ui = lv_event_get_user_data(event);
    if(ui == NULL || ui->model == NULL) return;
    ui->event_count++;
    if(ui->model->run == DASHBOARD_RUNNING) dashboard_model_pause(ui->model);
    else if(ui->model->run == DASHBOARD_PAUSED) dashboard_model_resume(ui->model);
    else dashboard_model_recover(ui->model);
    dashboard_ui_refresh(ui);
}

static void on_reset(lv_event_t *event)
{
    dashboard_ui_t *ui = lv_event_get_user_data(event);
    if(ui == NULL || ui->model == NULL) return;
    ui->event_count++;
    dashboard_model_reset(ui->model);
    dashboard_ui_refresh(ui);
}

static void on_fault(lv_event_t *event)
{
    dashboard_ui_t *ui = lv_event_get_user_data(event);
    if(ui == NULL || ui->model == NULL) return;
    ui->event_count++;
    if(ui->model->run == DASHBOARD_PAUSED) dashboard_model_resume(ui->model);
    dashboard_model_sample(ui->model, 4096);
    dashboard_ui_refresh(ui);
}

static void on_diag(lv_event_t *event)
{
    dashboard_ui_t *ui = lv_event_get_user_data(event);
    if(ui == NULL || ui->diag_screen == NULL) return;
    ui->event_count++;
    lv_screen_load(ui->diag_screen);
}

static void on_back(lv_event_t *event)
{
    dashboard_ui_t *ui = lv_event_get_user_data(event);
    if(ui == NULL || ui->main_screen == NULL) return;
    ui->event_count++;
    lv_screen_load(ui->main_screen);
}

bool dashboard_ui_create(dashboard_ui_t *ui, dashboard_model_t *model, lv_display_t *display)
{
    lv_obj_t *caption;
    if(ui == NULL || model == NULL || display == NULL) return false;
    memset(ui, 0, sizeof(*ui));
    ui->model = model;
    ui->display = display;
    ui->main_screen = lv_obj_create(NULL);
    ui->diag_screen = lv_obj_create(NULL);
    if(ui->main_screen == NULL || ui->diag_screen == NULL) return false;
    lv_obj_set_style_bg_color(ui->main_screen, lv_color_hex(0x101B2A), 0);
    lv_obj_set_style_bg_color(ui->diag_screen, lv_color_hex(0x101B2A), 0);
    lv_obj_set_style_text_color(ui->main_screen, lv_color_hex(0xE6F2F4), 0);
    lv_obj_set_style_text_color(ui->diag_screen, lv_color_hex(0xE6F2F4), 0);
    lv_obj_set_style_pad_all(ui->main_screen, 0, 0);
    lv_obj_set_style_pad_all(ui->diag_screen, 0, 0);
    make_label(ui->main_screen, "EMBEDDED MONITOR", 12, 10);
    make_label(ui->main_screen, "SYNTHETIC ADC  /  12 BIT", 12, 31);
    ui->value_label = make_label(ui->main_screen, "ADC --", 12, 62);
    ui->level_label = make_label(ui->main_screen, "UNKNOWN", 12, 96);
    ui->bar = lv_bar_create(ui->main_screen);
    lv_obj_set_pos(ui->bar, 12, 123);
    lv_obj_set_size(ui->bar, 216, 15);
    lv_bar_set_range(ui->bar, 0, 4095);
    lv_obj_set_style_bg_color(ui->bar, lv_color_hex(0x25354A), 0);
    lv_obj_set_style_bg_color(ui->bar, lv_color_hex(0x39BCD3), LV_PART_INDICATOR);
    ui->run_label = make_label(ui->main_screen, "RUNNING", 12, 151);
    ui->error_label = make_label(ui->main_screen, "Error: none", 12, 177);
    ui->action_button = make_button(ui->main_screen, "Pause", 12, 207, 68, on_action, ui, &ui->action_text);
    ui->reset_button = make_button(ui->main_screen, "Reset", 86, 207, 68, on_reset, ui, &caption);
    ui->fault_button = make_button(ui->main_screen, "Fault", 160, 207, 68, on_fault, ui, &caption);
    ui->diag_button = make_button(ui->main_screen, "Diagnostics", 12, 244, 216, on_diag, ui, &caption);
    make_label(ui->diag_screen, "DIAGNOSTICS", 12, 12);
    ui->diag_text = make_label(ui->diag_screen, "", 12, 45);
    ui->back_button = make_button(ui->diag_screen, "Back to dashboard", 12, 244, 216, on_back, ui, &caption);
    if(ui->value_label == NULL || ui->level_label == NULL || ui->bar == NULL ||
       ui->run_label == NULL || ui->error_label == NULL || ui->action_button == NULL ||
       ui->reset_button == NULL || ui->fault_button == NULL || ui->diag_button == NULL ||
       ui->diag_text == NULL || ui->back_button == NULL) return false;
    lv_screen_load(ui->main_screen);
    return dashboard_ui_refresh(ui);
}

bool dashboard_ui_refresh(dashboard_ui_t *ui)
{
    char text[256];
    if(ui == NULL || ui->model == NULL || ui->display == NULL ||
       ui->main_screen == NULL || ui->diag_screen == NULL ||
       !lv_obj_is_valid(ui->main_screen) || !lv_obj_is_valid(ui->diag_screen) ||
       !lv_obj_is_valid(ui->value_label) || !lv_obj_is_valid(ui->level_label) ||
       !lv_obj_is_valid(ui->bar) || !lv_obj_is_valid(ui->run_label) ||
       !lv_obj_is_valid(ui->error_label) || !lv_obj_is_valid(ui->diag_text) ||
       !lv_obj_is_valid(ui->action_text)) return false;
    snprintf(text, sizeof(text), "ADC  %s", ui->model->has_valid ? "" : "--");
    if(ui->model->has_valid) snprintf(text, sizeof(text), "ADC  %u", ui->model->last_valid);
    lv_label_set_text(ui->value_label, text);
    snprintf(text, sizeof(text), "%s  /  Seq %lu", dashboard_level_name(ui->model->level),
             (unsigned long)ui->model->sequence);
    lv_label_set_text(ui->level_label, text);
    lv_bar_set_value(ui->bar, ui->model->has_valid ? ui->model->last_valid : 0, LV_ANIM_OFF);
    lv_label_set_text(ui->run_label, dashboard_run_name(ui->model->run));
    snprintf(text, sizeof(text), "Error: %s", ui->model->error);
    lv_label_set_text(ui->error_label, text);
    lv_label_set_text(ui->action_text, ui->model->run == DASHBOARD_RUNNING ? "Pause" :
                      (ui->model->run == DASHBOARD_FAULT ? "Recover" : "Resume"));
    lv_obj_center(ui->action_text);
    snprintf(text, sizeof(text),
             "State: %s\nLevel: %s\nLast error: %s\nAccepted: %lu\nRejected: %lu\nLast valid: %s\nValue: %u\nSequence: %lu",
             dashboard_run_name(ui->model->run), dashboard_level_name(ui->model->level),
             ui->model->error, (unsigned long)ui->model->accepted,
             (unsigned long)ui->model->rejected, ui->model->has_valid ? "yes" : "none",
             ui->model->has_valid ? ui->model->last_valid : 0,
             (unsigned long)ui->model->sequence);
    lv_label_set_text(ui->diag_text, text);
    return true;
}

void dashboard_ui_destroy(dashboard_ui_t *ui)
{
    if(ui == NULL) return;
    if(ui->main_screen && lv_obj_is_valid(ui->main_screen)) lv_obj_delete(ui->main_screen);
    if(ui->diag_screen && lv_obj_is_valid(ui->diag_screen)) lv_obj_delete(ui->diag_screen);
    memset(ui, 0, sizeof(*ui));
}
