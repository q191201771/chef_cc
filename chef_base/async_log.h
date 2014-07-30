#ifndef CHEF_BASE_LOG_H_
#define CHEF_BASE_LOG_H_

#include "buffer.h"
#include "wait_event.h"
#include <stdio.h>
#include <stdint.h>
#include <string>

#include <boost/thread.hpp>
#include <boost/serialization/singleton.hpp>
#include <boost/smart_ptr.hpp>

/**
 * @use this class singleton,so won't call dtor i assume
 *
 * if async mode,
 *   @when shutdown,some log may lost
 *   @when coredump,some log may haven't flush to file,
 *    find them in core.
 * 
 * TODO
 *   handle fwrite failed
 *
 * usage:
 *   chef::async_log::get_mutable_instance().init();
 *   CHEF_TRACE_DEBUG("hello world");
 */

namespace chef
{

class async_log : public boost::serialization::singleton<async_log>
{
public:
    enum level
    {
        debug=0,
        info,
        warn,
        error,
        fatal,
        num_of_level,
    };

    int init(level l = async_log::debug, 
             bool async_mode = true, 
             bool screen = false);
    int trace(async_log::level l, 
              const char *src_file_name, 
              int line, 
              const char *func_name, 
              const char *format, ...);

    static void set_level(level l) {level_ = l;}
    static level get_level() {return level_;}
    async_log();
    ~async_log();

private:
    void log_thd_fun();

private:
    static level level_;
    FILE *fp_;
    char file_name_[512];
    boost::mutex mutex_;
    std::string level_name_[num_of_level];

    int32_t extra_buf_len_;
    char *extra_buf_;
    buffer front_buf_;
    buffer back_buf_;
    boost::scoped_ptr<boost::thread> log_thread_;
    bool async_mode_;
    bool screen_;
    wait_event log_thread_run_up_;
};

};

#define CHEF_TRACE_DEBUG(...) do {if (chef::async_log::get_level() <= chef::async_log::debug) \
    chef::async_log::get_mutable_instance().trace(chef::async_log::debug, __FILE__, __LINE__, __func__, __VA_ARGS__);}while(0)
#define CHEF_TRACE_INFO(...) do {if (chef::async_log::get_level() <= chef::async_log::info) \
    chef::async_log::get_mutable_instance().trace(chef::async_log::info, __FILE__, __LINE__, __func__, __VA_ARGS__);}while(0)
#define CHEF_TRACE_WARN(...) do {if (chef::async_log::get_level() <= chef::async_log::warn) \
    chef::async_log::get_mutable_instance().trace(chef::async_log::warn, __FILE__, __LINE__, __func__, __VA_ARGS__);}while(0)
#define CHEF_TRACE_ERROR(...) do {if (chef::async_log::get_level() <= chef::async_log::error) \
    chef::async_log::get_mutable_instance().trace(chef::async_log::error, __FILE__, __LINE__, __func__, __VA_ARGS__);}while(0)
#define CHEF_TRACE_FATAL(...) do {if (chef::async_log::get_level() <= chef::async_log::fatal) \
    chef::async_log::get_mutable_instance().trace(chef::async_log::fatal, __FILE__, __LINE__, __func__, __VA_ARGS__);}while(0)
#endif

