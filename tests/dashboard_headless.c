#include "dashboard_ui.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 240
#define HEIGHT 280
#define ROWS 40
#define CHECK(cond) do { if(!(cond)) { fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond); return 1; } } while(0)

typedef struct {
    uint32_t frame[WIDTH * HEIGHT];
    uint32_t draw[WIDTH * ROWS];
    uint32_t flushes;
    bool bounds_error;
    bool pressed;
    int x;
    int y;
} headless_t;

static void flush_cb(lv_display_t *display, const lv_area_t *area, uint8_t *pixels)
{
    headless_t *h = lv_display_get_user_data(display);
    if(area->x1 < 0 || area->y1 < 0 || area->x2 >= WIDTH || area->y2 >= HEIGHT ||
       area->x2 < area->x1 || area->y2 < area->y1) {
        h->bounds_error = true;
    }
    else {
        size_t width = (size_t)(area->x2 - area->x1 + 1);
        for(int y = area->y1; y <= area->y2; y++) {
            size_t src = (size_t)(y - area->y1) * width;
            size_t dst = (size_t)y * WIDTH + (size_t)area->x1;
            memcpy(&h->frame[dst], pixels + src * sizeof(uint32_t), width * sizeof(uint32_t));
        }
        h->flushes++;
    }
    lv_display_flush_ready(display);
}

static void pointer_cb(lv_indev_t *indev, lv_indev_data_t *data)
{
    headless_t *h = lv_indev_get_user_data(indev);
    data->point.x = h->x;
    data->point.y = h->y;
    data->state = h->pressed ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
}

static void pump(void)
{
    for(int i = 0; i < 6; i++) {
        lv_tick_inc(20);
        lv_timer_handler();
    }
}

static uint64_t frame_signature(const headless_t *h)
{
    uint64_t sum = 1469598103934665603ULL;
    for(size_t i = 0; i < WIDTH * HEIGHT; i++) {
        sum ^= h->frame[i];
        sum *= 1099511628211ULL;
    }
    return sum;
}

