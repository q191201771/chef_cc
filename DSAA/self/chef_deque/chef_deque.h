#ifndef _CHEF_CHEF_DEQUE_H_
#define _CHEF_CHEF_DEQUE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/**
 * @brief: 双向链表实现的deque
 *
 * @ no node
 *  head->NULL
 *  tail->NULL
 *
 * @ single node A
 *  head->A
 *  tail->A
 *  A' prev->NULL
 *  A' next->NULL
 *
 * @ nodes
 *        prev   next    
 *  NULL <---- A ---->    
 *               <----  B ---->NULL
 *                prev    next
 *
 *  head->A
 *  tail->B
 */

struct chef_deque_node {
    struct chef_deque_node *next_;
    struct chef_deque_node *prev_;
    void *data_;
};

struct chef_deque {
    struct chef_deque_node *head_;
    struct chef_deque_node *tail_;
    uint32_t size_;
};

struct chef_deque *chef_deque_malloc();
void chef_deque_free(struct chef_deque *deque);

void chef_deque_push_front(struct chef_deque *deque, void *data);
/**
 * @function: chef_deque_pop_front
 * @return: fail -1, if no node exist in deque;
 *          succ 0.
 */
int chef_deque_pop_front(struct chef_deque *deque);
/**
 * @function: chef_deque_front
 * @return: fail -1, if no node exist in deque;
 *          succ 0.
 * @brief: just fetch,not pop
 */
int chef_deque_front(struct chef_deque *deque, void **data);

void chef_deque_push_back(struct chef_deque *deque, void *data);
/**
 * @function: chef_deque_pop_back
 * @brief: see chef_deque_push_back
 */
int chef_deque_pop_back(struct chef_deque *deque);
/**
 * @function: chef_deque_back
 * @brief: see chef_deque_front
 */
int chef_deque_back(struct chef_deque *deque, void **data);

uint32_t chef_deque_size(struct chef_deque *deque);

#ifdef __cplusplus
}
#endif

#endif /// _CHEF_CHEF_DEQUE_H_

