#ifndef _CHEF_CHEF_IO_SOCKET_UTIL_H_
#define _CHEF_CHEF_IO_SOCKET_UTIL_H_

#include <stdint.h>

int set_socket_send_buf(int fd, int size);
int set_socket_recv_buf(int fd, int size);
int make_socket_nonblock(int fd);
int make_socket_reuseable(int fd);//for listen
int make_socket_keepalive(int fd);
int make_socket_nodelay(int fd);

/**
 * @return:
 *   succ: fd
 *   fail: -1
 */
int fetch_listen_socket(const char *ip, uint16_t port);

int fetch_peer_name(int fd, char **ip, uint16_t *port);
int fetch_sock_name(int fd, char **ip, uint16_t *port);

#endif

