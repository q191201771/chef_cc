#ifndef _CHEF_CHEF_BASE_NONCOPYABLE_H_
#define _CHEF_CHEF_BASE_NONCOPYABLE_H_

/**
 * @switch to boost::noncopyable
 */

namespace chef
{

class noncopyable
{
protected:
    noncopyable() {}
    ~noncopyable() {}

private:
    noncopyable(const noncopyable &);
    const noncopyable &operator=(const noncopyable &);
};

/// empty is fine
class copyable
{

};

} /// namespace chef

#endif /// _CHEF_CHEF_BASE_NONCOPYABLE_H_

