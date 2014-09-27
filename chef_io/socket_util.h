#ifndef _CHEF_CHEF_IO_SOCKET_UTIL_H_
#define _CHEF_CHEF_IO_SOCKET_UTIL_H_

#include <stdint.h>

/**
 * @ support win-platform also
 */

#ifdef _WIN32
void win_socket_init();
#endif

int set_socket_send_buf(int32_t fd, int size);
int set_socket_recv_buf(int32_t fd, int size);
int make_socket_nonblock(int32_t fd);
int make_socket_reuseable(int32_t fd);//for listen
int make_socket_keepalive(int32_t fd);
int make_socket_nodelay(int32_t fd);

/**
 * @return:
 *   succ: fd
 *   fail: -1
 */
int32_t fetch_listen_socket(const char *ip, uint16_t port);

int fetch_peer_name(int32_t fd, char *ip, uint16_t *port);
int fetch_sock_name(int32_t fd, char *ip, uint16_t *port);

#endif

