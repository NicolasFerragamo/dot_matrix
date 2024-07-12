#include "API_delay.h"

/**
 * @brief   Initialize delay struct
 *          Set delay duration
 * @param delay 
 * @param duration 
 */
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
        delay->startTime = totalMillis;
        delay->running = true;
    }
    else
    {
        if (totalMillis - delay->startTime >= delay->duration)
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