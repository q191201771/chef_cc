#include "_time.h"
#include <time.h>
#include <stdio.h>
#include <sys/time.h>

void time::format_now_time1(char *buf)
{
    if (!buf) {
        return;
    }

    time_t time1 = ::time(NULL);
    struct tm tm1;
    ::localtime_r(&time1, &tm1);

    snprintf(buf, 16, "%4d%02d%02d-%02d%02d%02d",
            tm1.tm_year + 1900,
            tm1.tm_mon + 1,
            tm1.tm_mday,
            tm1.tm_hour,
            tm1.tm_min,
            tm1.tm_sec);
}

void time::format_now_time2(char *buf)
{
    if (!buf) {
        return;
    }

    time_t time1 = ::time(NULL);
    struct tm tm1;
    ::localtime_r(&time1, &tm1);

    snprintf(buf, 18, "%4d%02d%02d %02d:%02d:%02d",
            tm1.tm_year + 1900,
            tm1.tm_mon + 1,
            tm1.tm_mday,
            tm1.tm_hour,
            tm1.tm_min,
            tm1.tm_sec);
}

void time::format_now_time3(char *buf)
{
    if (!buf) {
        return;
    }

    static __thread int64_t last_sec = 0;
    int64_t secs = 0;
    int64_t msecs = 0;
    now(&secs, &msecs);
    if (secs != last_sec) {
        struct tm tm1;
        time_t secs_tt = (time_t)secs;
        ::localtime_r(&secs_tt, &tm1);	

        snprintf(buf, 18, "%4d%02d%02d %02d:%02d:%02d",
                tm1.tm_year + 1900,
                tm1.tm_mon + 1,
                tm1.tm_mday,
                tm1.tm_hour,
                tm1.tm_min,
                tm1.tm_sec);
    }

    snprintf(buf + 17, 8, ".%06ld", msecs);
}

int64_t time::now(int64_t *secs, int64_t *msecs)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int64_t local_secs = tv.tv_sec;//necessary up to int64_t
    if (secs) {
        *secs = tv.tv_sec;
    }
    if (msecs) {
        *msecs = tv.tv_usec;
    }
    return local_secs * 1000 * 1000 + tv.tv_usec;
}

