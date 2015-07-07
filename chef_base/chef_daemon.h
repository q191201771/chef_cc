#ifndef _CHEF_CHEF_BASE_DAEMON_H_
#define _CHEF_CHEF_BASE_DAEMON_H_

/**
 * this file has been dumped.
 */

namespace chef
{
    /**
     * @ return
     *  -1 if failed,otherwise pid
     */
    int daemon_init(const char *pidfile);

    /**
     * @ brief
     *  @ call this func before program exit
     *  @ it call ::unlink() inside
     */
    int daemon_exit(const char *pidfile);
} /// namespace chef

#endif /// _CHEF_CHEF_BASE_DAEMON_H_

