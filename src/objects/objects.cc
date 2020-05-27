#include "object.h"
#include <time.h>
#include <iostream>
namespace rudis
{
    uint32_t RObject::lruclock = static_cast<uint32_t>(::time(nullptr));

    RObject::RObject(Type t) : type(t), lru(0), value(nullptr)
    {
        switch (type)
        {
        case R_STRING:
            encoding = R_ENCODING_RAW;
            break;
        case R_LIST:
            encoding = R_ENCODING_LIST;
            break;
        case R_HASH:
            encoding = R_ENCODING_HASH;
            break;
        case R_SET:
            encoding = R_ENCODING_SET;
            break;
        case R_SSET:
            encoding = R_ENCODING_SSET;
            break;
        case R_INVALID:
            encoding = R_ENCODING_INVALID;
            break;
        default:
            encoding = R_ENCODING_INVALID;
            break;
        }
    }

    RObject::~RObject()
    {
        _FreeValue();
    }

    void RObject::Clear()
    {
        _FreeValue();

        type = R_INVALID;
        encoding = R_ENCODING_INVALID;
        lru = 0;
        value = nullptr;
    }

    void RObject::Reset(void *newvalue)
    {
        _FreeValue();
        value = newvalue;
    }

    RObject::RObject(RObject &&obj)
    {
        _MoveFrom(std::move(obj));
    }

    RObject &RObject::operator=(RObject &&obj)
    {
        _MoveFrom(std::move(obj));
        return *this;
    }

    void RObject::_MoveFrom(RObject &&obj)
    {
        this->Reset();

        this->encoding = obj.encoding;
        this->type = obj.type;
        this->value = obj.value;
        this->lru = obj.lru;

        obj.encoding = R_ENCODING_INVALID;
        obj.type = R_INVALID;
        obj.value = nullptr;
        obj.lru = 0;
    }

    void RObject::_FreeValue()
    {
        switch (encoding)
        {
        case R_ENCODING_RAW:
            delete CastString();
            break;

        case R_ENCODING_LIST:
            delete CastList();
            break;

        case R_ENCODING_SET:
            delete CastSet();
            break;

        case R_ENCODING_SSET:
            delete CastSortedSet();
            break;

        case R_ENCODING_HASH:
            delete CastHash();
            break;

        default:
            return;
        }
    }

    RObject RObject::CreateString(const RString &value)
    {
        RObject obj(R_STRING);
        obj.value = new RString(value);
        return obj;
    }

    RObject RObject::CreateString(long value)
    {
        return CreateString(std::to_string(value));
    }

    RObject RObject::CreateList()
    {
        RObject obj(R_LIST);
        obj.value = new RList;
        return obj;
    }

    RObject RObject::CreateSet()
    {
        RObject obj(R_SET);
        obj.value = new RSet;
        return obj;
    }

    RObject RObject::CreateSSet()
    {
        RObject obj(R_SSET);
        obj.value = new RSortedSet;
        return obj;
    }

    RObject RObject::CreateHash()
    {
        RObject obj(R_HASH);
        obj.value = new RDict<RString>;
        return obj;
    }

} // namespace rudis