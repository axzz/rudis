#include <iostream>
#include "server.h"
#include "object.h"
#include "store.h"
using namespace rudis;
using namespace std;

int main()
{

    cout << 0 << endl;
    auto a = RObject::CreateString("hello world");
    cout << 1 << endl;
    STORE.SetValue("hello", std::move(a));
    cout << 2 << endl;
    RObject *b;
    cout << 3 << endl;
    STORE.GetValue("hello", b, false);
    cout << 4 << endl;
    cout << *(b->CastString()) << endl;
}