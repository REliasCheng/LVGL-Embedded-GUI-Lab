#ifndef DASHBOARD_MODEL_H
#define DASHBOARD_MODEL_H

#include <stdbool.h>
#include <stdint.h>

typedef enum { DASHBOARD_UNKNOWN, DASHBOARD_LOW, DASHBOARD_HIGH } dashboard_level_t;
typedef enum { DASHBOARD_RUNNING, DASHBOARD_PAUSED, DASHBOARD_FAULT } dashboard_run_t;

typedef struct {
    uint16_t low;
    uint16_t high;
    uint16_t last_valid;
    bool has_valid;
    dashboard_level_t level;
    dashboard_run_t run;
    uint32_t accepted;
    uint32_t rejected;
    uint32_t sequence;
    const char *error;
} dashboard_model_t;

bool dashboard_model_init(dashboard_model_t *model, uint16_t low, uint16_t high);
bool dashboard_model_sample(dashboard_model_t *model, int32_t sample);
bool dashboard_model_pause(dashboard_model_t *model);
bool dashboard_model_resume(dashboard_model_t *model);
bool dashboard_model_recover(dashboard_model_t *model);
bool dashboard_model_reset(dashboard_model_t *model);
const char *dashboard_level_name(dashboard_level_t level);
const char *dashboard_run_name(dashboard_run_t run);

#endif
