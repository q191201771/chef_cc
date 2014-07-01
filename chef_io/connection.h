#ifndef _CHEF_CHEF_IO_CONNECTION_H_
#define _CHEF_CHEF_IO_CONNECTION_H_

#include "io_tcp.h"
#include "buffer.h"
#include <stdint.h>
#include <boost/noncopyable.hpp>

using namespace chef;

enum link_status
{
    status_none = 0,
    status_linking,
    status_linked
};

class event_loop;
class connection : public boost::noncopyable
{
public:
    connection(event_loop *loop, const cio_conn_t &cc, int fd);
    ~connection();

    char *peer_ip() const {return peer_ip_;}
    uint16_t peer_port() const {return peer_port_;}
    const cio_conn_t &cio_conn() const {return cio_conn_;}
    void set_cio_conn(const cio_conn_t &cc) {cio_conn_ = cc;}
    void set_link_status(link_status s) {status_ = s;};

    void enable_read();
    void enable_write();
    void write(void *data, uint32_t len);
    void close_in_loop();

private:
    void epoll_cb(event_loop *loop, int fd, uint16_t event);
    void handle_read();
    void handle_write();
    void handle_error();

    event_loop *loop_;
    cio_conn_t cio_conn_;
    int fd_;
    char *peer_ip_;
    uint16_t peer_port_;
    char *local_ip_;
    uint16_t local_port_;
    link_status status_;
    bool is_del_;
    uint8_t *inbuf_;    
    buffer outbuf_;
};

#endif
