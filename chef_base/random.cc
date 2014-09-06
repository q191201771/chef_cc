#include "random.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

namespace chef
{
namespace random
{
    
uint32_t obtain()
{
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd == -1) {
        /// CHEFFIX
        return -1;
    }
    uint32_t random;
    uint32_t total_read_len = 0;
    while(total_read_len < (uint32_t)sizeof(random)) {
        ssize_t read_len = read(fd, (uint8_t *)&random + total_read_len,
                sizeof(uint32_t) - total_read_len);
        total_read_len += read_len;
    }

    close(fd);
    return random;
}

} /// namespace random
} /// namespace chef

