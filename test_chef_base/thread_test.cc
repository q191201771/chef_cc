#include "_thread.h"
#include <boost/thread/thread.hpp>
#include <boost/date_time.hpp>
#include <iostream>
//using namespace boost;
using namespace boost::gregorian;

void fun()
{
    int k = 0;
    for (int i = 0; i < 10000; ++i) {
        for (int j = 0; j < 10000; ++j) {
            k += j;
        }
    }
    printf("leave fun().\n");
}

int main()
{
    boost::thread *t = new boost::thread(fun);
    t->detach();
    delete t;
    printf("after delete.\n");
    getchar();
    return 0;

    printf("%d\n", current_thread::get_tid());    
    printf("%d\n", current_thread::get_tid());    
    std::cout << boost::this_thread::get_id() << std::endl;
    std::cout << boost::this_thread::get_id() << std::endl;

    for (int i = 0 ; i < 128; ++i) {
        boost::posix_time::ptime p1 = boost::posix_time::second_clock::local_time();
        //std::cout << p1 << std::endl;
        boost::posix_time::ptime p2 = boost::posix_time::microsec_clock::local_time();
        //std::cout << p2 << std::endl;
        printf("%s\n", boost::posix_time::to_iso_string(p1).c_str());
        printf("%s\n", boost::posix_time::to_iso_extended_string(p2).c_str());
    }

    return 0;
}
