#ifndef _CHEF_CHEF_BASE_SNIPPET_H_
#define _CHEF_CHEF_BASE_SNIPPET_H_

/**
 * @NOTICE
 *  this class temply wrap some snippets, it may add/del frequently.
 *  so copy the impl which you need to your code is an better way to use.
 */

#include <string>
#include <netdb.h>
extern int h_errno;

namespace chef {

class snippet {
public:
    /**
     * @function: get_host_by_name
     * @param:
     *  name: url,like "www.baidu.com",more info see
     *        test_chef_base/chef_snippet_test.cc
     * @return: succ like "220.181.111.188",otherwise ""
     *
     */
    static std::string get_host_by_name(std::string name) {
        struct hostent *ht = gethostbyname(name.c_str());
        if (!ht || ht->h_length <= 0) {
            fprintf(stderr, "gethostbyname(%s) fail,reason:%s\n", 
                    name.c_str(), hstrerror(h_errno));
            return "";
        }
        char result[128] = {0};
        snprintf(result, 128, "%hhu.%hhu.%hhu.%hhu",
                (uint8_t)ht->h_addr_list[0][0],
                (uint8_t)ht->h_addr_list[0][1],
                (uint8_t)ht->h_addr_list[0][2],
                (uint8_t)ht->h_addr_list[0][3]);
        return std::string(result);
    }
}; /// class snippet

} /// namespace chef

#endif /// _CHEF_CHEF_BASE_SNIPPET_H_

