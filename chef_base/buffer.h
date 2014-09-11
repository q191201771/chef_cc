#ifndef _CHEF_CHEF_BASE_BUFFER_H_
#define _CHEF_CHEF_BASE_BUFFER_H_

#include <stdint.h>

/**
 * @ brief
 *  @ chef::buffer is flexible, not fixed size, can self-grow & reduce
 *  @ chef::buffer is an flow buffer
 *  @ more into in buffer_test.cc
 */

namespace chef
{

class buffer
{
public:
    explicit buffer(uint64_t init_capacity = 16384, uint64_t shrink_capacity = 1048576);
    
    ///   buffer buf(data, len);
    ///  same as
    ///   buffer buf(len, 2 * len);
    ///   buf.append(data, len);
    buffer(const char *data, uint64_t len);
    ~buffer();

    /// deep copy
    buffer(const buffer &b);
    buffer &operator=(const buffer &b);

    /// +++++++++++++++++++++++++++++++++++++++++++++++++++++
    /// example
    /// buf.reserve(6);
    /// strcpy(buf.write_pos(), "hello");
    /// buf.seek_write(6);
    void reserve(uint64_t len);
    char *write_pos() const { return data_ + write_index_; }
    void seek_write(uint64_t len);
    /// or just 
    /// buf.append("hello", 6);
    void append(const char *buf, uint64_t len);

    /// -----------------------------------------------------
    /// pull out
    char *read_pos() const { return data_ + read_index_; }
    uint64_t readable() const { return write_index_ - read_index_; }
    void erase(uint64_t len);

    /// @ return 
    ///  @ position if found 
    ///  @ NULL if not found
    char *find(const char *key, int len);
    char *find(char c);
    char *find_crlf() { return find("\r\n", 2); }
    char *find_eol() { return find('\n'); }

    /// @ brief
    ///  erase space 
    /// @ return
    ///  this->read_pos();
    char *trim_left();
    char *trim_right();

    void reset(); 

    uint64_t capacity() const { return capacity_; }

#ifdef CHEF_UNIT_TEST
    uint64_t init_capacity() const { return init_capacity_; }
    uint64_t shrink_capacity() const { return shrink_capacity_; }
    uint64_t read_index() const { return read_index_; }
    uint64_t write_index() const { return write_index_; }
    char *data() const { return data_; }
#endif /// CHEF_UNIT_TEST

private:
    const uint64_t init_capacity_;
    const uint64_t shrink_capacity_;
    uint64_t capacity_;
    uint64_t read_index_;
    uint64_t write_index_;
    char *data_;
};

} /// namespace chef

#endif /// _CHEF_CHEF_BASE_BUFFER_H_

