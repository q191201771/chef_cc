#include "chef_time.h"
#include <assert.h>
#include <stdio.h>

int main()
{
    printf(">time_test.\n");
    int64_t ret, secs, msecs;
    ret = chef::time::now(&secs, &msecs);
    printf("%ld,%ld,%ld\n%s\n%s\n%s\n",
            ret, secs, msecs,
            chef::time::now_format1().c_str(),
            chef::time::now_format2().c_str(),
            chef::time::now_format3().c_str());
    assert(chef::time::now_format1().length() == 15);
    assert(chef::time::now_format2().length() == 17);
    assert(chef::time::now_format3().length() == 24);
    printf("<time_test.\n");
    return 0;
}

