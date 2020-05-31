#include "server.h"
#include <errno.h>
#include <iostream>
#include "assert.h"
#define INFTIM -1

void Poller::update(Socket *socket)
{
  if (socket->index() < 0)
  {
    pollfd pfd;
    pfd.fd = socket->fd();
    pfd.events = POLLIN | POLLPRI; // 更常规的服务器此处可变
    pfd.revents = 0;
    polls.push_back(pfd);
    socket->set_index(static_cast<int>(polls.size()) - 1);
    sockets[pfd.fd] = socket;
  }
  else
  {
    size_t idx = socket->index();
    auto &pfd = polls[idx];
    pfd.fd = socket->fd();
    pfd.events = POLLIN | POLLPRI;
    pfd.revents = 0;
  }
}

void Poller::remove(Socket *socket)
{
  int idx = socket->index();
  assert(sockets.find(socket->fd()) != sockets.end());
  sockets.erase(socket->fd());
  if (idx == static_cast<int>(polls.size() - 1))
  {
    polls.pop_back();
  }
  else
  {
    auto last_socket = sockets[polls.back().fd];
    std::iter_swap(polls.begin() + idx, polls.end() - 1);
    last_socket->set_index(idx);
    polls.pop_back();
  }
}

void Poller::poll(vector<Socket *> &activeSockets)
{
  int numEvents = ::poll(&*polls.begin(), polls.size(), INFTIM);
  int savedError = errno;
  activeSockets.clear();
  if (numEvents == 0)
  {
    //TODO: log
  }
  else if (numEvents < 0)
  {
    if (savedError != EINTR)
    {
      errno = savedError;
      //TODO: log
    }
  }
  else
  {
    for (auto &p : polls)
    {
      if (numEvents == 0)
      {
        break;
      }
      if (p.revents > 0)
      {
        --numEvents;
        Socket *socket = sockets.find(p.fd)->second;
        socket->set_revents(p.revents);
        activeSockets.push_back(socket);
      }
    }
  }
}
