#ifndef CHEF_TIME_H_
#define CHEF_tIME_H_

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
     * @ param
     *  secs  [out] NULL means don't obtain it
     *  msecs [out] NULL means don't obtain it
     */ 
    int64_t now(int64_t *secs /*out*/, int64_t *msecs /*out*/);    

    /// len 16, include '\0' in the end, like 20140512-135025
    std::string now_format1();

    /// len 18, include '\0' in the end, like 20140512 13:50:25
    std::string now_format2();

    /// len 25, include '\0' in the end, like 20140512 13:50:25.123456
    std::string now_format3();

} /// namespace time
} /// namespace chef

#endif

