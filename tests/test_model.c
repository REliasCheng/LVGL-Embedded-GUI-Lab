#include "dashboard_model.h"

#include <assert.h>
#include <limits.h>
#include <stdio.h>

int main(void)
{
    dashboard_model_t m;
    assert(!dashboard_model_init(NULL, 1000, 3000));
    assert(!dashboard_model_init(&m, 3000, 3000));
    assert(!dashboard_model_init(&m, 3001, 3000));
    assert(!dashboard_model_init(&m, 1000, 4096));
    assert(dashboard_model_init(&m, 1000, 3000));
    assert(m.level == DASHBOARD_UNKNOWN && m.run == DASHBOARD_RUNNING);
    assert(m.accepted == 0 && !m.has_valid);
    assert(dashboard_model_sample(&m, 2000));
    assert(m.level == DASHBOARD_UNKNOWN && m.sequence == 1);
    assert(dashboard_model_sample(&m, 3000) && m.level == DASHBOARD_HIGH);
    assert(dashboard_model_sample(&m, 2000) && m.level == DASHBOARD_HIGH);
    assert(dashboard_model_sample(&m, 1000) && m.level == DASHBOARD_LOW);
    assert(dashboard_model_sample(&m, 0) && m.level == DASHBOARD_LOW);
    assert(dashboard_model_sample(&m, 4095) && m.level == DASHBOARD_HIGH);
    assert(m.accepted == 6 && m.sequence == 6);
    assert(dashboard_model_pause(&m));
    assert(!dashboard_model_pause(&m));
    assert(!dashboard_model_sample(&m, 1000) && m.sequence == 6);
    assert(dashboard_model_resume(&m));
    assert(!dashboard_model_resume(&m));
    assert(!dashboard_model_sample(&m, 4096));
    assert(m.run == DASHBOARD_FAULT && m.last_valid == 4095);
    assert(m.rejected == 1 && m.accepted == 6 && m.sequence == 6);
    assert(!dashboard_model_sample(&m, 1));
    assert(!dashboard_model_resume(&m));
    assert(dashboard_model_recover(&m) && m.run == DASHBOARD_PAUSED);
    assert(!dashboard_model_recover(&m));
    assert(dashboard_model_resume(&m));
    assert(dashboard_model_sample(&m, 0) && m.level == DASHBOARD_LOW);
    assert(dashboard_model_reset(&m));
    assert(m.run == DASHBOARD_RUNNING && m.level == DASHBOARD_UNKNOWN);
    assert(m.accepted == 0 && m.rejected == 0 && !m.has_valid);
    assert(dashboard_model_init(&m, 0, 4095));
    assert(dashboard_model_sample(&m, 0) && m.level == DASHBOARD_LOW);
    assert(dashboard_model_sample(&m, 4095) && m.level == DASHBOARD_HIGH);
    assert(!dashboard_model_sample(&m, -1) && m.run == DASHBOARD_FAULT);
    assert(dashboard_model_reset(&m));
    m.accepted = UINT32_MAX;
    m.sequence = UINT32_MAX;
    assert(dashboard_model_sample(&m, 42));
    assert(m.accepted == UINT32_MAX && m.sequence == UINT32_MAX);
    m.rejected = UINT32_MAX;
    assert(!dashboard_model_sample(&m, -1) && m.rejected == UINT32_MAX);
    assert(!dashboard_model_sample(NULL, 0));
    assert(!dashboard_model_pause(NULL));
    assert(!dashboard_model_resume(NULL));
    assert(!dashboard_model_recover(NULL));
    assert(!dashboard_model_reset(NULL));
    puts("model: PASS");
    return 0;
}
