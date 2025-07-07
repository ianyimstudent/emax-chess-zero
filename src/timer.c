#include "timer.h"

#if defined(__APPLE__)
    #include <mach/mach_time.h>
    void timer_start(Timer *t) {
        t->start_ticks = mach_absolute_time();
    }
    uint64_t timer_elapsed_ms(const Timer *t) {
        uint64_t end = mach_absolute_time();
        mach_timebase_info_data_t info;
        mach_timebase_info(&info);
        return ((end - t->start_ticks) * info.numer / info.denom) / 1000000;
    }
#elif defined(_WIN32)
    #include <windows.h>
    static LARGE_INTEGER frequency;

    void timer_start(Timer *t) {
        static int initialized = 0;
        if (!initialized) {
            QueryPerformanceFrequency(&frequency);
            initialized = 1;
        }
        LARGE_INTEGER start;
        QueryPerformanceCounter(&start);
        t->start_ticks = start.QuadPart;
    }

    uint64_t timer_elapsed_ms(const Timer *t) {
        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);
        return (uint64_t)(((now.QuadPart - t->start_ticks) * 1000) / frequency.QuadPart);
    }
#else
    #include <sys/time.h>
    void timer_start(Timer *t) {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        t->start_ticks = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    }

    uint64_t timer_elapsed_ms(const Timer *t) {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        uint64_t now = tv.tv_sec * 1000 + tv.tv_usec / 1000;
        return now - t->start_ticks;
    }
#endif