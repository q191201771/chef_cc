#ifndef _CHEF_BASE_CONFIG_H_
#define _CHEF_BASE_CONFIG_H_

#include <stdio.h>
#include <string>
#include <map>

/**
 * @ cfg.right
 *  #this is an brief line
 *  name=chef
 *  num=100
 * @ cfg.wrong
 *  name =chef
 *  name= chef
 *  name=chef #wrong brief,must start with an line
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

} /// chef
#endif

