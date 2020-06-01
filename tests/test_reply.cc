#include <iostream>
#include "server.h"
#include "object.h"
#include "store.h"
#include "buffer.h"
using namespace rudis;
using namespace std;

void callback_test(Socket &skt)
{
    auto res = reveive_buffer(skt);
    ReplyBuffer rpy;
    rpy.mutli_init(res.size());
    for(auto s:res){
        rpy.push_str(s);
    }
    skt.write(rpy.c_str(), rpy.size());
}

int main()
{
    Server server(6324);
    server.setReadEventCallback(callback_test);
    server.start();
}