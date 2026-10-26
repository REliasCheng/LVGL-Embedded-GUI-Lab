#include "dashboard_model.h"

#include <limits.h>
#include <string.h>

bool dashboard_model_init(dashboard_model_t *model, uint16_t low, uint16_t high)
{
    if(model == NULL || low >= high || high > 4095) return false;
    memset(model, 0, sizeof(*model));
    model->low = low;
    model->high = high;
    model->level = DASHBOARD_UNKNOWN;
    model->run = DASHBOARD_RUNNING;
    model->error = "none";
    return true;
}

bool dashboard_model_sample(dashboard_model_t *model, int32_t sample)
{
    if(model == NULL || model->run != DASHBOARD_RUNNING) return false;
    if(sample < 0 || sample > 4095) {
        if(model->rejected < UINT32_MAX) model->rejected++;
        model->run = DASHBOARD_FAULT;
        model->error = "ADC out of range";
        return false;
    }
    model->last_valid = (uint16_t)sample;
    model->has_valid = true;
    if(model->accepted < UINT32_MAX) model->accepted++;
    if(model->sequence < UINT32_MAX) model->sequence++;
    if(sample >= model->high) model->level = DASHBOARD_HIGH;
    else if(sample <= model->low) model->level = DASHBOARD_LOW;
    return true;
}

bool dashboard_model_pause(dashboard_model_t *model)
{
    if(model == NULL || model->run != DASHBOARD_RUNNING) return false;
    model->run = DASHBOARD_PAUSED;
    return true;
}

bool dashboard_model_resume(dashboard_model_t *model)
{
    if(model == NULL || model->run != DASHBOARD_PAUSED) return false;
    model->run = DASHBOARD_RUNNING;
    return true;
}

bool dashboard_model_recover(dashboard_model_t *model)
{
    if(model == NULL || model->run != DASHBOARD_FAULT) return false;
    model->run = DASHBOARD_PAUSED;
    model->error = "none";
    return true;
}

bool dashboard_model_reset(dashboard_model_t *model)
{
    if(model == NULL) return false;
    return dashboard_model_init(model, model->low, model->high);
}

const char *dashboard_level_name(dashboard_level_t level)
{
    switch(level) {
        case DASHBOARD_LOW: return "LOW";
        case DASHBOARD_HIGH: return "HIGH";
        default: return "UNKNOWN";
    }
}

const char *dashboard_run_name(dashboard_run_t run)
{
    switch(run) {
        case DASHBOARD_RUNNING: return "RUNNING";
        case DASHBOARD_PAUSED: return "PAUSED";
        case DASHBOARD_FAULT: return "FAULT";
        default: return "INVALID";
    }
}
