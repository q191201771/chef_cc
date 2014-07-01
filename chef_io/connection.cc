#include "connection.h"
#include "event_loop.h"
#include "socket_util.h"
#include "assert_.h"
#include "async_log.h"
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <boost/bind.hpp>

connection::connection(event_loop *loop, const cio_conn_t &cc, int fd)
    : loop_(loop)
    , cio_conn_(cc)
    , fd_(fd)
    , status_(status_none)
    , is_del_(false)
{
    loop_->add(this);
    peer_ip_ = new char[128];
    local_ip_ = new char[128];
    memset(peer_ip_, 0, 128);
    memset(local_ip_, 0, 128);
    fetch_peer_name(fd, (char **)&peer_ip_, &peer_port_);
    fetch_sock_name(fd, (char **)&local_ip_, &local_port_);
    inbuf_ = new uint8_t[4096];
    loop_->add(fd_, boost::bind(&connection::epoll_cb, this, _1, _2, _3));
    //CHEF_TRACE_DEBUG("connection(%p),loop=%p,thread_index=%u,conn_id=%lu,fd=%d",
    //        this, loop, cc.thread_index_, cc.conn_id_, fd);
}

connection::~connection()
{
    //CHEF_TRACE_DEBUG("~connection(),this=%p.", this);
    delete []peer_ip_;
    delete []local_ip_;
    delete []inbuf_;
}

void connection::enable_read()
{
    CHEF_ASSERT(status_ == status_linked);
    loop_->modr(fd_, true);
}

void connection::enable_write()
{
    CHEF_ASSERT(status_ == status_linking || status_ == status_linked);
    loop_->modw(fd_, true);
}

void connection::epoll_cb(event_loop *loop, int fd, uint16_t event)
{
    CHEF_ASSERT(loop == loop_ && fd == fd_);
    if (!is_del_ && (event & epoll_event_read)) {
        handle_read();    
    }
    //can't else if
    if (!is_del_ && (event & epoll_event_write)) {
        handle_write();
    }
    if (!is_del_ && (event & epoll_event_error)) {
        handle_error();
    }
}

void connection::handle_read()
{
    int ret = read(fd_, (void *)inbuf_, 4096);
    if (ret < 0) {
        if (errno != EINTR && errno != EAGAIN) {
            CHEF_TRACE_DEBUG("handle_read,error.");
            loop_->error_cb()(cio_conn_, 0);
        }
        return;
    } else if (ret == 0) {
        CHEF_TRACE_DEBUG("close by peer,conn=%p,fd=%d", this, fd_);
        close_in_loop();
    } else {
        loop_->read_cb()(cio_conn_, inbuf_, ret);
    }
}

void connection::handle_write()
{
    if (status_ == status_linking) {
        int optval = 0;
        socklen_t optlen = sizeof optval;
        int ret = getsockopt(fd_, SOL_SOCKET, SO_ERROR, (void *)&optval, &optlen);
        if (ret == -1) {
            loop_->connect_cb()(cio_conn_, connect_status::fail);
            close_in_loop();
            return;
        }
        if (optval) {
            //!!!not sure if EINTR || EAGAIN,have chance,so close it for now
            //if (optval != EINTR && optval != EAGAIN) {
            loop_->connect_cb()(cio_conn_, connect_status::fail);
            close_in_loop();
            //}
            return;
        }
        
        status_ = status_linked;
        loop_->modr(fd_, true);
        if (outbuf_.readable() > 0) {
           loop_->modw(fd_, true); 
        }
        loop_->connect_cb()(cio_conn_, connect_status::connected);
        return;
    } else if (status_ == status_linked) {
        uint64_t succ_writed = ::write(fd_, 
                                   outbuf_.read_pos(), 
                                   outbuf_.readable());
        if (succ_writed < 0) {
            if (errno != EINTR && errno != EAGAIN) {
                CHEF_TRACE_DEBUG("handle_write,error.");
                loop_->error_cb()(cio_conn_, 0);
            }
            return;
        } else {
            outbuf_.erase(succ_writed);
            if (outbuf_.readable() == 0) {
                loop_->modw(fd_, false);
            }
            loop_->write_cb()(cio_conn_, succ_writed, outbuf_.readable());
        }
    }
}

void connection::handle_error()
{
    CHEF_TRACE_DEBUG("handle_error,error.");
    loop_->error_cb()(cio_conn_, 0);
}

void connection::close_in_loop()
{
    CHEF_ASSERT(status_ == status_linking || status_ == status_linked);
    loop_->close_cb()(cio_conn_);
    loop_->del(fd_);

    ::close(fd_);
    fd_ = -1;
    status_ = status_none;

    is_del_ = true;
    loop_->del(this);
}

void connection::write(void *data, uint32_t len)
{
    CHEF_ASSERT(data && len && status_ != status_none);
    if (status_ == status_linking || outbuf_.readable() > 0) {
        outbuf_.append((const char *)data, len);
        enable_write();
        loop_->write_cb()(cio_conn_, 0, outbuf_.readable());
        return;
    }
    int64_t succ_writed = ::write(fd_, data, len);
    if (succ_writed < 0) {
        if (errno != EINTR && errno != EAGAIN) {
            CHEF_TRACE_DEBUG("write,error.");
            loop_->error_cb()(cio_conn_, 0);
        }
        return;
    }
    else {
        loop_->write_cb()(cio_conn_, succ_writed, len - succ_writed);
        if (succ_writed == len) {
            return;
        }
        else if (succ_writed < len) {
            outbuf_.append((const char*)data + succ_writed, len - succ_writed);
            enable_write();
            return;
        }
        CHEF_ASSERT(0);
    }
}

