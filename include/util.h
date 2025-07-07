#ifndef UTIL_H
#define UTIL_H

#if defined(__GNUC__) || defined(__clang__)
    // GCC / CLANG
    #define likely(x)   __builtin_expect((x), 1)
    #define unlikely(x) __builtin_expect((x), 0)
#else
    #define likely(x)   (x)
    #define unlikely(x) (x)
#endif

#endif