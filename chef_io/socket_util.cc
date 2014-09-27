#include "socket_util.h"

#ifdef _WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#else
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <string.h>
#endif

#ifdef _WIN32
void win_socket_init()
{
    WSADATA wsad;
    WSAStartup(0x0201, &wsad);
}
#endif

int set_socket_send_buf(int32_t fd, int size)
{
    if (size <= 0) {
        return -1;
    }
#ifdef _WIN32
    return setsockopt(fd, SOL_SOCKET, SO_SNDBUF, (const char *)&size, sizeof size);
#else
    return setsockopt(fd, SOL_SOCKET, SO_SNDBUF, (char *)&size, (socklen_t)sizeof(size));
#endif
    return 0;
}

int set_socket_recv_buf(int32_t fd, int size)
{
    if (size <= 0) {
        return -1;
    }
#ifdef _WIN32
    return setsockopt(fd, SOL_SOCKET, SO_RCVBUF, (const char *)&size, sizeof size);
#else
    return setsockopt(fd, SOL_SOCKET, SO_RCVBUF, (char *)&size, (socklen_t)sizeof(size));
#endif
    return 0;
}

int make_socket_nonblock(int32_t fd)
{
#ifdef _WIN32
    u_long flag = 1;
    return ioctlsocket(fd, FIONBIO, &flag);
#else
    //return fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
    int flag;
    if ((flag = fcntl(fd, F_GETFL)) < 0) {
        return -1;
    }
    if (!(flag & O_NONBLOCK)) {
        return fcntl(fd, F_SETFL, flag | O_NONBLOCK);
    }
#endif
    return 0;
}

int make_socket_reuseable(int32_t fd)
{
#ifdef _WIN32
    int on = 1;
    return setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const char *)&on, sizeof on);
#else
    int on = 1;
    return setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (void *)&on, (socklen_t)sizeof on);
#endif
    return 0;
}

int make_socket_keepalive(int32_t fd)
{
#ifdef _WIN32
    int on = 1;
    return setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (const char *)&on, sizeof on);
#else
    int on = 1;
    return setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (void *)&on, (socklen_t)sizeof on);
#endif
}

int make_socket_nodelay(int32_t fd)
{
#ifdef _WIN32
    int on = 1;
    return setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (const char *)&on, sizeof on);
#else
    int on = 1;
    return setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (void *)&on, (socklen_t) sizeof on);
#endif
}

int fetch_listen_socket(const char *ip, uint16_t port)
{
    int32_t fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        return -1;
    }

    /// set outside if user needed
    //make_socket_nonblock(fd);
    //make_socket_reuseable(fd);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);
    if (::bind(fd, (struct sockaddr *)&addr, sizeof addr) == -1) {
        goto error_handle;
    }

    if (::listen(fd, 1024) == -1) {
        goto error_handle;
    }

    return fd;
error_handle:
#ifdef _WIN32
    ::closesocket(fd);
#else
    ::close(fd);
#endif
    return -1;
}

int fetch_peer_name(int fd, char *ip, uint16_t *port)
{
    if (fd < 0 || !ip || !port) {
        return -1;
    }
    struct sockaddr_in addr;
    socklen_t len = sizeof addr;
    if (::getpeername(fd, (sockaddr *)&addr, &len) == -1) {
        return -1;
    }
#ifdef _WIN32
    strcpy_s(ip, 128, inet_ntoa(addr.sin_addr));
#else
    strcpy(ip, inet_ntoa(addr.sin_addr));
#endif
    *port = ntohs(addr.sin_port);
    //    if (!inet_ntop(AF_INET, &addr.sin_addr.s_addr, *ip, 128)) {
    //        return -1;
    //    }
    //    *port = ntohs(addr.sin_port);
    return 0;
}

int fetch_sock_name(int fd, char *ip, uint16_t *port)
{
    if (fd < 0 || !ip || !port) {
        return -1;
    }
    struct sockaddr_in addr;
    socklen_t len = sizeof addr;
    if (::getsockname(fd, (sockaddr *)&addr, &len) == -1) {
        return -1;
    }
#ifdef _WIN32
    strcpy_s(ip, 128, inet_ntoa(addr.sin_addr));
#else
    strcpy(ip, inet_ntoa(addr.sin_addr));
#endif
    *port = ntohs(addr.sin_port);
    return 0;
}
