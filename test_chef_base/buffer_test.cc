#define CHEF_UNIT_TEST
#include "buffer.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

using chef::buffer;

#define TEST_STAGE_NUMBER 8

int main()
{
    printf(">buffer_test.\n");

    buffer buf1;
    assert(buf1.init_capacity() == 16384);
    assert(buf1.shrink_capacity() == 1048576);
    assert(buf1.capacity() == 16384);
    assert(buf1.read_index() == 0);
    assert(buf1.write_index() == 0);
    char *data = buf1.data();
    assert(data);
    assert(buf1.read_pos() == data);
    assert(buf1.readable() == 0);
    assert(buf1.write_pos() == data);
    //printf("[1/%d] done.\n", TEST_STAGE_NUMBER);

    buffer buf2(8, 32);
    char *p1 = buf2.read_pos();
    buf2.append("hello world", 5);
    assert(buf2.readable() == 5);
    assert(buf2.capacity() == 8);
    assert(memcmp(buf2.read_pos(), "hello", 5) == 0);
    
    char origin_buf[128] = {0};
    memset(origin_buf, 'x', 127);
    buf2.append(origin_buf, 30);
    char *p2 = buf2.read_pos();
    assert(buf2.readable() == 35);
    assert(buf2.capacity() == 64);
    assert(memcmp(buf2.read_pos(), "helloxxx", 8) == 0);
    assert(p1 != p2);

    buf2.erase(32);
    assert(buf2.capacity() == 8);
    char *p3 = buf2.read_pos();
    assert(p3 != p2);
    assert(memcmp(buf2.read_pos(), "xxx", 3) == 0);

    buf2.reserve(10);
    strcpy(buf2.write_pos(), "helloworld");
    buf2.seek_write(10);
    char *p4 = buf2.read_pos();
    assert(p4 != p3);
    assert(buf2.capacity() == 16);
    assert(memcmp(buf2.read_pos(), "xxxhelloworld", 13) == 0);

    buffer buf3(8, 32);
    buf3.append("helloworld", 8);
    assert(buf3.capacity() == 8);

    buffer buf4(8, 32);
    buf4.reserve(16);
    assert(buf4.capacity() == 16);
    memcpy(buf4.write_pos(), "1234567890123456", 16);
    buf4.seek_write(16);

    buffer buf5(buf2);
    assert(buf5.capacity() == 16);
    assert(memcmp(buf5.read_pos(), "xxxhelloworld", 13) == 0);

    buffer buf6 = buf5;
    assert(buf6.read_pos() == buf6.data());
    assert(memcmp(buf6.read_pos(), "xxxhelloworld", 13) == 0);
    buf6 = buf6;
    assert(memcmp(buf6.read_pos(), "xxxhelloworld", 13) == 0);
    
    buffer buf7;
    buf7.append("123456789", 10);
    assert(buf7.find("3", 1) == buf7.read_pos() + 2);
    assert(buf7.find("a", 1) == NULL);
    assert(buf7.find("345", 3) == buf7.read_pos() + 2);
    assert(buf7.find("345", 4) == NULL);
    assert(buf7.find("890", 3) == NULL);
    assert(buf7.find("134", 3) == NULL);
    assert(buf7.find_eol() == NULL);
    assert(buf7.find_crlf() == NULL);
    assert(buf7.find('9') == buf7.read_pos() + 8);
    assert(buf7.find('a') == NULL);
    assert(buf7.find("1234567890123", 14) == NULL);
    buf7.erase(buf7.readable());
    assert(buf7.readable() == 0);
    buf7.append("\0abc\r\n123\r\n4", 12);
    assert(buf7.find("bc\r", 3) == buf7.read_pos() + 2);
    assert(buf7.find('\r') == buf7.read_pos() + 4);
    assert(buf7.find_crlf() == buf7.read_pos() + 4);
    assert(buf7.find_eol() == buf7.read_pos() + 5);
    assert(buf7.find("33", 2) == NULL);

    printf("<buffer_test.\n");
    return 0;
}
