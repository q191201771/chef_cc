#include "chef_netstat.h"
#include "chef_time.h"
#include "current_thd.h"
#include <stdio.h>
#include <assert.h>

int main()
{
    printf(">chef_netstat_test.\n");
    uint64_t in_bytes_prev = 0;
    uint64_t out_byte_prev = 0;
    int64_t prev_time_ms = 0;
    int64_t now_time_ms = 0;
    uint64_t in_bytes = 0;
    uint64_t out_bytes = 0;
    assert(chef::netstat::fetch_io_bytes_at_this_moment("abcdefg", &in_bytes,
            &out_bytes, &now_time_ms) == -1);
    for (; ; ) {
    //for (int i = 0; i < 10; ++i) {
        int ret = chef::netstat::fetch_io_bytes_at_this_moment("eth0", &in_bytes,
                &out_bytes, &now_time_ms);
        if (ret != 0) {
            printf("chef::netstat::fetch_io_bytes_at_this_moment ret != 0.\n");
            break;
        }
        //printf("%lu %lu %ld\n", in_bytes, out_bytes, now_time_ms);
        /// skip first time
        if (prev_time_ms != 0) {
            printf("-----\nin:%lu kb/s\nout:%lu kb/s\n", 
                    (in_bytes - in_bytes_prev) * 8 * 1000 / 1024 / (now_time_ms - prev_time_ms),
                    (out_bytes - out_byte_prev) * 8 * 1000 / 1024 / (now_time_ms - prev_time_ms));
        }

        in_bytes_prev = in_bytes;
        out_byte_prev = out_bytes;
        prev_time_ms = now_time_ms;
        chef::current_thd::sleep_ms(1000);
    }
    printf("<chef_netstat_test.\n");
    return 0;
}

