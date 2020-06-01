#include <iostream>
#include "server.h"
#include "object.h"
#include "store.h"
#include "buffer.h"
#include "command.h"
using namespace rudis;
using namespace std;

void callback_test(Socket &skt)
{
    vector<RString> params = reveive_buffer(skt);
    ReplyBuffer rpy;
    COMMAND.execute_command(params, rpy);
    skt.write(rpy.c_str(), rpy.size());
}

int main()
{
    Server server(6324);
    server.setReadEventCallback(callback_test);
    server.start();
}