#ifndef _CHEF_CHEF_BASE_CONFIG_H_
#define _CHEF_CHEF_BASE_CONFIG_H_

#include <stdio.h>
#include <string>
#include <map>

/**
 * @ support win-platform alse
 *
 * @ brief
 *  @ this class is not thread-safe
 *  @ more info in config_test.cc
 */

namespace chef
{

class config
{
public:
    config();
    ~config();

    int load(std::string file_name);
    int get(std::string key, std::string &value);

private:
    void debug_data();

    FILE *fp_;
    std::string file_name_;
    std::map<std::string, std::string> data_;
};

} /// namespace chef
#endif /// _CHEF_CHEF_BASE_CONFIG_H_

