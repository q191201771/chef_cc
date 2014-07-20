#ifndef _CHEF_BASE_THREAD_H_
#define _CHEF_BASE_THREAD_H_

#include <string>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/noncopyable.hpp>

/**
 * @switch to boost::thread
 */

namespace chef
{

class thread : public boost::noncopyable
{
public:
    typedef boost::function<void()> thread_func;

    explicit thread(const thread_func &tf, std::string name=std::string("chef thread"));
    ~thread();

    int start();
    int join();
    int try_join();
    pid_t get_tid() const {return *tid_;}//may 0 if thread not run up

private:
    pthread_t pt_;
    bool started_;
    bool joined_;
    thread_func tf_;
    std::string name_;
    boost::shared_ptr<pid_t> tid_;
};

class current_thread
{
public:
    static pid_t get_tid();
};

namespace internal
{

struct thread_data
{
public:
    thread::thread_func tf_;
    std::string name_;
    boost::weak_ptr<pid_t> tid_;

    thread_data(const thread::thread_func tf,
                const std::string &name,
                const boost::shared_ptr<pid_t> &tid) :
        tf_(tf),
        name_(name),
        tid_(tid)
    {}

    static void *thd_fun(void *arg);
};

} /// namespace internal

} /// namespace chef
#endif

