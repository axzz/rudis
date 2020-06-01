#include "command.h"
#include <iostream>
#include <algorithm>
namespace rudis
{
    RudisCommand CommandTable::commands_[] = {
        {"command", ATTR_READ, 1, &command},
        {"set", ATTR_WRITE, 3, &set},
        {"get", ATTR_READ, 2, &get},
    };
    //  RudisCommand CommandTable::commands_[] = {
    //     // key
    //     {"type", ATTR_READ, 2, &type},
    //     {"exists", ATTR_READ, 2, &exists},
    //     {"del", ATTR_WRITE, -2, &del},
    //     {"expire", ATTR_READ, 3, &expire},
    //     {"ttl", ATTR_READ, 2, &ttl},
    //     {"pexpire", ATTR_READ, 3, &pexpire},
    //     {"pttl", ATTR_READ, 2, &pttl},
    //     {"expireat", ATTR_READ, 3, &expireat},
    //     {"pexpireat", ATTR_READ, 3, &pexpireat},
    //     {"persist", ATTR_READ, 2, &persist},
    //     {"move", ATTR_WRITE, 3, &move},
    //     {"keys", ATTR_READ, 2, &keys},
    //     {"randomkey", ATTR_READ, 1, &randomkey},
    //     {"rename", ATTR_WRITE, 3, &rename},
    //     {"renamenx", ATTR_WRITE, 3, &renamenx},
    //     {"scan", ATTR_READ, -2, &scan},
    //     {"sort", ATTR_READ, -2, &sort},
    //     {"dump", ATTR_READ, 2, &dump},
    //     {"restore", ATTR_WRITE, -4, &restore},
    //     {"migrate", ATTR_READ, -6, &migrate},

    //     // server
    //     {"select", ATTR_READ, 2, &select},
    //     {"dbsize", ATTR_READ, 1, &dbsize},
    //     {"bgsave", ATTR_READ, 1, &bgsave},
    //     {"save", ATTR_READ, 1, &save},
    //     {"lastsave", ATTR_READ, 1, &lastsave},
    //     {"flushdb", ATTR_WRITE, 1, &flushdb},
    //     {"flushall", ATTR_WRITE, 1, &flushall},
    //     {"client", ATTR_READ, -2, &client},
    //     {"debug", ATTR_READ, -2, &debug},
    //     {"shutdown", ATTR_READ, -1, &shutdown},
    //     {"bgrewriteaof", ATTR_READ, 1, &bgrewriteaof},
    //     {"ping", ATTR_READ, 1, &ping},
    //     {"echo", ATTR_READ, 2, &echo},
    //     {"info", ATTR_READ, -1, &info},
    //     {"monitor", ATTR_READ, 1, &monitor},
    //     {"auth", ATTR_READ, 2, &auth},
    //     {"slowlog", ATTR_READ, -2, &slowlog},
    //     {"config", ATTR_READ, -3, &config},

    //     // string
    //     {"strlen", ATTR_READ, 2, &strlen},
    //     {"set", ATTR_WRITE, 3, &set},
    //     {"mset", ATTR_WRITE, -3, &mset},
    //     {"msetnx", ATTR_WRITE, -3, &msetnx},
    //     {"setnx", ATTR_WRITE, 3, &setnx},
    //     {"setex", ATTR_WRITE, 4, &setex},
    //     {"psetex", ATTR_WRITE, 4, &psetex},
    //     {"get", ATTR_READ, 2, &get},
    //     {"getset", ATTR_WRITE, 3, &getset},
    //     {"mget", ATTR_READ, -2, &mget},
    //     {"append", ATTR_WRITE, 3, &append},
    //     {"bitcount", ATTR_READ, -2, &bitcount},
    //     {"bitop", ATTR_WRITE, -4, &bitop},
    //     {"getbit", ATTR_READ, 3, &getbit},
    //     {"setbit", ATTR_WRITE, 4, &setbit},
    //     {"incr", ATTR_WRITE, 2, &incr},
    //     {"decr", ATTR_WRITE, 2, &decr},
    //     {"incrby", ATTR_WRITE, 3, &incrby},
    //     {"incrbyfloat", ATTR_WRITE, 3, &incrbyfloat},
    //     {"decrby", ATTR_WRITE, 3, &decrby},
    //     {"getrange", ATTR_READ, 4, &getrange},
    //     {"setrange", ATTR_WRITE, 4, &setrange},

    //     // list
    //     {"lpush", ATTR_WRITE, -3, &lpush},
    //     {"rpush", ATTR_WRITE, -3, &rpush},
    //     {"lpushx", ATTR_WRITE, -3, &lpushx},
    //     {"rpushx", ATTR_WRITE, -3, &rpushx},
    //     {"lpop", ATTR_WRITE, 2, &lpop},
    //     {"rpop", ATTR_WRITE, 2, &rpop},
    //     {"lindex", ATTR_READ, 3, &lindex},
    //     {"llen", ATTR_READ, 2, &llen},
    //     {"lset", ATTR_WRITE, 4, &lset},
    //     {"ltrim", ATTR_WRITE, 4, &ltrim},
    //     {"lrange", ATTR_READ, 4, &lrange},
    //     {"linsert", ATTR_WRITE, 5, &linsert},
    //     {"lrem", ATTR_WRITE, 4, &lrem},
    //     {"rpoplpush", ATTR_WRITE, 3, &rpoplpush},
    //     {"blpop", ATTR_WRITE, -3, &blpop},
    //     {"brpop", ATTR_WRITE, -3, &brpop},
    //     {"brpoplpush", ATTR_WRITE, 4, &brpoplpush},

