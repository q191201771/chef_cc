#include "config.h"
#include <stdlib.h>

namespace chef
{

config::config() : fp_(NULL) { }

config::~config()
{
    if (fp_) {
        fclose(fp_);
    }
}

int config::load(std::string file_name)
{
    fp_ = fopen(file_name.c_str(), "rb+");
    if (!fp_) {
        return -1;
    }

    file_name_ = file_name;
    data_.clear();

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, fp_)) != -1) {
        //comment format
        if (line[0] == '#') {
            continue;
        }

        //format wrong
        std::string line_str(line, read - 1);
        std::size_t pos = line_str.find('=');
        if (pos == std::string::npos) {
            continue;
        }

        data_[line_str.substr(0, pos)] = line_str.substr(pos+1, 
                line_str.size() - 1);
    }
    free(line);
    //debug_data();

    fclose(fp_);
    fp_ = NULL;
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
        printf("%s:%s\n", iter.first.c_str(), iter.second.c_str());
    }
    printf("chef:debug_data()>>>\n");
}

}
