#ifndef _CHEF_CHEF_BASE_MEMORY_POOL_H_
#define _CHEF_CHEF_BASE_MEMORY_POOL_H_

#include <stdint.h>
#include <list>
#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>

/**
 * @ brief
 *  rename memory_pool to object_pool may better
 */

namespace chef
{

template<class memory_type>
class memory_pool : public boost::noncopyable
{
public:
    /**
     * @ function: create
     * @ return: NULL if fail
     */
    static memory_pool *create(uint32_t init_num, bool with_lock = true);
    static void destory(memory_pool *pool);

    /**
     * @ function: pop
     * @ return: NULL if fail
     * @ brief:
     *  if pool is empty,will produce [init_num_] of element again
     */
    memory_type *pop();

    /**
     * @ function: push
     * @ brief:
     *  if pool size > [init_num_] * 2,won't push [element] back into pool(will
     *  delete [element] directly).
     */
    void push(memory_type *element);

private:
    memory_pool(uint32_t init_num, bool with_lock);
    ~memory_pool();
    void produce_();

    uint32_t init_num_;
    bool with_lock_;
    std::list<memory_type *> elements_;
    boost::mutex mutex_;
};

template<class memory_type>
memory_pool<memory_type>::memory_pool(uint32_t init_num, bool with_lock)
    : init_num_(init_num)
    , with_lock_(with_lock)
{
    boost::unique_lock<boost::mutex> ul(mutex_, boost::defer_lock);
    if (with_lock_) {
        ul.lock();
    }
    produce_();
}

template<class memory_type>
memory_pool<memory_type>::~memory_pool()
{
    boost::unique_lock<boost::mutex> ul(mutex_, boost::defer_lock);
    if (with_lock_) {
        ul.lock();
    }
    while(!elements_.empty()) {
        delete elements_.front();
        elements_.pop_front();
    }
}

template<class memory_type>
memory_pool<memory_type> *memory_pool<memory_type>::create(uint32_t init_num, 
        bool with_lock)
{
    memory_pool<memory_type> *pool = NULL;
    try {
        pool = new memory_pool(init_num, with_lock);
    } catch (...) {
        return NULL;
    }
    return pool;
}

template<class memory_type>
void memory_pool<memory_type>::destory(memory_pool *pool)
{
    if (pool) {
        delete pool;
    }
}

template<class memory_type>
memory_type *memory_pool<memory_type>::pop()
{
    memory_type *element = NULL;
    boost::unique_lock<boost::mutex> ul(mutex_, boost::defer_lock);
    if (with_lock_) {
        ul.lock();
    }
    try {
        if (elements_.empty()) {
            produce_();
        }
        element = elements_.front();
        elements_.pop_front();
    } catch (...) {
        return NULL;
    }
    return element;
}

template<class memory_type>
void memory_pool<memory_type>::push(memory_type *element)
{
    if (!element) {
        return;
    }
    boost::unique_lock<boost::mutex> ul(mutex_, boost::defer_lock);
    if (with_lock_) {
        ul.lock();
    }
    if (elements_.size() > init_num_ * 2) {
        delete element;
    } else {
        elements_.push_back(element);
    }
}

template<class memory_type>
void memory_pool<memory_type>::produce_()
{
    for (uint32_t i = 0; i < init_num_; ++i) {
        memory_type *element = new memory_type();
        elements_.push_back(element);
    } 
}



} /// namespace chef

#endif /// _CHEF_CHEF_BASE_MEMORY_POOL_H_

