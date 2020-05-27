#include "server.h"
#include <iostream>
#include <string.h>
namespace mynet
{
  Server::Server(uint16_t port):readCallback(NULL)
  {
    if ((listenFd = ::socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      std::cout << "socket error" << std::endl;
      exit(1);
    }

    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(INADDR_ANY);

    if (::bind(listenFd, (sockaddr *)&address, sizeof(address)) < 0)
    {
      std::cout << "bind error" << std::endl;
      exit(1);
    }
  }

  void Server::setReadEventCallback(ReadEventCallback cb){
      readCallback=cb;
  }

  void Server::start()
  {
    startListen();
    while (true)
    {
      Poller::instance().poll(activeSockets);
      for (auto activeSocket : activeSockets)
      {
        activeSocket->handleEvents();
      }
    }
  }



  void Server::startListen()
  {
    std::cout << "start listenning" << std::endl; 
    Socket *accepter = new Socket(listenFd);
    accepter->setReadCallback(std::bind(&Socket::connect, accepter, _1, readCallback));
    ::listen(accepter->fd(), 100);
  }
} // namespace rudis