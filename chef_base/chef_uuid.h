#ifndef _CHEF_CHEF_BASE_UUID_H_
#define _CHEF_CHEF_BASE_UUID_H_

#include <string>

namespace chef
{
namespace uuid
{
    /// 8-4-4-4-12
    /// total 36
    /// return std::string() if failed.
    std::string create();

} /// namespace uuid
} /// namespace chef

#endif /// _CHEF_CHEF_BASE_UUID_H_

