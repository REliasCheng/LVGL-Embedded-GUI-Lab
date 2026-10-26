#include "dashboard_ui.h"
#include <lvgl/drivers/sdl/lv_sdl_mouse.h>
#include <lvgl/drivers/sdl/lv_sdl_window.h>
#include <SDL.h>

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    const bool smoke = argc == 2 && strcmp(argv[1], "--smoke") == 0;
    const int samples[] = {2000, 3100, 2400, 1200, 800, 2800, 3600, 1800};
    dashboard_model_t model;
    dashboard_ui_t ui;
    uint32_t elapsed = 0;
    uint32_t last_sample = 0;
    unsigned next_sample = 0;
    lv_init();
    lv_display_t *display = lv_sdl_window_create(240, 280);
    if(display == NULL || lv_sdl_window_get_window(display) == NULL) {
        fputs("SDL window creation failed\n", stderr);
        return 1;
    }
    lv_sdl_window_set_title(display, "Embedded Monitoring Dashboard");
    lv_sdl_window_set_zoom(display, 2.0f);
    lv_indev_t *mouse = lv_sdl_mouse_create();
    if(mouse == NULL || !dashboard_model_init(&model, 1400, 2700) ||
       !dashboard_ui_create(&ui, &model, display)) {
        fputs("Dashboard initialization failed\n", stderr);
        return 1;
    }
    int width, height;
    SDL_GetWindowSize(lv_sdl_window_get_window(display), &width, &height);
    if(width <= 0 || height <= 0 || lv_display_get_horizontal_resolution(display) != 240 ||
       lv_display_get_vertical_resolution(display) != 280) return 1;
    while(!smoke || elapsed < 1200) {
        SDL_Delay(20);
        lv_tick_inc(20);
        lv_timer_handler();
        elapsed += 20;
        if(elapsed - last_sample >= 500 && model.run == DASHBOARD_RUNNING) {
            dashboard_model_sample(&model, samples[next_sample++ % (sizeof(samples) / sizeof(samples[0]))]);
            if(!dashboard_ui_refresh(&ui)) return 1;
            last_sample = elapsed;
        }
    }
    if(smoke) printf("sdl_smoke: PASS window=%dx%d logical=240x280 samples=%lu\n",
                     width, height, (unsigned long)model.accepted);
    dashboard_ui_destroy(&ui);
    lv_indev_delete(mouse);
    lv_display_delete(display);
    lv_deinit();
    return 0;
}
