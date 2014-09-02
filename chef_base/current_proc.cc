#include "current_proc.h"
#include <unistd.h>
#include <sys/types.h>

namespace chef
{
namespace current_proc
{

int getpid()
{
    return static_cast<int>(::getpid());
}

std::string obtain_bin_path()
{
    char buf[512] = {0};
    ssize_t length = readlink("/proc/self/exe", buf, sizeof buf);
    if (length == -1) {
        return std::string();
    } 
    return std::string(buf, length);
}

std::string obtain_bin_name()
{
    std::string path = obtain_bin_path();
    if (path == std::string()) {
        return path;
    }
    std::size_t pos = path.find_last_of('/'); 
    if (pos == std::string::npos) {
        return std::string();
    }
    return std::string(path, pos + 1);
}

std::string obtain_bin_dir()
{
    std::string path = obtain_bin_path();
    if (path == std::string()) {
        return path;
    }
    std::size_t pos = path.find_last_of('/');
    if (pos == std::string ::npos) {
        return std::string();
    }
    return std::string(path, 0, pos + 1);
}

} /// namespace current_proc
} /// namespace chef

