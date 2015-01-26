#include "chef_chunk_head.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

int main()
{
    printf(">chunk_head_test.\n");
    char buf[32] = "hello world";
    char raw[64];
    memcpy(raw + 24, buf, strlen(buf) + 1);
    chef::chunk_head ch;
    ch.id_ = 7;
    ch.type_ = 13;
    ch.reserved_ = 26;
    ch.body_len_ = strlen(buf) + 1;
    chef::encode_chunk_head(ch, raw);
    (void)ch;

    chef::chunk_head ch2;
    assert(chef::decode_chunk_head(raw, &ch2) == 0);
    assert(ch2.id_ == 7);
    assert(ch2.type_ == 13);
    assert(ch2.reserved_ == 26);
    assert(ch2.body_len_ == strlen(buf) + 1);
    assert(memcmp(raw + 24, buf, ch2.body_len_) == 0);
    printf("<chunk_head_test.\n");

    return 0;
}

