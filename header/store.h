#pragma once
#include "object.h"
#include <vector>
namespace rudis
{
    const int max_db_num = 10000;
    using DB = RDict<RObject>;
    class Store
    {
    public:
        static Store &Instance();
        //不可复制
        Store(const Store &) = delete;
        void operator=(const Store &) = delete;

        void Init(int dbNum = 16);

        int SelectDB(int dbNo);
        int GetDB() const;

        bool DeleteItem(const RString &key);
        bool ExistsKey(const RString &key) const;
        Type GetType(const RString &key) const;

        //这个干啥用的? 随机获得一个key，并将val的地址填进去
        // TODO: 实现
        RString RandomKey(RObject **val = nullptr) const;

        size_t DBSize() const;

        //满足scan/hscan等功能，进行迭代，查找cursor之后count个数据放入res中,返回新cursor
        //TODO: 实现
        size_t Scan(size_t cursor, size_t count, std::vector<RString> &res) const;

        DB::const_iterator begin() const { return dbs[dbno].begin(); };
        DB::const_iterator end() const { return dbs[dbno].end(); };
        DB::iterator begin() { return dbs[dbno].begin(); };
        DB::iterator end() { return dbs[dbno].end(); };

        const RObject *GetObject(const RString &key) const;
        RuError GetValue(const RString &key, RObject *&value, bool touch = true);
        RuError GetValueByType(const RString &key, RObject *&value, Type type = R_INVALID, bool touch = true);

        const RObject *SetValue(const RString &key, RObject &&value);

        void ClearCurrentDB() { dbs[dbno].clear(); }
        void ResetDb();

        // TODO: expire相关命令还有定时命令InitEvictionTimer

        // TODO: blocking相关命令 等待直到有值再返回

        // TODO: 多机和持久化会用到dirty相关 注意在private和namespace还没实现

    private:
        Store() : dbno(0) { Init(); };
        mutable std::vector<DB> dbs;
        int dbno;
    };

#define STORE Store::Instance()

} // namespace rudis