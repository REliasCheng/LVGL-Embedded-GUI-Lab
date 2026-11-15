#include "dashboard_ui.h"
#include "../third_party/lvgl/src/display/lv_display_private.h"

#include <stdio.h>
#include <stdlib.h>

#define CHECK(condition) do { if(!(condition)) { \
    fprintf(stderr, "allocation %u: %s\n", fail_at, #condition); return 1; \
} } while(0)

static unsigned fail_at, calls;
static bool armed, injected;

void *__real_lv_malloc_core(size_t size);
void *__real_lv_realloc_core(void *ptr, size_t size);

static bool inject(void)
{
    if(!armed || ++calls != fail_at) return false;
    injected = true;
    return true;
}

void *__wrap_lv_malloc_core(size_t size)
{
    return inject() ? NULL : __real_lv_malloc_core(size);
}

void *__wrap_lv_realloc_core(void *ptr, size_t size)
{
    return inject() ? NULL : __real_lv_realloc_core(ptr, size);
}

int main(int argc, char **argv)
{
    if(argc != 2) return 2;
    fail_at = (unsigned)strtoul(argv[1], NULL, 10);
    dashboard_model_t model;
    dashboard_ui_t ui;
    CHECK(dashboard_model_init(&model, 1400, 2700));
    lv_init();
    lv_display_t *display = lv_display_create(240, 280);
    CHECK(display != NULL);
    lv_obj_t *original = lv_display_get_screen_active(display);
    uint32_t screens = display->screen_cnt;
    armed = true;
    bool created = dashboard_ui_create(&ui, &model, display);
    armed = false;
    CHECK(fail_at == 0 ? created : injected);
    if(created) {
        CHECK(dashboard_ui_refresh(&ui));
        CHECK(lv_display_get_screen_active(display) == ui.main_screen);
        lv_screen_load(original);
    }
    else {
        CHECK(!ui.main_screen && !ui.diag_screen && !ui.model && !ui.display);
        CHECK(!dashboard_ui_refresh(&ui));
    }
    dashboard_ui_destroy(&ui);
    dashboard_ui_destroy(&ui);
    CHECK(lv_display_get_screen_active(display) == original);
    CHECK(display->screen_cnt == screens);
    CHECK(lv_mem_test() == LV_RESULT_OK);
    CHECK(dashboard_ui_create(&ui, &model, display));
    lv_screen_load(original);
    dashboard_ui_destroy(&ui);
    CHECK(display->screen_cnt == screens);
    lv_display_delete(display);
    lv_deinit();
    printf("allocation=%u calls=%u result=%s\n", fail_at, calls, created ? "usable" : "clean_failure");
    return 0;
}
