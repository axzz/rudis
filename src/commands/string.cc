#include "command.h"
#include "store.h"
#include <iostream>
namespace rudis
{
    RuError command(const vector<RString> &params, ReplyBuffer& reply)
    {
        reply.reply_ok();
        return RuError_ok;
    }


    RuError set(const vector<RString> &params, ReplyBuffer& reply)
    {
        std::cout << "set:" << params[1] << ":" << params[2] << std::endl;
        STORE.SetValue(params[1], RObject::CreateString(params[2]));
        reply.reply_ok();
        return RuError_ok;
    }

    RuError get(const vector<RString> &params, ReplyBuffer& reply)
    {
        RObject* value;
        RuError err = STORE.GetValueByType(params[1], value, R_STRING, true);
        if(err!=RuError_ok){
            if(err==RuError_no_exist){
                reply.reply_simple_error();
            }else{
                reply.reply_simple_error();
            }
            return err;
        }
        reply.push_str(*(value->CastString()));
        return RuError_ok;
    }
} // namespace rudis
