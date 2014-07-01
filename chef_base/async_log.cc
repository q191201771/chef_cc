#include "async_log.h"
#include "assert_.h"
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdarg.h>
#include <string>
#include <boost/date_time.hpp>

static pid_t get_tid()
{
    static __thread pid_t tid = 0;
    if (tid == 0) {
        tid = syscall(__NR_gettid);
    }

    return tid;
}

namespace chef
{

async_log::level async_log::level_ = async_log::num_of_level;

async_log::async_log() : fp_(NULL)
{
    level_name_[async_log::debug] = "DEBUG";
    level_name_[async_log::info]  = "INFO";
    level_name_[async_log::warn]  = "WARN";
    level_name_[async_log::error] = "ERROR";
    level_name_[async_log::fatal] = "FATAL";

    memset(file_name_, 0, sizeof(file_name_));

    extra_buf_len_ = 16384;
    extra_buf_ = new char[extra_buf_len_];
    async_mode_ = false;
}

async_log::~async_log()
{
    //CHEF_ASSERT(0);

    {//lock
    boost::lock_guard<boost::mutex> guard(mutex_);
    if (fp_) {
        fclose(fp_);
        fp_ = NULL;
    }
    }//unlock
    if (async_mode_) {
        log_thread_->join();
    }

    delete []extra_buf_;
}

int async_log::init(level l, bool async_mode, bool screen)
{
    boost::lock_guard<boost::mutex> guard(mutex_);
    if (fp_) {
        return -1;
    }

    level_ = l;
    async_mode_ = async_mode;
    screen_ = screen;

    //20140411T115959.ubuntu.pid.log.chef
    size_t pc_name_len = 128;
    char pc_name[128] = {0};
    gethostname(pc_name, pc_name_len);
    boost::posix_time::ptime time_str = boost::posix_time::second_clock::local_time();
    snprintf(file_name_, sizeof(file_name_) - 1, "%s.%s.%lu.log.chef",
             boost::posix_time::to_iso_string(time_str).c_str(), 
             pc_name, 
             (uint64_t)getpid());

    fp_ = fopen(file_name_, "ab+");
    if (!fp_) {
        return -1;
    }

    if (async_mode) {
        //log_thread_.start();
        log_thread_.reset(new boost::thread());
        log_thread_run_up_.wait();
    }

    return 0;
}

int async_log::trace(async_log::level l,
                     const char *src_file_name,
                     int line,
                     const char *func_name,
                     const char *format,...)
{
    boost::lock_guard<boost::mutex> guard(mutex_);

    if (!fp_ || !src_file_name || !func_name) {
        return -1;
    }

    int len = -1;

    // *now time
    boost::posix_time::ptime pt = boost::posix_time::microsec_clock::local_time();
    std::string time_str = boost::posix_time::to_iso_extended_string(pt);
    front_buf_.append(time_str.c_str(), time_str.length());

    // *tid
    snprintf(extra_buf_, 9, " %6d ", (int)get_tid());
    front_buf_.append(extra_buf_, strlen(extra_buf_));

    // *level name
    front_buf_.reserve(7);
    len = snprintf(front_buf_.write_pos(), 7, "%5s ", level_name_[l].c_str());
    front_buf_.seek_write(len);

    // *main
    va_list ap;
    va_start(ap, format);
    len = vsnprintf(extra_buf_, extra_buf_len_, format, ap);
    if (len > extra_buf_len_) {
        //lost
        len = extra_buf_len_;
    }
    va_end(ap);
    front_buf_.append(extra_buf_, len);

    // *src file & line
    //  erase path
    if (l == async_log::debug) {
        std::string without_path_name(src_file_name);
        std::size_t split_pos = without_path_name.rfind('/');
        if (split_pos != std::string::npos) {
            without_path_name = without_path_name.substr(split_pos + 1, 
                                    without_path_name.size() - 1);
        }
        len = snprintf(extra_buf_, extra_buf_len_, " - %s:%d", 
                       without_path_name.c_str(), line);
        front_buf_.append(extra_buf_, len);
    }

    // *line end
    front_buf_.reserve(1);
    *front_buf_.write_pos() = '\n';
    front_buf_.seek_write(1);

    if (screen_) {
        //'\0' may cut,it's acceptable
        printf("%s", front_buf_.read_pos());
    }
    if (!async_mode_) {
        fwrite((const void *)front_buf_.read_pos(),
                front_buf_.readable(),
                1,
                fp_);
        fflush(fp_);
        front_buf_.reset();
    }

    return 0;
}

void async_log::log_thd_fun()
{
    log_thread_run_up_.notify();

    { //lock 
    boost::lock_guard<boost::mutex> guard(mutex_);
    if (!fp_) {
        CHEF_ASSERT(0);
        return;
    }
    fprintf(fp_, "async log tid=%d.\n", get_tid()); 
    fflush(fp_);
    } //unlock
    for (; ; ) {
        bool write = false;
        { //lock
        boost::lock_guard<boost::mutex> guard(mutex_);
        if (!fp_) {
            //CHEF_ASSERT(0);
            break;
        }
        
        if (front_buf_.readable() > 0) {
            back_buf_.append(front_buf_.read_pos(), front_buf_.readable());
            front_buf_.reset();
            write = true;
        }
        } //unlock

        if (write) {
            fwrite((const void *)back_buf_.read_pos(), 
                    back_buf_.readable(), 
                    1, 
                    fp_);
            fflush(fp_);
            back_buf_.reset();
        }
        sleep(1);
    }
}

}

