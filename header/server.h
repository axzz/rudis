#pragma once
#include <vector>
#include <unordered_map>
#include <string>

#include <functional>
#include <sys/poll.h>
#include <netinet/in.h>

namespace mynet
{
    using std::string;
    using std::unordered_map;
    using std::vector;
    using std::placeholders::_1;
    class Socket
    {
    public:
        typedef std::function<void(Socket&)> ReadEventCallback;
        Socket(int fd);
        ~Socket();

        void connect(Socket& socket, ReadEventCallback cb);            //socket为listen socket时会调用，新建一个connection socket
        void write(string buffer); //主动writeN; //可优化为在另一线程write
        void write(char *buffer, int n);
        void setReadCallback(ReadEventCallback cb) { readCallback = cb; };
        void default_read(Socket&); //主要逻辑 被poll调用的接受者，处理，然后通过write发送出去；
        void shutdown();     //主动shutdown
        void close();        //主动close 包括earse pollfd/earse dict/close fd/delete self
        void onClose();      // 对方close
        void onError();
        void handleEvents();
        int index() { return pfd_id; };
        void set_index(int idx) { pfd_id = idx; };
        int fd() { return fd_; };
        void set_revents(int revents) { revents_ = revents; };

    private:
        int pfd_id;
        int fd_;
        int revents_;
        ReadEventCallback readCallback;
        string inputBuffer;
    };

    class Poller
    {
    public:
        static Poller &instance()
        {
            static Poller poller;
            return poller;
        };

        void update(Socket *socket);
        void remove(Socket *socket);
        void poll(vector<Socket *> &activeSockets);

    private:
        Poller(){};
        unordered_map<int, Socket *> sockets; //TODO: 智能指针
        vector<struct pollfd> polls;
    };

    class Server
    {
        typedef std::function<void(Socket&)> ReadEventCallback;

    public:
        Server(uint16_t port);
        void setReadEventCallback(ReadEventCallback cb);
        void start(); //start listening and loop
    private:
        void startListen();
        int listenFd;
        sockaddr_in address;
        vector<Socket *> activeSockets;
        ReadEventCallback readCallback;
    };
} // namespace mynet