#include "chef_netstat.h"
#include "chef_time.h"
#include "chef_buffer.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

namespace chef
{

int netstat::fetch_io_bytes_at_this_moment(const char *interface, uint64_t *in_bytes,
        uint64_t *out_bytes, int64_t *now_ms)
{
    if (!interface || !in_bytes || !out_bytes || !now_ms) {
        fprintf(stderr, "%s:%d.", __func__, __LINE__);
        return -1;
    }

    *now_ms = chef::time::now(NULL, NULL) / 1000;
    return netstat::fetch_io_bytes_at_this_moment(interface, in_bytes, out_bytes);
}

int netstat::fetch_io_bytes_at_this_moment(const char *interface, uint64_t *in_bytes,
        uint64_t *out_bytes)
{
    if (!interface || !in_bytes || !out_bytes) {
        fprintf(stderr, "%s:%d.", __func__, __LINE__);
        return -1;
    }

    FILE *fp = fopen("/proc/net/dev", "r");
    if (!fp) {
        fprintf(stderr, "%s:%d,!fp.\n", __func__, __LINE__);
        return -1;
    }

    chef::buffer buf(4096); /// fixed?
    int file_len = fread(buf.write_pos(), 1, 4096, fp);
    fclose(fp);
    if (file_len <= 0) {
        fprintf(stderr, "%s:%d,fread fail,file_len=%d", __func__, __LINE__, 
                file_len);
        return -1;
    }
    buf.seek_write(file_len);

/// *skip 
/// Inter-|   Receive                                                |  Transmit
    char *pos1 = buf.find_eol();
    char *pos2 = NULL;
    if (!pos1) {
        fprintf(stderr, "%s:%d,skip line 1 fail.\n", __func__, __LINE__);
        return -1;
    }
    buf.erase(pos1 - buf.read_pos() + 1);
/// *skip
///  face |bytes    packets errs drop fifo frame compressed multicast|bytes    packets errs drop fifo colls carrier compressed
    pos1 = buf.find_eol();
    if (!pos1) {
        fprintf(stderr, "%s:%d,skip line 2 fail.\n", __func__, __LINE__);
        return -1;
    }
    buf.erase(pos1 - buf.read_pos() + 1);

    /// *find 'interface'
    pos1 = buf.find(interface, strlen(interface));
    if (!pos1) {
        fprintf(stderr, "%s:%d,find interface(%s) fail.\n", __func__, __LINE__, interface);
        return -1;
    }
    for (; ; ) {
        pos2 = buf.find_eol();
        if (!pos2) {
            fprintf(stderr, "%s:%d,find interface fail.\n", __func__, __LINE__);
            return -1;
        }
        /// not our 'interface'
        if (pos2 < pos1) {
            buf.erase(pos2 - buf.read_pos() + 1);
            continue;
        }

//        printf("<debug>");
//        for (char *ch = buf.read_pos(); ch != pos2; ++ch) {
//            printf("%c", *ch);
//        }
//        printf("</debug>\n");

        /// skip 'interface',because it may contain digit char!
        pos1 = buf.find(":", 1);
        if (!pos1) {
            fprintf(stderr, "%s:%d.\n", __func__, __LINE__);
            return -1;
        }
        buf.erase(pos1 - buf.read_pos());

/// example
///  eth0: 3901041572 40470868    0   17    0     0          0  13184753 456828555 6919264    0    0    0     0       0          0
        /// we concern 3901041572 456828555
        const int in_bytes_index = 0;
        const int out_bytes_index = 8;
        int digit_index = 0;
        char *digit_begin_pos = NULL;
        for (int i = 0; i < pos2 - buf.read_pos() + 1; ++i) {
            char ch = *(buf.read_pos() + i);
            if (isdigit(ch) != 0) { /// bingo
                if (!digit_begin_pos) {
                    digit_begin_pos = buf.read_pos() + i;
                } else {
                    /// inside digit,do nothing
                }
            } else {
                if (!digit_begin_pos) {
                    /// havn't begin,do nothing
                } else {
                    /// parse to num-data
                    char num_data_str[32] = {0};
                    uint64_t num_data = 0;
                    memcpy(num_data_str, digit_begin_pos, buf.read_pos() + i - digit_begin_pos);
                    sscanf(num_data_str, "%lu", &num_data);
                    //printf("\nnum=%lu\n", num_data);
                    digit_begin_pos = NULL;
                    if (digit_index == in_bytes_index) {
                        *in_bytes = num_data; 
                        (void)in_bytes;
                    } else if (digit_index == out_bytes_index) {
                        *out_bytes = num_data;
                        (void)out_bytes;
                    }
                    ++digit_index;
                }
            } 
        }
        break;
    }
    return 0;
}

} /// namespace chef

