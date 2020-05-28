#pragma once
#include <list>
#include <unordered_map>
#include <map>
#include <deque>
#include <set>
#include <unordered_set>
#include <string>
/*
	简单字符串 => std::string
	链表 => std::list
	字典 => std::unordered_map
	跳跃表 => 红黑树 => std::map
	整数集合 => std::set<int>
    集合对象实现原来用hash_map封装=>采用unordered_set直接封装
*/
namespace rudis
{
    using RString = std::string;

    using RList = std::list<RString>;

    template <class T>
    using RDict = std::unordered_map<RString, T>;

    template <class T1, class T2>
    using Rskipmap = std::map<T1, T2>;

    using RIntSet = std::set<int>;

    using RSet = std::unordered_set<RString>;

    enum Type
    {
        R_STRING,
        R_LIST,
        R_HASH,
        R_SET,
        R_SSET,
        R_INVALID
    };
    enum Encoding
    {
        R_ENCODING_INT,
        R_ENCODING_RAW,
        R_ENCODING_HASH,
        R_ENCODING_LIST,
        R_ENCODING_SET,
        R_ENCODING_SSET,
        R_ENCODING_TREE,
        R_ENCODING_INVALID
    };

    enum RuError
    {
        RuError_ok,
        RuError_no_exist,
        RuError_type
    };

    class RSortedSet
    {
        // TODO: sset
    };

    using PSTRING = RString *;
    using PLIST = RList *;
    using PSET = RSet *;
    using PINTSET = RIntSet *;
    using PSSET = RSortedSet *;
    using PDICT = RDict<RString> *;

    class RObject
    {
    public:
        static uint32_t lruclock;
        Type type;
        Encoding encoding;
        unsigned long long lru;

        void *value;

        explicit RObject(Type t = R_INVALID);
        ~RObject();

        RObject(const RObject &obj) = delete;
        RObject &operator=(const RObject &obj) = delete;

        RObject(RObject &&obj);
        RObject &operator=(RObject &&obj);

        void Clear();
        void Reset(void *newvalue = nullptr);

        static RObject CreateString(const RString &value);
        static RObject CreateString(long value);
        static RObject CreateList();
        static RObject CreateSet();
        static RObject CreateSSet();
        static RObject CreateHash();

        PSTRING CastString() const { return reinterpret_cast<PSTRING>(value); }
        PLIST CastList() const { return reinterpret_cast<PLIST>(value); }
        PSET CastSet() const { return reinterpret_cast<PSET>(value); }
        PSSET CastSortedSet() const { return reinterpret_cast<PSSET>(value); }
        PDICT CastHash() const { return reinterpret_cast<PDICT>(value); }

    private:
        void _MoveFrom(RObject &&obj);
        void _FreeValue();
    };
} // namespace rudis