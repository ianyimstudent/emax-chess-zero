#ifndef TIMER_H
#define TIMER_H
#include <stdint.h>

typedef struct {
    uint64_t start_ticks;
} Timer;

void timer_start(Timer *t);
uint64_t timer_elapsed_ms(const Timer *t);
#endif