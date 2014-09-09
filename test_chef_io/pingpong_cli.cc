#include "io_tcp.h"
#include "async_log.h"
#include "task_thread.h"
#include <boost/bind.hpp>

using namespace boost;
using namespace chef;

io_tcp_ptr srv;
char srv_ip[128] = {0};
uint16_t srv_port = 0;;
char *block = NULL;
uint32_t block_size = 0;

void close_conn(cio_conn_t cc);

void accept_cb(cio_conn_t cc, const char *peer_ip, uint16_t peer_port)
{
    CHEF_TRACE_DEBUG("user:accept_cb(),thread_id=%u,conn_id=%lu,ip=%s,port=%u.",
            cc.thread_index_, cc.conn_id_, peer_ip, peer_port);

    cc.arg_ = NULL;
    srv->set_user_arg(cc);
    srv->enable_read(cc);
}
void connect_cb(cio_conn_t cc, connect_status cs)
{
    CHEF_TRACE_DEBUG("user:connect_cb(),thread_id=%u,conn_id=%lu,status=%u.",
            cc.thread_index_, cc.conn_id_, cs);
    if (cs == connect_status::connecting) {
        //do nothing
    } else if (cs == connect_status::connected) {
        srv->write(cc, block, block_size);
    } else if (cs == connect_status::fail) {
        srv->connect(srv_ip, srv_port, NULL);
    }
}
void read_cb(cio_conn_t cc, void *buf, uint32_t len)
{
    CHEF_TRACE_DEBUG("user:read_cb(),thread_id=%u,conn_id=%lu,len=%u.",
            cc.thread_index_, cc.conn_id_, len);
    //echo
    srv->write(cc, buf, len);
}
void close_cb(cio_conn_t cc)
{
    CHEF_TRACE_DEBUG("user:close_cb(),thread_id=%u,conn_id=%lu.",
            cc.thread_index_, cc.conn_id_);
}
void error_cb(cio_conn_t cc, uint8_t error_no)
{
    CHEF_TRACE_DEBUG("user:error_cb(),thread_id=%u,conn_id=%lu.",
            cc.thread_index_, cc.conn_id_);
    srv->close(cc);
}
void write_cb(cio_conn_t cc, uint64_t succ_writed, uint64_t pending_len)
{
    CHEF_TRACE_DEBUG("user:writed_cb(),thread_id=%u,conn_id=%lu,succ=%lu,pending=%lu.", 
            cc.thread_index_, cc.conn_id_, succ_writed, pending_len);
}

int main(int argc, char **argv)
{
    if (argc != 5) {
        printf("usage: <srv ip> <srv port> <block size> <how much connect>");
        return 0;
    }
    strcpy(srv_ip, argv[1]);
    srv_port = atoi(argv[2]);
    block_size = atoi(argv[3]);
    int connection = atoi(argv[4]);
    block = new char[block_size];
    memset(block, 'x', block_size);

    chef::async_log::get_mutable_instance().init();
    srv = io_tcp::create("0.0.0.0", -1, 4, accept_cb, connect_cb, read_cb,
                close_cb, error_cb, write_cb);
    if (!srv) {
        CHEF_TRACE_DEBUG("user:init fail.");
        return 0;
    }
    for (int i = 0; i < connection; ++i) {
        srv->connect(srv_ip, srv_port, NULL);
    }
    srv->run();
    delete []block;
    return 0;
}
