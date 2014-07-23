#ifndef _CHEF_CHEF_IO_IO_TCP_H_
#define _CHEF_CHEF_IO_IO_TCP_H_

#include <stdint.h>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

/**
 * TODO
 *  @demo
 *  @timer
 *  @elegant shutdown & dtor
 *  @connectout time out
 */

class io_tcp_impl;
namespace chef
{

struct cio_conn_t
{
    uint16_t thread_index_;
    uint64_t conn_id_;
    void *arg_;
};

/**
 * @brief:
 *   passive link,someone connect this server.
 * @param:
 *   1.const char *: peer ip
 *   2.uint16_t:     peer port
 */
typedef boost::function<void(cio_conn_t, const char *, uint16_t)> accept_cb_t;

/**
 * @brief:
 *   positive link,after call io_tcp::connect().
 *    
 * @warn: 
 *   before connect_status::connected or connect_status::fail,you may recv 
 *   connect_status::connecting.
 *
 *   if io_tcp::connect() fail,you will recv connect_status_fail first,then 
 *   recv close_cb_t,see close_cb_t brief get more info.
 */
//enum class connect_status
enum connect_status
{
    connecting,
    connected,
    fail
};
typedef boost::function<void(cio_conn_t, connect_status)> connect_cb_t;

/**
 * @brief:
 *   after this cb,buffer(param) will be release.
 * @param:
 *   1.void *:   buffer pointer
 *   2.uint32_t: buffer len
 *               <= 4096
 */
typedef boost::function<void(cio_conn_t, void *, uint32_t)> read_cb_t;

/**
 * @brief:
 *   link broke or closed by peer or user call io_tcp::close().
 *
 *   io_tcp will release all this connection's src autoly and this cio_conn_t 
 *   won't fire msg to user anymore.
 *    
 *   tips:user can release his cio_conn_t::arg_ safely in this callback.
 */
typedef boost::function<void(cio_conn_t)> close_cb_t;

/**
 * @brief:
 *   something wrong in this connection.
 *   for now,use should call io_tcp::close() in this callback.
 * @param:
 *   1.uint8_t: error_no
 *              for now,it always 0
 */
typedef boost::function<void(cio_conn_t, uint8_t)> error_cb_t;

/**
 * @brief:
 *   maybe use it to count io status,qos or something.
 * @param:
 *   1.uint64_t: call ::write successfully,it's single count,not sum
 *               >=0
 *   2.uint64_t: out pending buffer len
 *               >=0
 */
typedef boost::function<void(cio_conn_t, uint64_t, uint64_t)> write_cb_t;

class io_tcp : public boost::noncopyable
{
public:
    /**
     * @param:
     *       port:   -1: don't listen @ any port,only use to connect others.
     *   xxx_cb_t: NULL: don't watch this type of cb
     *     failno:    0: no error
     *                1: invalid param,like port=-100 or thread_num = 0
     *                2: ::bind failed
     * @return:
     *   NULL:failed,check param 'failno'
     */
    static io_tcp *create(const char *ip, int16_t port, uint16_t thread_num,
                          const accept_cb_t &acb,
                          const connect_cb_t &connect_cb,
                          const read_cb_t &rcb,
                          const close_cb_t &close_cb,
                          const error_cb_t &ecb,
                          const write_cb_t &wcb,
                          //uint8_t *failno = nullptr/*out*/);
                          uint8_t *failno = NULL/*out*/);
    
    /**
     * @brief:
     *   if running(called run() already),must call shutdown() first to cancel
     *   run()-blocking,after run() completed,call this.
     */
    static void destroy(io_tcp *param);

    /**
     * @brief:
     *   block-func
     */ 
    void run(); 
    
    void shutdown(); 
    
    /**
     * @brief:
     *   this func only for passive link.(::accept)
     *
     *   if didn't set,read_cb's void *arg will be NULL
     *   see enable_read brief know more
     * @param:
     *   fill cc' void *arg_
     */
    void set_user_arg(const cio_conn_t &cc); 
    
    /**
     * @brief:
     *   this func only for passive link.(::accept)
     *
     *   if didn't set,io_tcp won't ::read at this link
     *
     *   most of time,call set_user_arg() first,then call enable_read() or just
     *   call enable_read().
     */
    void enable_read(const cio_conn_t &cc);

    /**
     * @brief:
     *   @non-block
     *
     *   @io_tcp will do mem-copy inside if needed,so release data(param) after 
     *    this call is safe.
     */
    void write(const cio_conn_t &cc, void *data, uint32_t len);
    
    /**
     * @brief:
     *   @non-block 
     *    you should watch connect_cb to get result
     *   
     *   @as an positive link,set your void *arg(all cb will carry it) 
     *    at this moment if you need.
     */
    void connect(const char *ip, uint16_t port, void *arg);
    
    void close(const cio_conn_t &cc);
private:
    io_tcp();
    ~io_tcp();

    boost::scoped_ptr<io_tcp_impl> impl_;
};

};

#endif

