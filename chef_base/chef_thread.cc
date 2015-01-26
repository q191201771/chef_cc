#include "chef_thread.h"
#include "chef_current_thd.h"
#include <pthread.h>
#include <assert.h>
#include <sys/prctl.h>
#include <unistd.h>
#include <stdio.h>
#include <boost/make_shared.hpp>

using namespace chef::internal;

namespace chef
{

thread::thread(const thread_func &tf, std::string name)
    : pt_(0)
    , started_(false)
    , joined_(false)
    , tf_(tf)
    , name_(name)
{
    tid_ = boost::make_shared<pid_t>(0);
}

thread::~thread()
{
    if (started_ && !joined_) {
        pthread_detach(pt_);
    }
}

void *thread_data::thd_fun(void *arg)
{
    thread_data *td = (thread_data *)arg;
    ::prctl(PR_SET_NAME, td->name_.c_str());

    boost::shared_ptr<pid_t> sp_pid = td->tid_.lock();
    if (sp_pid) {
        *sp_pid	= chef::current_thd::gettid();
        sp_pid.reset();
    }

    td->tf_();
    delete td;
    return NULL;
}

int thread::start()
{
    assert(!started_);
    started_ = true;

    int res;
    thread_data *fd = new thread_data(tf_, name_, tid_);
    if ((res = pthread_create(&pt_, NULL, thread_data::thd_fun, fd)) != 0) {
        started_ = false;
        return res;
    }

    return 0;
}

int thread::try_join()
{
    if (!started_ || joined_) {
        return -1;
    }
    return join();
}

int thread::join()
{
    assert(started_);
    assert(!joined_);

    joined_ = true;
    return pthread_join(pt_, NULL);
}

} /// namespace chef

