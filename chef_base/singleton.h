#ifndef _CHEF_CHEF_BASE_SINGLETON_H_
#define _CHEF_CHEF_BASE_SINGLETON_H_

#include <pthread.h>
#include <boost/noncopyable.hpp>

/**
 * @switch to boost::serialization::singleton
 *
 * i don't think we need an destory interface
 * useless
 */

namespace chef
{

template<typename T>
class singleton : public boost::noncopyable
{
public:
    static T& instance()
    {
        pthread_once(&ponce_, &singleton::init);
        return *value_;
    }

private:
    singleton();
    ~singleton();

    static void init()
    {
        value_ = new T();
    }

private:
    static pthread_once_t ponce_;
    static T *value_;
};

template<typename T>
pthread_once_t singleton<T>::ponce_ = PTHREAD_ONCE_INIT;

template<typename T>
T *singleton<T>::value_ = NULL;

} /// namespace chef

#endif /// _CHEF_CHEF_BASE_SINGLETON_H_

