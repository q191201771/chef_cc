#ifndef _CHEF_BASE_CHUNK_H_
#define _CHEF_BASE_CHUNK_H_

#include <stdint.h>

/**
 * @ brief
 *  @ a simple TLV head
 *  @ mocked from https://github.com/owenliang/simple_kit/tree/master/simple_head
 */

namespace chef
{
    const int CHUNK_HEAD_LEN = 24;
    
    /**
     *
     * +--------+------+-----------+----------+----------+
     * |   id   | type | magic num | reserved | body len |
     * 0        8     12          16         20         23
     * ---------------------------------------------------
     *
     */ 
    struct chunk_head
    {
        uint64_t id_;
        uint32_t type_;
        /// uint32_t magic_num_; /// don't expose to user
        uint32_t reserved_;
        uint32_t body_len_;
    };

    /// raw_head malloc outside
    /// make sure raw_head have CHUNK_HEAD_LEN
    int encode_chunk_head(const chunk_head &ch, char *raw_head /*out*/ );
    int decode_chunk_head(const char *raw_head, chunk_head *ch /*out*/ );

} /// namespace chef

#endif ///  _CHEF_BASE_CHUNK_H_
