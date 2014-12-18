#include "chef_snippet.hpp"
#include <vector>

int main()
{
    printf(">chef_snippet_test.\n");
    
    std::vector<std::string> urls;
    urls.push_back("localhost");
    urls.push_back("1.2.3.4");
    urls.push_back("http://www.baidu.com");
    urls.push_back("www.baidu.com");
    urls.push_back("baidu.com");
    urls.push_back("baidu");
    std::vector<std::string>::iterator iter = urls.begin();
    for (; iter != urls.end(); ++iter) {
        printf("%s:%s\n", (*iter).c_str(), chef::snippet::get_host_by_name(*iter).c_str());
    }

    printf("<chef_snippet_test.\n");
    return 0;
}
