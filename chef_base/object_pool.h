#ifndef _CHEF_CHEF_BASE_OBJECT_POOL_H_
#define _CHEF_CHEF_BASE_OBJECT_POOL_H_

#include <stdint.h>
#include <list>
#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>

namespace chef
{

template<class object_type>
class object_pool : public boost::noncopyable
{
public:
    /**
     * @ function: create
     * @ return: NULL if fail
     */
    static object_pool *create(uint32_t init_num, bool with_lock = true);
    static void destory(object_pool *pool);

    /**
     * @ function: pop
     * @ return: NULL if fail
     * @ brief:
     *  if pool is empty,will produce [init_num_] of element again
     */
    object_type *pop();

    /**
     * @ function: push
     * @ brief:
     *  if pool size > [init_num_] * 2,won't push [element] back into pool(will
     *  delete [element] directly).
     */
    void push(object_type *element);

#ifdef CHEF_UNIT_TEST
    uint32_t get_outstanding() const { return outstanding_; }
#endif

private:
    object_pool(uint32_t init_num, bool with_lock);
    ~object_pool();
    void produce_();

    uint32_t init_num_;
    bool with_lock_;
    uint32_t outstanding_; ///pop but not push back,only for debug view
    std::list<object_type *> elements_;
    boost::mutex mutex_;
};

template<class object_type>
object_pool<object_type>::object_pool(uint32_t init_num, bool with_lock)
    : init_num_(init_num)
    , with_lock_(with_lock)
    , outstanding_(0)
{
    boost::unique_lock<boost::mutex> ul(mutex_, boost::defer_lock);
    if (with_lock_) {
        ul.lock();
    }
    produce_();
}

template<class object_type>
object_pool<object_type>::~object_pool()
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

template<class object_type>
object_pool<object_type> *object_pool<object_type>::create(uint32_t init_num, 
        bool with_lock)
{
    object_pool<object_type> *pool = NULL;
    try {
        pool = new object_pool(init_num, with_lock);
    } catch (...) {
        return NULL;
    }
    return pool;
}

template<class object_type>
void object_pool<object_type>::destory(object_pool *pool)
{
    if (pool) {
        delete pool;
    }
}

template<class object_type>
object_type *object_pool<object_type>::pop()
{
    object_type *element = NULL;
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
    ++outstanding_;
    return element;
}

template<class object_type>
void object_pool<object_type>::push(object_type *element)
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
    --outstanding_;
}

template<class object_type>
void object_pool<object_type>::produce_()
{
    for (uint32_t i = 0; i < init_num_; ++i) {
        object_type *element = new object_type();
        elements_.push_back(element);
    } 
}

} /// namespace chef

#endif /// _CHEF_CHEF_BASE_OBJECT_POOL_H_

