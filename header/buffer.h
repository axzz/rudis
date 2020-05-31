#include "object.h"
#include "server.h"
#include <vector>
namespace rudis
{
    using std::vector;

    //收到请求时调用，直接产生
    vector<RString> reveive_buffer(Socket &skt);

    //reply生成器
    class ReplyBuffer
    {
    private:
        vector<char> buffer;
        /* data */
    public:
        ReplyBuffer();
        ~ReplyBuffer();
        void push();

        char *c_str();//应使用
        size_t size() { return buffer.size(); };

        void reply_ok();
        void reply_error();
    };

    void callback_test(Socket &skt);

} // namespace rudis
