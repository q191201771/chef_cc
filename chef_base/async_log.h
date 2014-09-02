#ifndef _CHEF_BASE_ASYNC_LOG_H_
#define _CHEF_BASE_ASYNC_LOG_H_

#include "buffer.h"
#include "wait_event.h"
#include <stdio.h>
#include <stdint.h>
#include <string>
#include <boost/serialization/singleton.hpp>
#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>

/**
 * @ brief
 *  @ use this class singleton,make sure don't call CHEF_TRACE_XXX after dtor
 *  @ if turn on async mode
 *   @ when shutdown,some log may lost
 *   @ when coredump,some log may haven't flush to file,find them in core.
 *
 * @ usage:
 *  @ chef::async_log::get_mutable_instance().init();
 *  @ CHEF_TRACE_DEBUG("hello world");
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

    /// @ param
    ///  if async_mode=false,log will not only flush to file but also to screen
    int init(level l = async_log::debug, 
             bool async_mode = true);
    int trace(async_log::level l, 
              const char *src_file_name, 
              int line, 
              const char *func_name, 
              const char *format, ...);

    /// not support dynamic change log level yet.
    //static void set_level(level l) {level_ = l;}
    static level get_level() {return level_;}
    async_log();
    ~async_log();

private:
    void log_thd_fun();

private:
    static level level_;
    const std::string end_screen_color_;
    std::string file_name_;
    boost::mutex mutex_;
    boost::scoped_ptr<buffer> front_buf_;
    boost::scoped_ptr<buffer> back_buf_;
    boost::scoped_ptr<boost::thread> log_thread_;
    bool async_mode_;
    bool screen_;
    wait_event log_thread_run_up_;
    bool run_;
    std::string level_name_[num_of_level];
    std::string screen_color_[num_of_level];
    FILE *fp_;
};

} /// namespace chef

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
#endif /// _CHEF_BASE_ASYNC_LOG_H_

