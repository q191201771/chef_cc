#ifndef _CHEF_BASE_ASSERT_H_
#define _CHEF_BASE_ASSERT_H_

// *define NDEBUG truns off assert
//  see more info,man assert
///////////////////////////////////////////////////////
//#define NDEBUG
//#include <assert.h>
//#define CHEF_ASSERT(cond) do {assert(cond);}while(0);
///////////////////////////////////////////////////////


/**
 * @brief:
 *   @CHEF_ASSERT_LEVEL: 1 <assert.h>
 *                      2 do nothing
 *                      3 CHEF_TRACE_DEBUG
 *   
 *   you can modify CHEF_ASSERT_LEVEL in this file or define your CHEF_ASSERT_LEVEL 
 *   after include assert_.h 
 */
#include "async_log.h"

#define CHEF_ASSERT_LEVEL 3

#define CHEF_ASSERT(cond) \
    do { \
        if (!(cond)) { \
            if (CHEF_ASSERT_LEVEL == 1) { \
                assert(cond); \
            } else if (CHEF_ASSERT_LEVEL == 2) { \
                \
            } else if (CHEF_ASSERT_LEVEL == 3) { \
                CHEF_TRACE_DEBUG("assert!!!"); \
            } \
        } \
    } while(0);

// *1.assert
//#include <assert.h>
//#define CHEF_ASSERT(cond) assert(cond);
// *2.nothing
//#define CHEF_ASSERT(cond)
// *3.log while false
//#include "async_log.h"
//#define CHEF_ASSERT(cond) do {if (!(cond)) {CHEF_TRACE_DEBUG("assert!!!");}}while(0);

#endif

