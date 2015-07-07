#include "chef_md5.h"
#include "md5.h"

static char nybble_to_xdigit(int num) {
    if (num < 10) {
        return '0' + num;
    } else {
        return 'A' + num - 10;
    }
}

static std::string byte_to_hex(uint8_t byte) {
    std::string rv;
    rv += nybble_to_xdigit(byte >> 4);
    rv += nybble_to_xdigit(byte & 0x0f);
    return rv;
}

namespace chef {
namespace md5 {

std::string marshal(const std::string &src) {
    unsigned char fp[16] = {0};
    std::string sign;
    md5_state_t ms;
    md5_init(&ms);
    md5_append(&ms, (const md5_byte_t *)src.c_str(), src.size());
    md5_finish(&ms, fp);
    for (int i = 0; i < 16; i++) {
        sign += byte_to_hex(fp[i]);
    }
    /// lower them
    for (uint32_t i = 0; i < sign.size(); i++) {
        if (sign[i] >= 'A' && sign[i] <= 'Z') {
            sign[i] += 32;
        }
    }
    return sign;
}

} /// namespace md5
} /// namespace chef
