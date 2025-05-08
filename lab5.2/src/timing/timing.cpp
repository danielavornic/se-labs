
#include "timing.h"

static unsigned long lastUpdateTimeMs = 0;

void initTiming()
{
    lastUpdateTimeMs = millis();
}

bool isUpdateDue()
{
    return (millis() - lastUpdateTimeMs >= UPDATE_INTERVAL);
}

void markUpdateTime()
{
    lastUpdateTimeMs = millis();
}
