#include "uuid.h"
#include <assert.h>
#include <set>
#include <vector>
#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/atomic.hpp>

std::set<std::string> g_uuids;
boost::mutex g_mutex;

void fun()
{
    for (int i = 0; i < 1024; ++i) {
        boost::lock_guard<boost::mutex> guard(g_mutex);
        std::string uuid = chef::uuid::create();
        assert(uuid != std::string());
        assert(g_uuids.find(uuid) == g_uuids.end());
        g_uuids.insert(uuid);
    }
}

int main()
{
    printf(">uuid_test.\n");
    std::string str = chef::uuid::create();
    assert(str.size() == 37);
    assert(str[14] == '4');
    printf("    %s", str.c_str());

    typedef boost::shared_ptr<boost::thread> thread_ptr;
    std::vector<thread_ptr > threads;
    for (int i = 0; i < 16; ++i) {
        threads.push_back(thread_ptr(new boost::thread(&fun)));
    }
    for (int i = 0; i < 16; ++i) {
        threads[i]->join();
    }
    assert(g_uuids.size() == 1024 * 16);
    printf("<uuid_test.\n");
    return 0;
}

