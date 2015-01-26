#include "chef_assert.h"

int main()
{
    printf(">assert_test.\n");
    bool var = true;
    CHEF_ASSERT(var);
    CHEF_ASSERT(!var);
    chef::async_log::get_mutable_instance().init(chef::async_log::debug, false);
    CHEF_ASSERT(var == false);
    CHEF_ASSERT(1 + 1 == 3);
    printf("<assert_test.\n");

    return 0;
}