static bool save_ppm(const char *path, const headless_t *h)
{
    FILE *file = fopen(path, "wb");
    if(file == NULL) return false;
    fprintf(file, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
    for(size_t i = 0; i < WIDTH * HEIGHT; i++) {
        uint32_t pixel = h->frame[i];
        unsigned char rgb[3] = {(unsigned char)(pixel >> 16),
                                (unsigned char)(pixel >> 8), (unsigned char)pixel};
        if(fwrite(rgb, 1, 3, file) != 3) { fclose(file); return false; }
    }
    return fclose(file) == 0;
}

static void click(headless_t *h, int x, int y)
{
    h->x = x;
    h->y = y;
    h->pressed = true;
    pump();
    h->pressed = false;
    pump();
}

int main(int argc, char **argv)
{
    static headless_t h;
    dashboard_model_t model;
    dashboard_ui_t ui;
    lv_display_t *display;
    lv_indev_t *pointer;
    uint64_t initial;
    bool image_saved = false;
    CHECK(argc >= 2 && argc <= 3);
    CHECK(dashboard_model_init(&model, 1400, 2700));
    lv_init();
    display = lv_display_create(WIDTH, HEIGHT);
    CHECK(display != NULL);
    lv_display_set_color_format(display, LV_COLOR_FORMAT_XRGB8888);
    lv_display_set_user_data(display, &h);
    lv_display_set_flush_cb(display, flush_cb);
    lv_display_set_buffers(display, h.draw, NULL, sizeof(h.draw), LV_DISPLAY_RENDER_MODE_PARTIAL);
    pointer = lv_indev_create();
    CHECK(pointer != NULL);
    lv_indev_set_type(pointer, LV_INDEV_TYPE_POINTER);
    lv_indev_set_user_data(pointer, &h);
    lv_indev_set_read_cb(pointer, pointer_cb);
    CHECK(dashboard_ui_create(&ui, &model, display));
    CHECK(lv_display_get_screen_active(display) == ui.main_screen);
    CHECK(strcmp(lv_label_get_text(ui.value_label), "ADC  --") == 0);
    pump();
    CHECK(h.flushes > 0 && !h.bounds_error);
    initial = frame_signature(&h);
    CHECK(initial != 0 && h.frame[0] != 0);

    if(strcmp(argv[1], "normal") == 0) {
        CHECK(dashboard_model_sample(&model, 2000));
        CHECK(model.level == DASHBOARD_UNKNOWN);
        CHECK(dashboard_ui_refresh(&ui));
        pump();
        CHECK(frame_signature(&h) != initial);
        CHECK(strstr(lv_label_get_text(ui.value_label), "2000") != NULL);
        CHECK(lv_bar_get_value(ui.bar) == 2000);
        CHECK(dashboard_model_sample(&model, 3000) && model.level == DASHBOARD_HIGH);
        CHECK(dashboard_ui_refresh(&ui));
        pump();
        CHECK(dashboard_model_sample(&model, 1000) && model.level == DASHBOARD_LOW);
        CHECK(dashboard_ui_refresh(&ui));
        pump();
        CHECK(model.sequence == 3 && model.accepted == 3);
    }
    else if(strcmp(argv[1], "fault") == 0) {
        CHECK(dashboard_model_sample(&model, 3000));
        CHECK(dashboard_ui_refresh(&ui));
        pump();
        CHECK(lv_obj_send_event(ui.fault_button, LV_EVENT_CLICKED, NULL) == LV_RESULT_OK);
        pump();
        CHECK(model.run == DASHBOARD_FAULT && model.last_valid == 3000);
        CHECK(strstr(lv_label_get_text(ui.error_label), "out of range") != NULL);
        CHECK(strcmp(lv_label_get_text(ui.run_label), "FAULT") == 0);
        CHECK(frame_signature(&h) != initial);
        if(argc == 3) { CHECK(save_ppm(argv[2], &h)); image_saved = true; }
        CHECK(lv_obj_send_event(ui.action_button, LV_EVENT_CLICKED, NULL) == LV_RESULT_OK);
        CHECK(model.run == DASHBOARD_PAUSED);
        CHECK(lv_obj_send_event(ui.action_button, LV_EVENT_CLICKED, NULL) == LV_RESULT_OK);
        CHECK(model.run == DASHBOARD_RUNNING);
        CHECK(dashboard_model_sample(&model, 1000));
        CHECK(dashboard_ui_refresh(&ui));
        pump();
    }
    else if(strcmp(argv[1], "interaction") == 0) {
        click(&h, 42, 222);
        CHECK(model.run == DASHBOARD_PAUSED && ui.event_count == 1);
        CHECK(!dashboard_model_sample(&model, 3000) && model.sequence == 0);
        click(&h, 42, 222);
        CHECK(model.run == DASHBOARD_RUNNING && ui.event_count == 2);
        CHECK(dashboard_model_sample(&model, 3000));
        CHECK(dashboard_ui_refresh(&ui));
        pump();
        click(&h, 100, 258);
        CHECK(lv_display_get_screen_active(display) == ui.diag_screen);
        CHECK(strstr(lv_label_get_text(ui.diag_text), "Accepted: 1") != NULL);
        if(argc == 3) { CHECK(save_ppm(argv[2], &h)); image_saved = true; }
        click(&h, 100, 258);
        CHECK(lv_display_get_screen_active(display) == ui.main_screen);
        CHECK(lv_obj_send_event(ui.reset_button, LV_EVENT_CLICKED, NULL) == LV_RESULT_OK);
        CHECK(model.sequence == 0 && !model.has_valid);
        pump();
        CHECK(ui.event_count == 5 && !h.bounds_error);
    }
    else { fprintf(stderr, "Unknown scenario: %s\n", argv[1]); return 2; }

    CHECK(h.flushes > 0 && !h.bounds_error);
    if(argc == 3 && !image_saved) CHECK(save_ppm(argv[2], &h));
    printf("%s: PASS flushes=%lu events=%lu signature=%llu\n", argv[1],
           (unsigned long)h.flushes, (unsigned long)ui.event_count,
           (unsigned long long)frame_signature(&h));
    dashboard_ui_destroy(&ui);
    CHECK(!dashboard_ui_refresh(&ui));
    lv_indev_delete(pointer);
    lv_display_delete(display);
    lv_deinit();
    return 0;
}
