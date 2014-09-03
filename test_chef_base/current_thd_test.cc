#include "current_thd.h"
#include "current_proc.h"
#include "_time.h"
#include <assert.h>

int main()
{
    printf(">current_thd_test.\n");
    assert(chef::current_thd::get_last_errno() == 0);
    assert(chef::current_proc::getpid() == chef::current_thd::gettid()); 
    printf("    chef::current_thd::sleep_ms(1234).\n");
    int64_t now1 = chef::time::now(NULL, NULL);
    chef::current_thd::sleep_ms(1234);
    int64_t now2 = chef::time::now(NULL, NULL);
    printf("    truely sleep_ms(%ld.%ld).\n", (now2 - now1) / 1000, 
            (now2 - now1) % 1000);
    printf("<current_thd_test.\n");
    chef::current_thd::exit();
    assert(0);
    return 0;
}

