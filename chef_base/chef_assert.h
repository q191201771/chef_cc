#ifndef _CHEF_CHEF_BASE_ASSERT_H_
#define _CHEF_CHEF_BASE_ASSERT_H_

// *define NDEBUG truns off assert
//  see more info,man assert
///////////////////////////////////////////////////////
//#define NDEBUG
//#include <assert.h>
//#define CHEF_ASSERT(cond) do {assert(cond);}while(0);
///////////////////////////////////////////////////////

#include "async_log.h"

#define CHEF_ASSERT(cond) \
    do { \
        if (!(cond)) { \
            CHEF_TRACE_DEBUG("CHEFASSERT,%s.", #cond); \
        } \
    } while(0);

#endif /// _CHEF_CHEF_BASE_ASSERT_H_

