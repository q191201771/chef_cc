#include "current_thd.h"
#include <unistd.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>

namespace chef
{
namespace current_thd
{
    int gettid()
    {
        static __thread int tid = 0;
        if (tid == 0) {
            tid = static_cast<int>(syscall(__NR_gettid));
        }
        return tid;
    }
 
    void exit()
    {
        pthread_exit(NULL);
    }

    int sleep_ms(int64_t var) 
    {
        if (var < 0) {
            return -1;
        }
        timespec ts = { var / 1000, (var % 1000) * 1000000 };
        while (nanosleep(&ts, &ts) == -1 && get_last_errno() == EINTR);
        return 0;
    }

    int get_last_errno()
    {
        return errno;
    }

} /// namespace current_thd
} /// namespace chef

