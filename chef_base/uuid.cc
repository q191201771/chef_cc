#include "uuid.h"
#include <stdio.h>

namespace chef
{
namespace uuid
{
    std::string create()
    {
        FILE *fp = fopen("/proc/sys/kernel/random/uuid", "r");
        if (!fp) {
            return std::string();
        }
        char *line = NULL;
        size_t len = 0;
        ssize_t read;
        read = getline(&line, &len, fp);
        if (read == -1) {
            printf("getline fail.\n");
            fclose(fp);
            return std::string();
        }
        std::string ret(line, 36);
        //printf("ERASECHEF %s\n", ret.c_str());
        //ret += '\0';
        free(line);
        fclose(fp);
        return ret;
    }

} /// namespace uuid
} /// namespace chef

