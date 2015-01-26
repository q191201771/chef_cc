#include "chef_daemon.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include "chef_async_log.h"

namespace chef
{

static int check_pid(const char *pidfile)
{
    FILE *fp = fopen(pidfile, "rb");
    if (!fp) {
        return 0;
    }
    int pid;
    int ret = fscanf(fp, "%d", &pid);
    fclose(fp);
    if (ret != 1 || pid <= 0 || pid == (int)getpid()) {
        return 0;
    }
    if (kill(pid, 0) == -1 && errno == ESRCH) {
        return 0;
    }
    return pid;
}

static int write_pid(const char *pidfile)
{
    /// @ notice
    ///  stderr rediects to /dev/null if ::daemon()'s 2rd param is 0
    ///  more info man 3 daemon

    int fd = open(pidfile, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        fprintf(stderr, "::open()==-1,pidfile=%s,errno=%d.\n", pidfile, errno);
        return -1;
    }
    /// fd is not dup'ed, more info man 3 fdopen
    FILE *fp = fdopen(fd, "r+");
    if (!fp) {
        fprintf(stderr, "::fdopen()==-1,pidfile=%s,errno=%d.\n", pidfile, errno);
        close(fd);
        return -1;
    }
    int ret, pid;
    while ((ret = flock(fd, LOCK_EX | LOCK_NB)) == -1) {
        if (errno == EINTR) {
            continue;
        } else if (errno == EWOULDBLOCK) {
            ret = fscanf(fp, "%d", &pid);
            if (ret == 1) {
                fprintf(stderr, "flock by others,pid=%d.\n", pid);
            } else {
                fprintf(stderr, "::flock()==-1,pidfile=%s,errno=%d.\n", pidfile, errno); 
            }
            goto error;
        } else {
            fprintf(stderr, "::flock()==-1,pidfile=%s,errno=%d.\n", pidfile, errno);
            goto error;
        }
    }
    pid = (int)getpid();
    if (!fprintf(fp, "%d", pid)) {
        fprintf(stderr, "::fprintf()==NULL,pidfile=%s.\n", pidfile);
        goto error;
    }
    fflush(fp);
    /// keep flock' non-blocking lock
    return pid;

error:
    if (fp) {
        fclose(fp);
    }
    return -1;
}

int daemon_init(const char *pidfile)
{
    int pid = check_pid(pidfile);
    if (pid) {
       fprintf(stderr, "FATAL: %s already running,pid=%d.\n", pidfile, pid);
       return -1;
    }
    if (daemon(1, 0) == -1) {
        fprintf(stderr, "::daemon()==-1,errno=%d.\n", errno);
        return -1;
    }
    pid = write_pid(pidfile);
    return pid;
}

int daemon_exit(const char *pidfile)
{
    return unlink(pidfile);
}

} /// namespace chef

