#ifndef _CHEF_CHEF_BASE_CURRENT_PROC_H_
#define _CHEF_CHEF_BASE_CURRENT_PROC_H_

#include <stdint.h>
#include <string>

namespace chef
{
    namespace current_proc
    {
        /// call ::getpid inside
        int getpid();
        
        /// like '/usr/bin/iostat'
        std::string obtain_bin_path();
        
        /// like 'iostat'
        std::string obtain_bin_name();
        
        /// like '/usr/bin/'
        std::string obtain_bin_dir();
    
    } /// namespace current_proc
} /// namespace chef

#endif /// _CHEF_CHEF_BASE_CURRENT_PROC_H_

