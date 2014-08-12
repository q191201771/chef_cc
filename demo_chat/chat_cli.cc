#include "io_tcp.h"
#include "async_log.h"
#include "_thread.h"
#include "wait_event.h"
#include "_time.h"
#include "assert_.h"
#include "chunk.h"
#include "chat.pb.h"
#include <boost/bind.hpp>
using namespace chef;

io_tcp_ptr srv;
wait_event connect_event;
cio_conn_t cio_conn;
buffer inbuf;
uint32_t chunk_len = 0;

void connect_cb(cio_conn_t cc, connect_status cs)
{
    if (cs == connect_status::fail) {
        printf("---connect fail.\n");
        printf("---bye bye.\n");
        exit(0);
    } else if (cs == connect_status::connected) {
        cio_conn = cc;
        connect_event.notify();
    }
}
void read_cb(cio_conn_t cc, void *buf, uint32_t len)
{
    inbuf.append((const char *)buf, len);
    for (; ; ) {
        if (chunk_len == 0) {
            if (inbuf.readable() < sizeof(uint32_t)) {
                return;
            }
            chunk_len = parse_uint32(inbuf.read_pos());
            if (chunk_len == 0 || chunk_len > 65535) {
                printf("---parse error,%u.", chunk_len);
                srv->close(cc);
                return;
            }
        }
        if (inbuf.readable() < chunk_len) {
            return;
        }
        chat::msg msg;
        if (!msg.ParseFromArray(inbuf.read_pos() + sizeof(uint32_t), 
                    chunk_len - sizeof(uint32_t))) {
            printf("---parse error.\n");
            srv->close(cc);
            return;
        }
        printf("---%s:%s.\n", msg.name().c_str(), msg.data().c_str());
        inbuf.erase(chunk_len);
        chunk_len = 0;
    }
}
void close_cb(cio_conn_t cc)
{
    printf("---link broken.\n");
    printf("---bye bye.\n");
    exit(0);
}
void error_cb(cio_conn_t cc, uint8_t error_no)
{
    srv->close(cc);
}

void main_loop(io_tcp_ptr itp)
{
    itp->run();
}

int main(int argc, char **argv)
{
    if (argc != 4) {
        printf("usage: <ip> <port> <name>\n");
        return 0;
    }
    chef::async_log::get_mutable_instance().init();
    srv = io_tcp::create("0.0.0.0", -1, 1, NULL, connect_cb, read_cb,
                close_cb, error_cb, NULL);
    if (!srv) {
        CHEF_TRACE_DEBUG("user:init fail.");
        return 0;
    }
    thread io_thread(boost::bind(&main_loop, srv), "io loop");
    io_thread.start();

    printf("---connecting...\n");
    srv->connect(argv[1], atoi(argv[2]), NULL);
    connect_event.wait();
    printf("---connect succ.\n");

    char *data = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&data, &len, stdin)) != -1) {
        data[strlen(data) - 1] = '\0';
        if (!strcmp(data, "quit")) {
            break;
        }
    //for (; ; ) {
        //sleep(1);
        //char data[4096] = {0};
        //time::format_now_time3(data);
        //static char cc = 0;
        //memset(data, ++cc, 4094);
        buffer buf(1024);
        chat::msg msg;
        msg.set_name(argv[3]);
        msg.set_data(data);
        int msg_len = msg.ByteSize();
        uint32_t total_len = sizeof(uint32_t) + msg_len;
        serialize_uint32(total_len, buf.write_pos());
        buf.seek_write(sizeof(uint32_t));
        buf.reserve(msg_len);
        msg.SerializeToArray(buf.write_pos(), msg_len);
        buf.seek_write(msg_len);
        srv->write(cio_conn, buf.read_pos(), buf.readable());
    }
    free(data);

    srv.reset();   
    //io_tcp::destroy(srv);
    printf("---bye bye.\n");
    return 0;
}
