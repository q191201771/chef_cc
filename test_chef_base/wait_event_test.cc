#include <stdio.h>
#include "wait_event.h"

int main()
{
    printf(">wait_event_test.\n");
    chef::wait_event we;
    we.notify();
    we.wait();

    chef::wait_event we2;
    we2.wait_for(1500);
    printf("<wait_event_test.\n");

    return 0;
}

