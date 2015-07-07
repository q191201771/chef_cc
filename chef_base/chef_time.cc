#include "chef_time.h"
#include <time.h>
#include <stdio.h>
#include <sys/time.h>

namespace chef
{
namespace time
{

std::string now_format1()
{
    time_t time1 = ::time(NULL);
    struct tm tm1;
    ::localtime_r(&time1, &tm1);

    char buf[16] = {0};
    snprintf(buf, 16, "%4d%02d%02d-%02d%02d%02d",
            tm1.tm_year + 1900,
            tm1.tm_mon + 1,
            tm1.tm_mday,
            tm1.tm_hour,
            tm1.tm_min,
            tm1.tm_sec);
    return std::string(buf);
}

std::string now_format2()
{
    time_t time1 = ::time(NULL);
    struct tm tm1;
    ::localtime_r(&time1, &tm1);

    char buf[32] = {0};
    snprintf(buf, 18, "%4d%02d%02d %02d:%02d:%02d",
            tm1.tm_year + 1900,
            tm1.tm_mon + 1,
            tm1.tm_mday,
            tm1.tm_hour,
            tm1.tm_min,
            tm1.tm_sec);
    return std::string(buf);
}

std::string now_format3()
{
    static __thread char buf[32] = {0};
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
    return std::string(buf);
}

int64_t now(int64_t *secs, int64_t *msecs)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int64_t local_secs = tv.tv_sec;//necessary up to int64_t
    if (secs) {
        *secs = tv.tv_sec;
    }
    if (msecs) {
        *msecs = tv.tv_usec / 1000;
    }
    return local_secs * 1000 * 1000 + tv.tv_usec;
}

} /// namespace time
} /// namespace chef

#if 0
#include <stdio.h>

int main()
{
    int64_t sec;
    int64_t msec;
    int64_t tick;
    tick = chef::time::now(&sec, &msec);
    printf("%ld,%ld,%ld\n", tick, sec, msec);
    printf("%s\n", chef::time::now_format1().c_str());
    printf("%s\n", chef::time::now_format2().c_str());
    printf("%s\n", chef::time::now_format3().c_str());
    printf("%ld\n", chef::time::now(NULL, NULL));
    return 0;
}

#endif

