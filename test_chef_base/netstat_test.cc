#include "chef_netstat.h"
#include "chef_time.h"
#include "chef_current_thd.h"
#include "chef_snippet.hpp"
#include <stdio.h>
#include <assert.h>

int main()
{
    printf(">netstat_test.\n");
    uint64_t in_bytes_prev = 0;
    uint64_t out_byte_prev = 0;
    int64_t prev_time_ms = 0;
    int64_t now_time_ms = 0;
    uint64_t in_bytes = 0;
    uint64_t out_bytes = 0;
    assert(chef::netstat::fetch_io_bytes_at_this_moment("abcdefg", &in_bytes,
            &out_bytes, &now_time_ms) == -1);
    //for (; ; ) {
    for (int i = 0; i < 3; ++i) {
        int ret = chef::netstat::fetch_io_bytes_at_this_moment("eth0", &in_bytes,
                &out_bytes, &now_time_ms);
        if (ret != 0) {
            printf("    chef::netstat::fetch_io_bytes_at_this_moment ret != 0.\n");
            break;
        }
        //printf("%lu %lu %ld\n", in_bytes, out_bytes, now_time_ms);
        /// skip first time
        if (prev_time_ms != 0) {
            printf("    -----\n    in:%s/s\n    out:%s/s\n", 
                    chef::snippet::bytes2human(((in_bytes - in_bytes_prev) * 1000) / (now_time_ms - prev_time_ms)).c_str(),
                    chef::snippet::bytes2human(((out_bytes - out_byte_prev) * 1000) / (now_time_ms - prev_time_ms)).c_str());
        }

        in_bytes_prev = in_bytes;
        out_byte_prev = out_bytes;
        prev_time_ms = now_time_ms;
        chef::current_thd::sleep_ms(1000);
    }
    printf("<netstat_test.\n");
    return 0;
}

