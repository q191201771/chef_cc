#include "socket_util.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

int set_socket_send_buf(int fd, int size)
{
	socklen_t varsize = sizeof size;
	return setsockopt(fd, SOL_SOCKET, SO_SNDBUF, (char *)&size, varsize);
}

int set_socket_recv_buf(int fd, int size)
{
    socklen_t varsize = sizeof size;
	return setsockopt(fd, SOL_SOCKET, SO_RCVBUF, (char *)&size, varsize);
}

int make_socket_nonblock(int fd)
{
    return fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
}

int make_socket_reuseable(int fd)
{
    int on = 1;
    return setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (void *)&on,
            (socklen_t)sizeof on);
}

int make_socket_keepalive(int fd)
{
    int on = 1;
    return setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (void *)&on,
            (socklen_t)sizeof on);
}

int fetch_listen_socket(const char *ip, uint16_t port)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        return -1;
    }

    make_socket_nonblock(sock);
    make_socket_reuseable(sock);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);
    if (::bind(sock, (struct sockaddr *)&addr, sizeof addr) == -1) {
        ::close(sock);
        return -1;
    }

    if (::listen(sock, 1024) == -1) {
        ::close(sock);
        return -1;
    }

    return sock;
}

int make_socket_nodelay(int fd)
{
    int on = 1;
    return setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (void *)&on,
            (socklen_t) sizeof on);
}

int fetch_peer_name(int fd, char **ip, uint16_t *port)
{
    if (fd < 0 || !ip || !port) {
        return -1;
    }
    struct sockaddr_in addr;
    socklen_t len = sizeof addr;
    if (::getpeername(fd, (sockaddr *)&addr, &len) == -1) {
        return -1;
    }
    if (!inet_ntop(AF_INET, &addr.sin_addr.s_addr, *ip, 128)) {
        return -1;
    }
    *port = ntohs(addr.sin_port);
    return 0;
}

int fetch_sock_name(int fd, char **ip, uint16_t *port)
{
    if (fd < 0 || !ip || !port) {
        return -1;
    }
    struct sockaddr_in addr;
    socklen_t len = sizeof addr;
    if (::getsockname(fd, (sockaddr *)&addr, &len) == -1) {
        return -1;
    }
    if (!inet_ntop(AF_INET, &addr.sin_addr.s_addr, *ip, 128)) {
        return -1;
    }
    *port = ntohs(addr.sin_port);
    return 0;
}
