#pragma once
#include "object.h"
#include "server.h"
#include <vector>
namespace rudis
{
    using std::vector;

    //收到请求时调用，直接产生
    vector<RString> reveive_buffer(Socket &skt);

    //reply生成器 builder
    class ReplyBuffer
    {
    private:
        vector<char> buffer;
        /* data */
    public:
        ReplyBuffer(){};
        ~ReplyBuffer(){};

        char *c_str() { return &buffer[0]; };
        size_t size() { return buffer.size(); };

        void clear();
        void reply_ok();
        void reply_state(RString str);
        void reply_simple_error();
        void reply_error(RString str);
        void push_int(int num);
        void push_str(RString str);
        void mutli_init(int num);

    private:
        void push(RString str);
        void push_CRLF();
    };

} // namespace rudis
