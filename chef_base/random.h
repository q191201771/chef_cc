#ifndef _CHEF_CHEF_BASE_RANDOM_H_
#define _CHEF_CHEF_BASE_RANDOM_H_

#include <stdint.h>
#include <stdlib.h>

namespace chef
{
namespace random
{
    /// [-MAX,MAX]
    int32_t next_signed();
    
    /// [-(n-1),(n-1)]
    int32_t uniform_signed(uint32_t n) { return next_signed() % n; }

    /// [0,MAX]
    uint32_t next_unsigned() { return abs(next_signed()); }

    /// [0,(n-1)]
    uint32_t uniform_unsigned(uint32_t n) { return next_unsigned() % n; }
}

} /// namespace chef

#endif /// _CHEF_CHEF_BASE_RANDOM_H_

