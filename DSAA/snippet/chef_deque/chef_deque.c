#include "chef_deque.h"
#include <stdlib.h>

struct chef_deque *chef_deque_malloc()
{
    struct chef_deque *deque = (struct chef_deque *)malloc(sizeof(*deque));
    deque->head_ = NULL;
    deque->tail_ = NULL;
    deque->size_ = 0;
    return deque;
}

void chef_deque_free(struct chef_deque *deque)
{
    struct chef_deque_node *node = deque->head_;
    while(node) {
        struct chef_deque_node *bak = node->next_;
        free(node);
        node = bak;
    }
    free(deque);
}

void chef_deque_push_front(struct chef_deque *deque, void *data)
{
    struct chef_deque_node *node = (struct chef_deque_node *)malloc(sizeof(*node));
    node->data_ = data;
    node->prev_ = NULL;
    node->next_ = deque->head_;
    if (deque->head_) {
        deque->head_->prev_ = node;
    } else {
        deque->tail_ = node;
    }
    deque->head_ = node;
    ++deque->size_;
}

int chef_deque_pop_front(struct chef_deque *deque)
{
    if (deque->head_ == NULL) {
        return -1;
    }
    
    struct chef_deque_node *node = deque->head_;
    deque->head_ = deque->head_->next_;
    if (deque->head_) {
        deque->head_->prev_ = NULL;
    } else {
        deque->tail_ = NULL;
    }
    free(node);
    --deque->size_;
    return 0;
}

int chef_deque_front(struct chef_deque *deque, void **data)
{
    if (deque->head_ == NULL) {
        return -1;
    }
    *data = deque->head_->data_;
    return 0;
}

void chef_deque_push_back(struct chef_deque *deque, void *data)
{
    struct chef_deque_node *node = (struct chef_deque_node *)malloc(sizeof(*node));
    node->data_ = data;
    node->prev_ = deque->tail_;
    node->next_ = NULL;
    if (deque->tail_) {
        deque->tail_->next_ = node;
    } else {
        deque->head_ = node;
    }
    deque->tail_ = node;
    ++deque->size_;
}

int chef_deque_pop_back(struct chef_deque *deque)
{
    if (deque->tail_ == NULL) {
        return -1;
    }
    struct chef_deque_node *node = deque->tail_;
    deque->tail_ = deque->tail_->prev_;
    if (deque->tail_) {
        deque->tail_->next_ = NULL;
    } else {
        deque->head_ = NULL;
    }
    free(node);
    --deque->size_;
    return 0;
}

int chef_deque_back(struct chef_deque *deque, void **data)
{
    if (deque->tail_ == NULL) {
        return -1;
    }
    *data = deque->tail_->data_;
    return 0;
}

uint32_t chef_deque_size(struct chef_deque *deque)
{
    return deque->size_;
}

