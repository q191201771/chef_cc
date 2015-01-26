#include <stdio.h>
#include "chef_wait_event.h"

int main()
{
    printf(">wait_event_test.\n");
    chef::wait_event we;
    we.notify();
    we.wait();

    chef::wait_event we2;
    we2.wait_for(500);
    
    chef::wait_event we3;
    we3.notify();
    we3.wait_for(0);
    printf("<wait_event_test.\n");

    return 0;
}

