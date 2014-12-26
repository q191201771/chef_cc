#include "chef_deque.h"
#include <assert.h>
#include <stdio.h>

int arr[] = {1, 2, 3, 4, 5};

int main(int argc, char **argv)
{
    int *p = NULL;
    struct chef_deque *deque = NULL;
    printf(">test_chef_deque.\n");
    deque = chef_deque_malloc();
    assert(chef_deque_pop_front(deque) == -1);
    assert(chef_deque_front(deque, (void **)&p) == -1);
    assert(p == NULL);
    chef_deque_push_front(deque, (void *)&arr[0]);
    /// after push 1
    assert(chef_deque_front(deque, (void **)&p) == 0);
    assert(*p == 1);
    assert(chef_deque_back(deque, (void **)&p) == 0);
    assert(*p == 1);
    chef_deque_push_front(deque, (void *)&arr[1]);
    /// after push 2 1
    chef_deque_push_back(deque, (void *)&arr[2]);
    /// after push 2 1 3
    chef_deque_push_back(deque, (void *)&arr[3]);
    /// after push 2 1 3 4
    chef_deque_push_front(deque, (void *)&arr[4]);
    /// after push 5 2 1 3 4
    assert(chef_deque_pop_back(deque) == 0);
    /// after pop 5 2 1 3
    assert(chef_deque_pop_back(deque) == 0);
    /// after pop 5 2 1
    assert(chef_deque_pop_front(deque) == 0);
    /// after pop 2 1
    assert(chef_deque_back(deque, (void **)&p) == 0);
    assert(*p == 1);
    assert(chef_deque_front(deque, (void **)&p) == 0);
    assert(*p == 2);
    assert(chef_deque_size(deque) == 2);

    while(chef_deque_front(deque, (void **)&p) == 0) {
        assert(chef_deque_pop_front(deque) == 0);
    }
    assert(chef_deque_size(deque) == 0);
    chef_deque_push_front(deque, (void *)&arr[0]);
    chef_deque_free(deque);
    deque = NULL;
    printf("<test_chef_deque.\n");
    return 0;
}

