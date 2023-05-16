#ifndef TIME_HPP
#define TIME_HPP

#include <time.h>

#define NS_PER_SECOND (1000000000)
#define NS_PER_MILLISECOND (1000000)

#define NOW() ({ \
    timespec ts; \
    timespec_get(&ts, TIME_UTC); \
    ((ts.tv_sec * NS_PER_SECOND) + ts.tv_nsec);})

#endif