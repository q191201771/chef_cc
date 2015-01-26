#include "chef_config.h"
#include "chef_buffer.h"
#include <stdlib.h>
#include <assert.h>

namespace chef
{

config::config() : fp_(NULL) { }

config::~config()
{
    if (fp_) {
        fclose(fp_);
        fp_ = NULL;
    }
}

int config::load(std::string file_name)
{
#ifdef _WIN32
    fopen_s(&fp_, file_name.c_str(), "rb+");
#else
    fp_ = fopen(file_name.c_str(), "rb+");
#endif
    if (!fp_) {
        return -1;
    }
    file_name_ = file_name;
    data_.clear();

    fseek(fp_, 0L, SEEK_END);
    long total_len = ftell(fp_);
    rewind(fp_);
    chef::buffer buf(total_len);
    fread(buf.write_pos(), total_len, 1, fp_);
    buf.seek_write(total_len);
    fclose(fp_);
    fp_ = NULL;
    char *end_pos = NULL;
    bool is_crlf;
    std::string line;
    for (; ; ) {
        /// @notice: can't parse some line end with '\n',other line end with
        /// '\r\n' in one config file
        if ((end_pos = buf.find_crlf()) != NULL) {
            is_crlf = true;
        } else {
            if ((end_pos = buf.find_eol()) != NULL) {
                is_crlf = false;
            } else {
                break;
            }
        }
        line.assign(buf.read_pos(), end_pos - buf.read_pos());
        buf.erase(end_pos - buf.read_pos() + (is_crlf ? 2 : 1));
        if (line[0] == '#') {
            continue;
        }
        std::size_t pos = line.find('=');
        if (pos == std::string::npos) {
            continue;
        }

        data_[line.substr(0, pos)] = line.substr(pos+1, line.size() - 1);
    }
    //debug_data();
    return 0;
}

int config::get(std::string key, std::string &value)
{
    const auto &iter = data_.find(key);
    if (iter == data_.end()) {
        return -1;
    } else {
        value = iter->second;
        return 0;
    }
}

void config::debug_data()
{
    printf("chef:debug_data()<<<\n");
    for (const auto &iter : data_) {
        printf("key(%s):value(%s)\n", iter.first.c_str(), iter.second.c_str());
    }
    printf("chef:debug_data()>>>\n");
}

} /// namespace chef
