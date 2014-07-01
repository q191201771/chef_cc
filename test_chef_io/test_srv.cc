#include "io_tcp.h"
#include "async_log.h"
#include "task_thread.h"
#include "assert_.h"
#include "wait_event.h"
#include <boost/bind.hpp>

//using namespace boost;
using namespace chef;

io_tcp *srv = NULL;
task_thread *tt = NULL;
bool shutdown = false;
wait_event exit_event;

void close_conn(cio_conn_t cc);

void accept_cb(cio_conn_t cc, const char *peer_ip, uint16_t peer_port)
{
    CHEF_TRACE_DEBUG("user:accept_cb(),thread_id=%u,conn_id=%lu,ip=%s,port=%u.",
            cc.thread_index_, cc.conn_id_, peer_ip, peer_port);

    cc.arg_ = NULL;
    srv->set_user_arg(cc);
    srv->enable_read(cc);
    tt->add(boost::bind(&close_conn, cc), 200);
}
void connect_cb(cio_conn_t cc, connect_status cs)
{
    CHEF_TRACE_DEBUG("user:connect_cb(),thread_id=%u,conn_id=%lu,status=%u.",
            cc.thread_index_, cc.conn_id_, cs);
    if (cs == connect_status::connected) {
        if (srv) {  //may other srv
            srv->write(cc, (void *)"test", 4);
        }
    }
}
void read_cb(cio_conn_t cc, void *buf, uint32_t len)
{
    CHEF_TRACE_DEBUG("user:read_cb(),thread_id=%u,conn_id=%lu,buf=%s,len=%u.",
            cc.thread_index_, cc.conn_id_, (char *)buf, len);
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

void run()
{
    srv->run();
    exit_event.notify();
}

void shutdown_io()
{
    srv->shutdown(); 
    shutdown = true;
}
void close_conn(cio_conn_t cc)
{
    if (srv) {  //FIXME multithread,may fake check
        srv->close(cc);
    }
}

int main()
{
    int test_num = 100;

    chef::async_log::get_mutable_instance().init(chef::async_log::debug, false, true);
    CHEF_TRACE_DEBUG("hello world.");
    io_tcp *srv1 = io_tcp::create(NULL, 8384, 4, NULL, connect_cb, 
                            read_cb, close_cb, error_cb, write_cb);
    CHEF_ASSERT(!srv1);
    srv1 = io_tcp::create("1.2.3.4", 8384, 4, NULL, NULL, 
                            read_cb, close_cb, error_cb, write_cb);
    CHEF_ASSERT(!srv1);
    srv1 = io_tcp::create("0.0.0.0", 0, 4, accept_cb, connect_cb, 
                            read_cb, close_cb, error_cb, write_cb);
    CHEF_ASSERT(!srv1);
    srv1 = io_tcp::create("0.0.0.0", 8384, 0, accept_cb, connect_cb, 
                            read_cb, close_cb, error_cb, write_cb);
    CHEF_ASSERT(!srv1);
    io_tcp *srv2 = io_tcp::create("0.0.0.0", 8384, 4, accept_cb, NULL, 
                            read_cb, close_cb, NULL, write_cb);
    CHEF_ASSERT(srv2);
    uint8_t failno = 0;
    srv1 = io_tcp::create("0.0.0.0", 8384, 4, accept_cb, connect_cb, 
                            read_cb, close_cb, error_cb, write_cb, &failno);
    CHEF_ASSERT(!srv1);
    CHEF_ASSERT(failno == 2);
    CHEF_TRACE_DEBUG("[1/%d] test create done.", test_num);
    io_tcp::destroy(srv2);
    CHEF_TRACE_DEBUG("[2/%d] test single create & single destroy done.", test_num);

    io_tcp *srv3 = io_tcp::create("0.0.0.0", 8384, 4, accept_cb, 
                            connect_cb, read_cb, close_cb, error_cb, write_cb);
    CHEF_ASSERT(srv3);
    srv3->connect("0.0.0.0", 8384, NULL);
    srv3->shutdown();
    srv3->connect("0.0.0.0", 8384, NULL);
    srv3->shutdown();
    srv3->connect("0.0.0.0", 1000, NULL);
    srv3->shutdown();
    io_tcp::destroy(srv3);
    CHEF_TRACE_DEBUG("[3/%d] test mess shutdown & mess connect done.", test_num);

    printf("-----srv begin.\n");
    srv = io_tcp::create("0.0.0.0", 8384, 4, accept_cb, connect_cb, read_cb,
                            close_cb, error_cb, write_cb);
    CHEF_ASSERT(srv);
    tt = new task_thread();
    tt->start();
    tt->add(boost::bind(&shutdown_io), 1000);
    thread t(boost::bind(&run));
    t.start();
    for (int i = 0; i < 10000; ++i) {
        srv->connect("0.0.0.0", 8384, NULL);
    }
    exit_event.wait();
    io_tcp::destroy(srv);
    srv = NULL;
    delete tt;
    CHEF_TRACE_DEBUG("all test done.");

    return 0;
}
