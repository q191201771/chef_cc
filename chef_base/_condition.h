#ifndef CHEF_BASE_CONDITION_H_
#define CHEF_BASE_CONDITION_H_

#include "_mutex.h"
#include "_noncopyable.h"
#include <pthread.h>

/**
 * @switch to boost::condition_variable
 */

namespace chef
{

class condition : public noncopyable
{
public:
    explicit condition(mutex &m) : 
        m_(m)
    {
        pthread_cond_init(&cond_, NULL);
    }
    ~condition()
    {
        pthread_cond_destroy(&cond_);
    }

    void wait()
    {
        pthread_cond_wait(&cond_, &(m_.get_pthread_mutex_t()));
    }	

    void notify()
    {
        pthread_cond_signal(&cond_);	
    }

private:
    pthread_cond_t cond_;
    mutex &m_;
};

} /// namespace chef
#endif

