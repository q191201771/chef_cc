#ifndef _CHEF_CHEF_BASE_NETSTAT_H_
#define _CHEF_CHEF_BASE_NETSTAT_H_

/// @ only for linux

#include <stdint.h>

namespace chef
{

class netstat
{
public:

    /**
     * @return  0 succ,-1 fail
     * @param
     *   interface           like 'eth0'
     *   in_bytes/out_bytes  like '3924811357'
     * @brief
     *   fetch twice,rate = subtraction bytes / duration
     *   more usage see test_chef_base/chef_netstat_test.cc
     */
    static int fetch_io_bytes_at_this_moment(const char *interface, 
            uint64_t *in_bytes,
            uint64_t *out_bytes);

    /**
     * @brief
     *   add an output param [now_ms] to figure out duration more convenient
     *   more usage see test_chef_base/chef_netstat_test.cc
     */
    static int fetch_io_bytes_at_this_moment(const char *interface, 
            uint64_t *in_bytes,
            uint64_t *out_bytes,
            int64_t *now_ms);
}; /// class netstat

} /// namespace chef

#endif /// _CHEF_CHEF_BASE_NETSTAT_H_

