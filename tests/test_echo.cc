#include <iostream>
#include "server.h"
#include "object.h"
#include "store.h"
#include "buffer.h"
using namespace rudis;
using namespace std;

// test function, can be deleted
int main()
{
    Server server(6324);
    // server.setReadEventCallback(callback_test);
    server.start();
}