#include "chef_random.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

namespace chef
{
namespace random
{
    
int32_t next_signed()
{
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd == -1) {
        /// CHEFFIX
        return -1;
    }
    int32_t random;
    int32_t total_read_len = 0;
    while(total_read_len < (int32_t)sizeof(random)) {
        ssize_t read_len = read(fd, (uint8_t *)&random + total_read_len,
                sizeof(int32_t) - total_read_len);
        total_read_len += read_len;
    }

    close(fd);
    return random;
}

int32_t uniform_signed(uint32_t n) { return n == 0 ? 0 : next_signed() % n; }
uint32_t next_unsigned() { return abs(next_signed()); }
uint32_t uniform_unsigned(uint32_t n) { return n == 0 ? 0 : next_unsigned() % n; }

} /// namespace random
} /// namespace chef