    //     // hash
    //     {"hget", ATTR_READ, 3, &hget},
    //     {"hgetall", ATTR_READ, 2, &hgetall},
    //     {"hmget", ATTR_READ, -3, &hmget},
    //     {"hset", ATTR_WRITE, 4, &hset},
    //     {"hsetnx", ATTR_WRITE, 4, &hsetnx},
    //     {"hmset", ATTR_WRITE, -4, &hmset},
    //     {"hlen", ATTR_READ, 2, &hlen},
    //     {"hexists", ATTR_READ, 3, &hexists},
    //     {"hkeys", ATTR_READ, 2, &hkeys},
    //     {"hvals", ATTR_READ, 2, &hvals},
    //     {"hdel", ATTR_WRITE, -3, &hdel},
    //     {"hincrby", ATTR_WRITE, 4, &hincrby},
    //     {"hincrbyfloat", ATTR_WRITE, 4, &hincrbyfloat},
    //     {"hscan", ATTR_READ, -3, &hscan},
    //     {"hstrlen", ATTR_READ, 3, &hstrlen},

    //     // set
    //     {"sadd", ATTR_WRITE, -3, &sadd},
    //     {"scard", ATTR_READ, 2, &scard},
    //     {"sismember", ATTR_READ, 3, &sismember},
    //     {"srem", ATTR_WRITE, -3, &srem},
    //     {"smembers", ATTR_READ, 2, &smembers},
    //     {"sdiff", ATTR_READ, -2, &sdiff},
    //     {"sdiffstore", ATTR_WRITE, -3, &sdiffstore},
    //     {"sinter", ATTR_READ, -2, &sinter},
    //     {"sinterstore", ATTR_WRITE, -3, &sinterstore},
    //     {"sunion", ATTR_READ, -2, &sunion},
    //     {"sunionstore", ATTR_WRITE, -3, &sunionstore},
    //     {"smove", ATTR_WRITE, 4, &smove},
    //     {"spop", ATTR_WRITE, 2, &spop},
    //     {"srandmember", ATTR_READ, 2, &srandmember},
    //     {"sscan", ATTR_READ, -3, &sscan},

    //     //
    //     {"zadd", ATTR_WRITE, -4, &zadd},
    //     {"zcard", ATTR_READ, 2, &zcard},
    //     {"zrank", ATTR_READ, 3, &zrank},
    //     {"zrevrank", ATTR_READ, 3, &zrevrank},
    //     {"zrem", ATTR_WRITE, -3, &zrem},
    //     {"zincrby", ATTR_WRITE, 4, &zincrby},
    //     {"zscore", ATTR_READ, 3, &zscore},
    //     {"zrange", ATTR_READ, -4, &zrange},
    //     {"zrevrange", ATTR_READ, -4, &zrevrange},
    //     {"zrangebyscore", ATTR_READ, -4, &zrangebyscore},
    //     {"zrevrangebyscore", ATTR_READ, -4, &zrevrangebyscore},
    //     {"zremrangebyrank", ATTR_WRITE, 4, &zremrangebyrank},
    //     {"zremrangebyscore", ATTR_WRITE, 4, &zremrangebyscore},

    //     // pubsub
    //     {"subscribe", ATTR_READ, -2, &subscribe},
    //     {"unsubscribe", ATTR_READ, -1, &unsubscribe},
    //     {"publish", ATTR_READ, 3, &publish},
    //     {"psubscribe", ATTR_READ, -2, &psubscribe},
    //     {"punsubscribe", ATTR_READ, -1, &punsubscribe},
    //     {"pubsub", ATTR_READ, -2, &pubsub},

    //     // multi
    //     {"watch", ATTR_READ, -2, &watch},
    //     {"unwatch", ATTR_READ, 1, &unwatch},
    //     {"multi", ATTR_READ, 1, &multi},
    //     {"exec", ATTR_READ, 1, &exec},
    //     {"discard", ATTR_READ, 1, &discard},

    //     // replication
    //     {"sync", ATTR_READ, 1, &sync},
    //     {"psync", ATTR_READ, 1, &sync},
    //     {"slaveof", ATTR_READ, 3, &slaveof},
    //     {"replconf", ATTR_READ, -3, &replconf},

    //     // help
    //     {"cmdlist", ATTR_READ, 1, &cmdlist},
    // };

    void CommandTable::Init()
    {
        for (auto &command : commands_)
        {
            commands[command.cmd] = &command;
        }
    }

    bool RudisCommand::cheak_arg_num(size_t n) const
    {
        if (arg_num < 0)
        {
            if (n < -arg_num)
                return false;
        }
        else
        {
            if (n != arg_num)
                return false;
        }
        return true;
    }

    RuError CommandTable::execute_command(const vector<RString> params, ReplyBuffer &reply)
    {
        if (params.empty())
        {
            reply.reply_simple_error();
            return RuError_no_exist;
        }

        RString cmmd = params[0];
        std::transform(cmmd.begin(), cmmd.end(), cmmd.begin(), ::tolower);
        auto it(commands.find(cmmd));
        if (it == commands.end())
        {
            std::cout << "no this command" << std::endl;
            reply.reply_simple_error();
            return RuError_no_exist;
        }

        const RudisCommand *cmd = it->second;
        if (!cmd->cheak_arg_num(params.size()))
        {
            std::cout << "error arg nums" << std::endl;
            reply.reply_simple_error();
            return RuError_type;
        }

        return cmd->proc(params, reply);
    }
} // namespace rudis
