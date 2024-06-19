#include "API_delay.h"

void delayInit(delay_t *delay, uint64_t duration)
{
    delay->duration = duration;
    delay->running = false;
    delay->startTime = 0;
}

bool delayRead(delay_t *delay)
{
    bool timerFinish = false;

    if (delay->running == false)
    {
        delay->startTime = total_ms;
        delay->running = true;
    }
    else
    {
        if (total_ms - delay->startTime >= delay->duration)
        {
            delay->running = false;
            delay->startTime = 0;
            timerFinish = true;
        }
    }
    return timerFinish;
}

void delayWrite(delay_t *delay, uint64_t duration)
{
    delay->duration = duration;
}