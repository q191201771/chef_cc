#include "chef_random.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

int main()
{
    printf(">random_test.\n");
    const int LOOP_TIMES = 10000;
    const int RANGE = 100;
    int count[RANGE] = {0};

    assert(chef::random::uniform_signed(0) == 0);
    assert(chef::random::uniform_unsigned(0) == 0);

    int32_t sum = 0;
    for (int i = 0; i < LOOP_TIMES; ++i) {
        int32_t num = chef::random::uniform_unsigned(RANGE);
        assert(num >= 0 && num < RANGE);
        ++count[num];
        sum += num;
    }
    printf("     -----");
    for (int i = 0; i < RANGE; ++i) {
        if (i % 10 == 0) {
            printf("\n     ");
        }
        printf("%d:%d ", i, count[i]);
    }
    printf("\n     -----\n");
    printf("     average=%f(supposed ~=%f)\n", (float)sum / LOOP_TIMES, 
            (float)(RANGE - 1) / 2);
    printf("<random_test.\n");
    return 0;
}

