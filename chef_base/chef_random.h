#ifndef _CHEF_CHEF_BASE_RANDOM_H_
#define _CHEF_CHEF_BASE_RANDOM_H_

#include <stdint.h>
#include <stdlib.h>

namespace chef
{
namespace random
{
    /// @return [-MAX,MAX]
    int32_t next_signed();
    
    /// @return 0 if n=0,otherwise [-(n-1),(n-1)]
    int32_t uniform_signed(uint32_t n);

    /// @return [0,max] 
    uint32_t next_unsigned();

    /// @return 0 if n=0,otherwise [0,(n-1)]
    uint32_t uniform_unsigned(uint32_t n);

} /// namespace random
} /// namespace chef

#endif /// _CHEF_CHEF_BASE_RANDOM_H_

