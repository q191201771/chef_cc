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

    /**
     * @function: bytes2human
     * @param:
     *   n: how much bytes
     * @return:
     *   bytes2human(768) = "768.0B"
     *   bytes2human(10000) = "9.8K"
     *   bytes2human(100001221) = "95.4M"
     *   more info see test_chef_base/snippet_test.cc
     */
    static std::string bytes2human(uint64_t n) {
        char units[] = {'B', 'K', 'M', 'G', 'T', 'P', 'E'};//, 'Z', 'Y'};
        int index = 0;
        for (; n >> (index * 10); ++index) {
            if (index == 6) { ///  can't do n >> 70
                ++index;
                break;
            }
        }
        index = index > 0 ? index - 1 : index;
        char buf[128] = {0};
        snprintf(buf, 127, "%.1f%c", 
                float(n) / (index ? 1UL << (index) * 10 : 1),
                units[index]);
        return std::string(buf);
    }

}; /// class snippet

} /// namespace chef

#endif /// _CHEF_CHEF_BASE_SNIPPET_H_

