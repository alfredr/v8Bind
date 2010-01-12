#ifndef V8BIND_HOLDER_H_
#define V8BIND_HOLDER_H_

#include <v8.h>
#include <typeinfo>

#include "except.h"
#include "make_weak.h"

namespace v8Bind {

    /*
     * Holder is declared here but defined in the files
     * included from holders/
     */

    template <typename T>
    struct Holder;

    /*
     * Each Holder implements the IHolder interface
     * as declared below.
     */

    struct IHolder {
        template <typename T>
        static inline T ValueCast(IHolder & iholder);

        template <typename T>
        static inline T* PointerCast(IHolder & iholder);

        template <typename T>
        static inline T& ReferenceCast(IHolder & iholder);

        template <typename T>
        static inline T Cast(IHolder & iholder);

        template <typename T>
        static inline T GetValueFromObject(v8::Handle<v8::Value>);

        template <typename T>
        static inline void StoreValueInObject(v8::Handle<v8::Object>, T value);

        static inline IHolder * GetFromObject(v8::Handle<v8::Value>);
        static inline void StoreInObject(v8::Handle<v8::Object>, IHolder *);

        virtual bool is_a(const std::type_info & type) const = 0;
        virtual bool is_const(void) const = 0;
        virtual const std::string & get_name(void) const = 0;
        virtual void * get_raw(void) = 0;

        virtual void claim_ownership(void) = 0;
        virtual ~IHolder(void) = 0;
    };

    IHolder::~IHolder() { }

    template <typename T>
    inline bool IsA(const IHolder & p) {
        return p.is_a(typeid(T));
    }
 
    template <typename T>
    inline bool IsA(const IHolder * p) {
        return p->is_a(typeid(T));
    }
 
    //TODO: Guard against references and pointers 
    template <typename T>
    T IHolder::ValueCast(IHolder & iholder) {
        if(!IsA<T>(iholder))
            throw TypeCastFailureException();

        return T(*static_cast<T*>(iholder.get_raw()));
    }

    template <typename T>
    T* IHolder::PointerCast(IHolder & iholder) {
        if(!IsA<T>(iholder))
            throw TypeCastFailureException();

        if(!std::is_const<T>::value)
            if(iholder.is_const())
                throw ConstCastFailureException();

        return static_cast<T*>(iholder.get_raw());
    }

    template <typename T>
    T& IHolder::ReferenceCast(IHolder & iholder) {
        if(!IsA<T>(iholder))
            throw TypeCastFailureException();

        if(!std::is_const<T>::value)
            if(iholder.is_const())
                throw ConstCastFailureException();

        return *static_cast<T*>(iholder.get_raw());
    }

    //TODO: GUARD - T must be a class
    template <typename T>
    struct _CastHelper {
        static inline T Cast(IHolder & iholder) {
            return IHolder::ValueCast<T>(iholder);
        }
    };

    template <typename T>
    struct _CastHelper<T*> {
        static inline T* Cast(IHolder & iholder) {
            return IHolder::PointerCast<T>(iholder);
        }
    };

    template <typename T>
    struct _CastHelper<T&> {
        static inline T& Cast(IHolder & iholder) {
            return IHolder::ReferenceCast<T>(iholder);
        }
    };

    template <typename T>
    T IHolder::Cast(IHolder & iholder) {
        return _CastHelper<T>::Cast(iholder);
    }

    IHolder * IHolder::GetFromObject(v8::Handle<v8::Value> HValue) {
        if(!HValue->IsObject())
            throw TypeCastFailureException();

        v8::Handle<v8::Object> HObject (
            v8::Handle<v8::Object>::Cast(HValue)
        );

        if(HObject->InternalFieldCount() != FIELDCOUNT)
            throw NullReferenceException();

        IHolder * p_holder = static_cast<IHolder*>(
            v8::External::Unwrap(HObject->GetInternalField(0))
        );

        if(!p_holder)
            throw NullReferenceException();

        return p_holder;
    }

    void IHolder::StoreInObject(v8::Handle<v8::Object> HObject, IHolder * p) {
        HObject->SetInternalField(0, make_weak(p));
    }
 
    template <typename T>
    T IHolder::GetValueFromObject(v8::Handle<v8::Value> HValue) {
        return IHolder::Cast<T>(*IHolder::GetFromObject(HValue));
    }

    template <typename T>
    void IHolder::StoreValueInObject(v8::Handle<v8::Object> HObject, T value) {
        IHolder::StoreInObject(HObject, new Holder<T>(value));
    }
 
} // namespace v8Bind;

#endif

#include "holders/value.h"
#include "holders/pointer.h"
#include "holders/reference.h"


