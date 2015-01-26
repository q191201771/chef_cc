#ifndef _CHEF_CHEF_BASE_TIME_H_
#define _CHEF_CHEF_BASE_TIME_H_

#include <stdint.h>
#include <string>

/**
 * @ switch to boost::date_time
 */

namespace chef
{
namespace time 
{
    /**
     * @param
     *  secs  [out] NULL means don't obtain it
     *  msecs [out] NULL means don't obtain it
     * @return
     *  us
     * @tips
     *  1s(second) = 1000ms(millisecond) = 1000000us(microsecond)
     */ 
    int64_t now(int64_t *secs /*out*/, int64_t *msecs /*out*/);    

    /// @return string.length=15, like 20140512-135025
    std::string now_format1();

    /// @return string.length=17, like 20140512 13:50:25
    std::string now_format2();

    /// @return string.length=24, like 20140512 13:50:25.123456
    std::string now_format3();

} /// namespace time
} /// namespace chef

#endif /// _CHEF_CHEF_BASE_TIME_H_

