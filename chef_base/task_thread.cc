#include "task_thread.h"
#include <stdio.h>
#include <assert.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <boost/thread/lock_guard.hpp>

task_thread::task_thread(const std::string &name) :
    name_(name),
    run_(false),
    thread_(NULL)
{
    init_epoll();	
}

task_thread::~task_thread()
{
    //before dtor,some task have't done.
    //need?
    //do this for valgrind,but some deferred task may lost,though
    if (run_) {
        run_ = false;
        thread_->join();
    }

    if (epfd_ != -1) {
        ::close(epfd_);
        epfd_ = -1;
    }
    if (wakefd_[0] != -1) {
        ::close(wakefd_[0]);
        wakefd_[0] = -1;
    }
    if (wakefd_[1] != -1) {
        ::close(wakefd_[1]);
        wakefd_[1] = -1;
    }
}

int task_thread::init_epoll()
{
    wakefd_[0] = -1;
    wakefd_[1] = -1;

    epfd_ = epoll_create(16);
    //assert(epfd_ != -1);
    if (epfd_ == -1) {
        return -1;
    }

    init_wakeup();
    return 0;
}

int task_thread::init_wakeup()
{
    if (pipe(wakefd_) < 0) {
        return -1;
    }

    if (make_socket_nonblocking(wakefd_[0]) == -1 || 
        make_socket_nonblocking(wakefd_[1]) == -1) {
        close(wakefd_[0]);
        close(wakefd_[1]);
        return -1;
    }

    //1. add
    struct epoll_event event = {0};
    event.data.ptr = (void *)&wakefd_[0];
    if (epoll_ctl(epfd_, EPOLL_CTL_ADD, wakefd_[0], &event) == -1) {
        close(wakefd_[0]);
        close(wakefd_[1]);
        return -1;
    }

    //2. modr
    event.events = EPOLLIN;
    if (epoll_ctl(epfd_, EPOLL_CTL_MOD, wakefd_[0], &event) == -1) {
        close(wakefd_[0]);
        close(wakefd_[1]);
        return -1;
    }

    return 0;
}

int task_thread::make_socket_nonblocking(int fd)
{
    int flag = fcntl(fd, F_GETFL);
    if (flag == -1) {
        return -1;
    }

    if (fcntl(fd, F_SETFL, flag | O_NONBLOCK) == -1) {
        return -1;
    }

    return 0;
}

void task_thread::start()
{
    run_ = true;
    thread_.reset(new thread(boost::bind(&task_thread::run_in_thread, this), 
                name_));
    thread_->start();
    thread_run_up_.wait();
}

void task_thread::add(const task &t, uint32_t deferred_time_ms)
{
    {//lock
    boost::lock_guard<boost::mutex> guard(lock_); 
    if (deferred_time_ms == 0){
        tasks_.push_back(t);
    } else {
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        uint64_t expire = ts.tv_sec * 1000 + 
            ts.tv_nsec / 1000000 + 
            deferred_time_ms;
        deferred_tasks_.insert(std::pair<uint64_t, task>(expire, t));
    }
    }//unlock

    wakeup();
}

void task_thread::wakeup()
{
    while(write(wakefd_[1], "", 1) == -1 && errno == EINTR);
}

int task_thread::poll(int timeout)
{
    run_task();
    run_deferred_task();

    struct epoll_event events[32];
    int numfd = epoll_wait(epfd_, events, 32, timeout);
    if (numfd <= 0) {
        return 0;
    }

    //assert(numfd == 1);
    for (int i = 0; i < numfd; ++i) {
        int *fd = (int *)events[i].data.ptr;

        if (*fd == wakefd_[0] && events[i].events & EPOLLIN) {
            char buf[8];
            read(wakefd_[0], buf, 1);	
        }
    }

    return 0;
}

void task_thread::run_in_thread()
{
    thread_run_up_.notify();
    while(run_) {
        poll(100);
    }
    poll(0);
}

void task_thread::run_task()
{
    std::deque<task> tasks_copy;
    {//lock
    boost::lock_guard<boost::mutex> guard(lock_);
    tasks_copy.swap(tasks_);
    }//unlock
    while (!tasks_copy.empty()) {
        task t = tasks_copy.front();
        tasks_copy.pop_front();
        t();
    }
}

void task_thread::run_deferred_task()
{
    boost::lock_guard<boost::mutex> guard(lock_);
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    uint64_t now = ts.tv_sec * 1000 + ts.tv_nsec / 1000000;

    auto iter = deferred_tasks_.begin();
    for (; iter != deferred_tasks_.end(); ++iter) {
        if (iter->first > now) {
            break;
        }

        (iter->second)();
    }
    deferred_tasks_.erase(deferred_tasks_.begin(), iter);
}

