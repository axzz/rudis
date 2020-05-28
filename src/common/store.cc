#include "store.h"
#include <utility>
namespace rudis
{
  Store &Store::Instance()
  {
    static Store store;
    return store;
  }

  // TODO: expire库初始化 blockclient初始化
  void Store::Init(int dbNum)
  {
    if (dbNum < 1)
    {
      dbNum = 1;
    }
    else if (dbNum > max_db_num)
    {
      dbNum = max_db_num;
    }
    dbs.resize(dbNum);
  }

  int Store::SelectDB(int dbNo)
  {
    if (dbNo >= 0 and dbNo < static_cast<int>(dbs.size()))
    {
      int old = dbno;
      dbno = dbNo;
      return old;
    }
    return -1;
  }

  int Store::GetDB() const
  {
    return dbno;
  }

  bool Store::DeleteItem(const RString &key)
  {
    auto &db = dbs[dbno];
    // TODO: dirty delete things
    return db.erase(key) != 0;
  }

  bool Store::ExistsKey(const RString &key) const
  {
    const RObject *obj = GetObject(key);
    return obj != nullptr;
  }

  Type Store::GetType(const RString &key) const
  {
    const RObject *obj = GetObject(key);
    if (!obj)
      return R_INVALID;
    return obj->type;
  }

  size_t Store::DBSize() const
  {
    return dbs[dbno].size();
  }

  const RObject *Store::GetObject(const RString &key) const
  {
    auto &db = dbs[dbno];
    auto it(db.find(key));
    if (it != db.end())
    {
      return &(it->second);
    }
    // TODO: dirty things
    return nullptr;
  };

  // 一下touch指代是否更新lru（用户使用则更新）
  RuError Store::GetValue(const RString &key, RObject *&value, bool touch)
  {
    return GetValueByType(key, value, R_INVALID, touch);
  }

  RuError Store::GetValueByType(const RString &key, RObject *&value, Type type, bool touch)
  {
    //TODO: expire
    auto obj = GetObject(key);
    if (obj)
    {
      if (type != R_INVALID and type != obj->type)
      {
        return RuError_type;
      }
      else
      {
        value = const_cast<RObject *>(obj);
        if (touch)
        {
          //TODO: touch
        }
        return RuError_ok;
      }
    }
    else
    {
      return RuError_no_exist;
    }
    return RuError_ok;
  };

  const RObject* Store::SetValue(const RString &key, RObject &&value)
  {
    auto& db = dbs[dbno];
    RObject& obj = db[key] = std::move(value);
    obj.lru = RObject::lruclock;
    //dirty
    return &obj;
  };

  void Store::ResetDb(){
    std::vector<DB>(dbs.size()).swap(dbs);// 临时变量会被销毁
    //TODO: other dbs
    dbno=0; 
  }
} // namespace rudis