#include "buffer.h"
#include "unistd.h"

#include <iostream>

//TODO: 考虑客户端不规范问题
namespace rudis
{
    static const char CRLF[] = "\r\n";
    // TODO: 变成验证char
    inline void drop_char(Socket &skt)
    {
        char v;
        ::read(skt.fd(), &v, 1);
    }

    int get_number(Socket &skt)
    {
        char var = '0';
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
        drop_char(skt);
        drop_char(skt);
        return res;
    }

    vector<RString> reveive_buffer(Socket &skt)
    {
        // 获得命令数
        drop_char(skt);
        int len = get_number(skt);
        vector<RString> res;
        for (int i = 0; i < len; ++i)
        {
            res.push_back(get_row(skt));
        }
        return res;
    }


    void ReplyBuffer::clear()
    {
        buffer.clear();
    }

    void ReplyBuffer::push(RString str)
    {
        for (char c : str)
        {
            buffer.push_back(c);
        }
    }

    void ReplyBuffer::push_CRLF()
    {
        for (char c : CRLF)
        {
            buffer.push_back(c);
        }
    }

    void ReplyBuffer::reply_ok()
    {
        reply_state("OK");
    }

    void ReplyBuffer::reply_state(RString str)
    {
        clear();
        push("+");
        push(str);
        push_CRLF();
    }

    void ReplyBuffer::reply_simple_error()
    {
        reply_error("err");
    }

    void ReplyBuffer::reply_error(RString str)
    {
        clear();
        push("-");
        push(str);
        push_CRLF();
    }

    void ReplyBuffer::push_int(int num)
    {
        push(":");
        push(std::to_string(num));
        push_CRLF();
    }

    void ReplyBuffer::push_str(RString str)
    {
        if (str.size() == 0)
        {
            push("$-1");
            push_CRLF();
        }
        else
        {
            push("$" + std::to_string(str.size()));
            push_CRLF();
            push(str);
            push_CRLF();
        }
    }

    void ReplyBuffer::mutli_init(int num)
    {
        clear();
        push("*" + std::to_string(num));
        push_CRLF();
    }
} // namespace rudis
