#ifndef API_DELAY_H
#define API_DELAY_H

#include <stdbool.h>
#include <stdint.h>

extern volatile uint64_t total_ms;

typedef struct
{
    uint64_t startTime;
    uint64_t duration;
    bool running;
} delay_t;

void delayInit(delay_t *delay, uint64_t duration);

bool delayRead(delay_t *delay);

void delayWrite(delay_t *delay, uint64_t duration);

#endif