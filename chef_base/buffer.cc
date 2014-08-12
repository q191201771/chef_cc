#include "buffer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

namespace chef
{

buffer::buffer(uint64_t init_capacity, uint64_t shrink_capacity)
    : init_capacity_(init_capacity)
    , shrink_capacity_(shrink_capacity)
    , capacity_(init_capacity)
    , read_index_(0)
    , write_index_(0)	
{
    data_ = (char *)calloc(1, init_capacity);
}

buffer::~buffer()
{
    free(data_);
}

buffer::buffer(const buffer &b)
    : init_capacity_(b.init_capacity_)
    , shrink_capacity_(b.shrink_capacity_)
    , capacity_(b.capacity_)
    , read_index_(0)
    , write_index_(0)
{
    data_ = (char *)calloc(1, init_capacity_);
    append(b.read_pos(), b.readable());
}

buffer &buffer::operator=(const chef::buffer &b)
{
    if (this != &b) {
        this->reset();
        this->append(b.read_pos(), b.readable());
    }
    return *this;
}

void buffer::reserve(uint64_t len)
{
    if (capacity_ - write_index_ >= len) {
        return;
    } else if (capacity_ - write_index_ + read_index_ >= len) {
        memmove(data_, data_ + read_index_, write_index_ - read_index_);
    } else {
        uint64_t need_len = write_index_ - read_index_ + len;
        for (; capacity_ < need_len; capacity_ <<= 1);
        char *new_buf = (char *)malloc(capacity_);
        memcpy(new_buf, data_ + read_index_, write_index_ - read_index_);
        free(data_);
        data_ = new_buf;
    }
    write_index_ -= read_index_;
    read_index_ = 0;
}

void buffer::append(const char *buf, uint64_t len)
{
    reserve(len);
    memcpy(data_ + write_index_, buf, len);
    write_index_ += len;
}

void buffer::erase(uint64_t len)
{
    assert(len <= readable());

    read_index_ += len;
    if (write_index_ - read_index_ < init_capacity_ && 
            capacity_ > shrink_capacity_) {
        char *new_data = (char *)malloc(init_capacity_);
        memcpy(new_data, data_ + read_index_, write_index_ - read_index_);
        write_index_ -= read_index_;
        read_index_ = 0;
        free(data_);
        data_ = new_data;
        capacity_ = init_capacity_;
    }	
}

void buffer::reset()
{
    read_index_ = write_index_ = 0;
    if (capacity_ > shrink_capacity_) {
        capacity_ = init_capacity_;
        free(data_);
        data_ = (char *)malloc(capacity_);
    }
}

void buffer::seek_write(uint64_t len) 
{
    assert(capacity_ - write_index_ >= len);
    write_index_ += len;
}

} /// namespace chef

