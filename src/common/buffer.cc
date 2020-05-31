#include "buffer.h"
#include "unistd.h"

#include <iostream>
namespace rudis
{

    //TODO: 考虑客户端不规范问题
    inline void drop_char(Socket &skt)
    {
        char v;
        ::read(skt.fd(), &v, 1);
    }

    int get_number(Socket &skt)
    {
        char var='0';
        int len = 0;
        do
        {
            len = (10 * len) + (var - '0');
            ::read(skt.fd(), &var, 1);
        } while (var != '\r');
        drop_char(skt);
        return len;
    }

    RString get_row(Socket &skt)
    {
        drop_char(skt);
        int len = get_number(skt);
        RString res(len, ' ');
        ::read(skt.fd(), &res[0], len);
        drop_char(skt);drop_char(skt);
        return res;
    }

    vector<RString> reveive_buffer(Socket &skt)
    {
        // 获得命令数
        char var[32];
        drop_char(skt);
        int len = get_number(skt);
        vector<RString> res;
        for (int i = 0; i < len; ++i)
        {
            res.push_back(get_row(skt));
        }
        return res;
    }

    void callback_test(Socket &skt){
        auto res = reveive_buffer(skt);
        for(auto& str:res){
            std::cout << str << std::endl;
        }
    }
} // namespace rudis
