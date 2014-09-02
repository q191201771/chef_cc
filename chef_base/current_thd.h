#ifndef _CHEF_CHEF_BASE_CURRENT_THD_H_
#define _CHEF_CHEF_BASE_CURRENT_THD_H_

#include <stdint.h>

namespace chef
{
namespace current_thd
{
    /// every thread call syscall only at first time
    int  gettid();

    /// call ::pthread_exit inside
    void exit();
    
    /// @ return
    ///   0 succ sleeping after spefic interval
    ///  -1 fail
    int  sleep_ms(int64_t var);
    
    /// @ return 
    ///  return errno in errno.h
    ///  it is thread-local  
    int  get_last_errno();

} /// namespace current_thd
} /// namespace chef

#endif /// _CHEF_CHEF_BASE_CURRENT_THD_H_

