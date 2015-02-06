#include "chef_snippet.hpp"
#include <assert.h>
#include <vector>

int main()
{
    printf(">snippet_test.\n");
    
    std::vector<std::string> urls;
    urls.push_back("localhost");
    urls.push_back("1.2.3.4");
    urls.push_back("http://www.baidu.com");
    urls.push_back("www.baidu.com");
    urls.push_back("baidu.com");
    urls.push_back("baidu");
    std::vector<std::string>::iterator iter = urls.begin();
    for (; iter != urls.end(); ++iter) {
        printf("    %s:%s\n", (*iter).c_str(), chef::snippet::get_host_by_name(*iter).c_str());
    }

    assert(chef::snippet::bytes2human(768) == "768.0B");
    assert(chef::snippet::bytes2human(10000) == "9.8K");
    assert(chef::snippet::bytes2human(100001221) == "95.4M");
    assert(chef::snippet::bytes2human(1000) == "1000.0B");
    assert(chef::snippet::bytes2human(1023) == "1023.0B");
    assert(chef::snippet::bytes2human(1024) == "1.0K");
    assert(chef::snippet::bytes2human(1025) == "1.0K");
    assert(chef::snippet::bytes2human(1000UL * 1000) == "976.6K");
    assert(chef::snippet::bytes2human(1024UL * 1024) == "1.0M");
    assert(chef::snippet::bytes2human(1000UL * 1000 * 1000) == "953.7M");
    assert(chef::snippet::bytes2human(1024UL * 1024 * 1024) == "1.0G");
    assert(chef::snippet::bytes2human(1024UL * 1024 * 1024 + 1000UL * 1000 * 1000) == "1.9G");
    assert(chef::snippet::bytes2human(1000UL * 1000 * 1000 * 1000) == "931.3G");
    assert(chef::snippet::bytes2human(1024UL * 1024 * 1024 * 1024) == "1.0T");
    assert(chef::snippet::bytes2human(1024UL * 1024 * 1024 * 1024 * 1024) == "1.0P");
    assert(chef::snippet::bytes2human(1024UL * 1024 * 1024 * 1024 * 1024 * 1024) == "1.0E");
    assert(chef::snippet::bytes2human(1024UL * 1024 * 1024 * 1024 * 1024 * 1024 * 15) == "15.0E");
    assert(chef::snippet::bytes2human(0UL - 1) == "16.0E");
    assert(chef::snippet::bytes2human(18446744073709551615UL) == "16.0E");

    printf("<snippet_test.\n");
    return 0;
}
