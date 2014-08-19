#include "io_tcp.h"
#include "wait_event.h"
#include "buffer.h"
#include "chunk.h"
#include "chat.pb.h"
#include <string>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

using chef::io_tcp_ptr;
using chef::cio_conn_t;
using chef::connect_status;
using chef::wait_event;
using chef::buffer;

class chat_cli : public boost::noncopyable
               , public boost::enable_shared_from_this<chat_cli>
{
public:
    chat_cli(char *ip, int16_t port)
        : ip_(ip)
        , port_(port)
        , it_(NULL)
        , chunk_len_(0)
        , closed_(false)
    {
    }
    ~chat_cli()
    {
    }
    bool init()
    {
         it_ = chef::io_tcp::create("0.0.0.0", -1, 1, NULL,
                boost::bind(&chat_cli::connect_cb, this, _1, _2),
                boost::bind(&chat_cli::read_cb, this, _1, _2, _3),
                boost::bind(&chat_cli::close_cb, this, _1),
                boost::bind(&chat_cli::error_cb, this, _1, _2),
                NULL);
        if (!it_) {
            printf("chef::io_tcp::create fail.\n");
            return false;
        }
        return true;
    }
    bool connect()
    {
        boost::thread t(boost::bind(&chef::io_tcp::run, it_));
        it_->connect(ip_.c_str(), port_, NULL);
        if (!connect_event_.wait_for(5000)) {
            /// connect timeout
            return false;
        }
        return connect_succ_;
    }
    void write(void *data, uint32_t len)
    {
        it_->write(cc_, data, len);
    }
    bool closed() const { return closed_; }
private:
    void connect_cb(cio_conn_t cc, connect_status cs)
    {
        cc_ = cc;
        if (cs == connect_status::fail) {
            connect_succ_ = false;
            connect_event_.notify();
        } else if (cs == connect_status::connected) {
            connect_succ_ = true;
            connect_event_.notify();
        } else if (cs == connect_status::connecting) {
            /// do nothing
        }
    }
    void read_cb(cio_conn_t cc, void *buf, uint32_t len)
    {
        inbuf_.append((const char *)buf, len);
        for (; ; ) {
            if (chunk_len_ == 0) {
                if (inbuf_.readable() < sizeof(uint32_t)) {
                    return;
                }
                chunk_len_ = parse_uint32(inbuf_.read_pos());
                if (chunk_len_ == 0 || chunk_len_ > 65535) {
                    printf("---parse error,%u.", chunk_len_);
                    it_->close(cc);
                    return;
                }
            }
            if (inbuf_.readable() < chunk_len_) {
                return;
            }
            chat::msg msg;
            if (!msg.ParseFromArray(inbuf_.read_pos() + sizeof(uint32_t), 
                        chunk_len_ - sizeof(uint32_t))) {
                printf("---parse error.\n");
                it_->close(cc);
                return;
            }
            printf("---%s:%s.\n", msg.name().c_str(), msg.data().c_str());
            inbuf_.erase(chunk_len_);
            chunk_len_ = 0;
        }
    }
    void close_cb(cio_conn_t cc)
    {
        closed_ = true;
    }
    void error_cb(cio_conn_t cc, uint8_t error_no)
    {
        it_->close(cc);
    }

private:
    std::string ip_;
    int16_t port_;
    io_tcp_ptr it_;
    cio_conn_t cc_;
    wait_event connect_event_;
    bool connect_succ_;
    buffer inbuf_;
    uint32_t chunk_len_;
    bool closed_;
};
typedef boost::shared_ptr<chat_cli> chat_cli_ptr;

int main(int argc, char **argv)
{
    if (argc != 4) {
        printf("usage: <ip> <port> <name>\n");
        return 0;
    }

    chat_cli_ptr cli(new chat_cli(argv[1], (int16_t)atoi(argv[2])));
    if (!cli->init()) {
        printf("---bye bye.\n");
        return 0;
    }
    printf("---connecting...\n");
    if (!cli->connect()) {
        printf("---connect fail.\n");
        printf("---bye bye.\n");
        return 0;
    } else {
        printf("---connect succ.\n");
    }

    char *data = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&data, &len, stdin)) != -1) {
        data[strlen(data) - 1] = '\0';
        if (!strcmp(data, "quit")) {
            break;
        }
        if (cli->closed()) {
            printf("---link broken.\n");
            printf("---bye bye.\n");
            break;
        }
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
        cli->write(buf.read_pos(), buf.readable());
    }
    free(data);

    printf("---bye bye.\n");
    return 0;
}
