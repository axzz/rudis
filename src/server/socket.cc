#include "server.h"
#include <unistd.h>
#include <iostream>

Socket::Socket(int fd) : fd_(fd), pfd_id(-1)
{
    setReadCallback(std::bind(&Socket::default_read, this, _1));
    Poller::instance().update(this);
    //TODO: log
}

Socket::~Socket()
{
    ::close(fd_);
    Poller::instance().remove(this);
}

void Socket::handleEvents()
{
    if ((revents_ & POLLHUP) and !(revents_ & POLLIN))
    {
        onClose();
    }
    if (revents_ & (POLLERR | POLLNVAL))
    {
        onError();
    }
    if (revents_ & (POLLIN | POLLPRI))
    {
        readCallback(*this);
    }
}

void Socket::connect(Socket &socket, ReadEventCallback cb)
{
    int connfd = ::accept(fd_, NULL, NULL);
    Socket *connect_socket = new Socket(connfd);
    if (cb == NULL)
    {
        connect_socket->setReadCallback(std::bind(&Socket::default_read, connect_socket, _1));
    }
    else
    {
        connect_socket->setReadCallback(cb);
    }
};

void Socket::close()
{
    std::cout << "Socket closed" << std::endl;
    delete this;
}

void Socket::shutdown()
{
    close();
}

void Socket::onClose()
{
    close();
}

void Socket::write(string buffer)
{
    const char *ptr = buffer.c_str();
    size_t left = buffer.size();
    ssize_t written;
    while (left > 0)
    {
        if ((written = ::write(fd_, ptr, left)) < 0)
        {
            if (written < 0 && errno == EINTR)
            {
                written = 0;
            }
            else
            {
                return;
            }
        }
        left -= written;
        ptr += written;
    }
}

void Socket::write(char *buffer, int n)
{
    string b(buffer, n);
    write(b);
}

void Socket::default_read(Socket &socket)
{
    char buf[1024];
    ssize_t n = ::read(fd_, buf, 1024);
    char reply[10] = "+OK\r\n";
    for (int i = 0; i < n; i++)
    {
        std::cout << buf[i];
    }
    if (n == 0)
    {
        close();
    }
    else
    {
        write(reply, 5);
    }
}

void Socket::onError()
{
    close();
}
