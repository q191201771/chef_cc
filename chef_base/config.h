#ifndef _CHEF_BASE_CONFIG_H_
#define _CHEF_BASE_CONFIG_H_

#include <stdio.h>
#include <string>
#include <map>

//1. comment should begin with #
//2. every line is a key,value pair
//   they combin like this:
//   key=value
//   and can't with space, like key = value

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

#endif

