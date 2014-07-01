#ifndef CHEF_TIME_H_
#define CHEF_tIME_H_

#include <stdint.h>

/**
 * @switch to boost::date_time
 *
 * format 1 & 2 have sec,have no msec,their string format diff
 * format 3 have msec
 *
 * format 1. len 16, like 20140512-135025,log file name,etc
 * format 2. len 18, like 20140512 13:50:25,log info,etc
 * format 3. len 25, like 20140512 13:50:25.123456,log info,etc
 */

class time
{
public:
    static void format_now_time1(char *buf);
    static void format_now_time2(char *buf);
    static int64_t now(int64_t *secs, int64_t *msecs);
    static void format_now_time3(char *buf);
};

#endif

