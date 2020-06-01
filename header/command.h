#pragma once

#include "object.h"
#include <vector>
#include "buffer.h"
using std::vector;

namespace rudis
{
  using RuCommandHandler = RuError(const vector<RString> &params, ReplyBuffer &reply);

  // 所有命令申明
  // key commands
  RuCommandHandler command;
  RuCommandHandler type;
  RuCommandHandler exists;
  RuCommandHandler del;
  RuCommandHandler expire;
  RuCommandHandler pexpire;
  RuCommandHandler expireat;
  RuCommandHandler pexpireat;
  RuCommandHandler ttl;
  RuCommandHandler pttl;
  RuCommandHandler persist;
  RuCommandHandler move;
  RuCommandHandler keys;
  RuCommandHandler randomkey;
  RuCommandHandler rename;
  RuCommandHandler renamenx;
  RuCommandHandler scan;
  RuCommandHandler sort;
  RuCommandHandler dump;
  RuCommandHandler restore;
  RuCommandHandler migrate;

  // server commands
  RuCommandHandler select;
  RuCommandHandler dbsize;
  RuCommandHandler bgsave;
  RuCommandHandler save;
  RuCommandHandler lastsave;
  RuCommandHandler flushdb;
  RuCommandHandler flushall;
  RuCommandHandler client;
  RuCommandHandler debug;
  RuCommandHandler shutdown;
  RuCommandHandler bgrewriteaof;
  RuCommandHandler ping;
  RuCommandHandler echo;
  RuCommandHandler info;
  RuCommandHandler monitor;
  RuCommandHandler auth;
  RuCommandHandler slowlog;
  RuCommandHandler config;

  // string commands
  RuCommandHandler set;
  RuCommandHandler get;
  RuCommandHandler getrange;
  RuCommandHandler setrange;
  RuCommandHandler getset;
  RuCommandHandler append;
  RuCommandHandler bitcount;
  RuCommandHandler bitop;
  RuCommandHandler getbit;
  RuCommandHandler setbit;
  RuCommandHandler incr;
  RuCommandHandler incrby;
  RuCommandHandler incrbyfloat;
  RuCommandHandler decr;
  RuCommandHandler decrby;
  RuCommandHandler mget;
  RuCommandHandler mset;
  RuCommandHandler msetnx;
  RuCommandHandler setnx;
  RuCommandHandler setex;
  RuCommandHandler psetex;
  RuCommandHandler strlen;

  // list commands
  RuCommandHandler lpush;
  RuCommandHandler rpush;
  RuCommandHandler lpushx;
  RuCommandHandler rpushx;
  RuCommandHandler lpop;
  RuCommandHandler rpop;
  RuCommandHandler lindex;
  RuCommandHandler llen;
  RuCommandHandler lset;
  RuCommandHandler ltrim;
  RuCommandHandler lrange;
  RuCommandHandler linsert;
  RuCommandHandler lrem;
  RuCommandHandler rpoplpush;
  RuCommandHandler blpop;
  RuCommandHandler brpop;
  RuCommandHandler brpoplpush;

  // hash commands
  RuCommandHandler hget;
  RuCommandHandler hmget;
  RuCommandHandler hgetall;
  RuCommandHandler hset;
  RuCommandHandler hsetnx;
  RuCommandHandler hmset;
  RuCommandHandler hlen;
  RuCommandHandler hexists;
  RuCommandHandler hkeys;
  RuCommandHandler hvals;
  RuCommandHandler hdel;
  RuCommandHandler hincrby;
  RuCommandHandler hincrbyfloat;
  RuCommandHandler hscan;
  RuCommandHandler hstrlen;

  // set commands
  RuCommandHandler sadd;
  RuCommandHandler scard;
  RuCommandHandler srem;
  RuCommandHandler sismember;
  RuCommandHandler smembers;
  RuCommandHandler sdiff;
  RuCommandHandler sdiffstore;
  RuCommandHandler sinter;
  RuCommandHandler sinterstore;
  RuCommandHandler sunion;
  RuCommandHandler sunionstore;
  RuCommandHandler smove;
  RuCommandHandler spop;
  RuCommandHandler srandmember;
  RuCommandHandler sscan;

  // sset
  RuCommandHandler zadd;
  RuCommandHandler zcard;
  RuCommandHandler zrank;
  RuCommandHandler zrevrank;
  RuCommandHandler zrem;
  RuCommandHandler zincrby;
  RuCommandHandler zscore;
  RuCommandHandler zrange;
  RuCommandHandler zrevrange;
  RuCommandHandler zrangebyscore;
  RuCommandHandler zrevrangebyscore;
  RuCommandHandler zremrangebyrank;
  RuCommandHandler zremrangebyscore;

  // pubsub
  RuCommandHandler subscribe;
  RuCommandHandler unsubscribe;
  RuCommandHandler publish;
  RuCommandHandler psubscribe;
  RuCommandHandler punsubscribe;
  RuCommandHandler pubsub;

  //multi
  RuCommandHandler watch;
  RuCommandHandler unwatch;
  RuCommandHandler multi;
  RuCommandHandler exec;
  RuCommandHandler discard;

  // replication
  RuCommandHandler sync;
  RuCommandHandler slaveof;
  RuCommandHandler replconf;

  // modules
  RuCommandHandler module;

  // help
  RuCommandHandler cmdlist;

  enum COMMAND_FLAG
  {
    ATTR_READ,
    ATTR_WRITE
  };

  struct RudisCommand
  {
    RString cmd;
    COMMAND_FLAG flag; // 读或写
    int arg_num;       // 至少的arg数量
    RuCommandHandler *proc;
    bool cheak_arg_num(size_t n) const;
    /*
    原实现中有calls milliseconds表示命令总共次数与时间
  */
  };

  class CommandTable
  {
  private:
    //这个数组存在的意义是 dict无法直接容易地被初始化
    static RudisCommand commands_[];
    RDict<const RudisCommand *> commands;
    CommandTable() { Init(); };

  public:
    void Init();
    static CommandTable &Instance()
    {
      static CommandTable command_table;
      return command_table;
    }
    RuError execute_command(const vector<RString> command, ReplyBuffer &reply);
  };

#define COMMAND CommandTable::Instance()
} // namespace rudis