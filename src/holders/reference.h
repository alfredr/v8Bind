#ifndef V8BIND_HOLDER_REFERENCE_H_
#define V8BIND_HOLDER_REFERENCE_H_

#include <type_traits>

#include "holder.h"
#include "function_stub.h"

namespace v8Bind {

    template <typename T>
    struct Holder<T&> : IHolder {
        virtual ~Holder();
        inline Holder(T & value);
        
        inline virtual bool is_a(const std::type_info & type) const;
        inline virtual bool is_const(void) const;
        inline virtual const std::string & get_name(void) const;
        void * get_raw(void);

        inline virtual void claim_ownership(void);

        protected:
        T & _value;
        bool _const;
    };

    template <typename T>
    Holder<T&>::~Holder() { };

    template <typename T>
    inline Holder<T&>::Holder(T & value) 
        : _value(value), _const(std::is_const<T>::value) { }

    template <typename T>
    inline bool Holder<T&>::is_const(void) const {
        return _const;
    }

    template <typename T>
    inline bool Holder<T&>::is_a(const std::type_info & type) const {
        return FunctionStub<T>::Get::GetTypeinfo()->in_chain(type);
    }

    template <typename T>
    inline const std::string & Holder<T&>::get_name(void) const {
        return FunctionStub<T>::Get::GetName();
    }

    template <typename T>
    inline void * Holder<T&>::get_raw(void) {
        return (void *) &_value;
    }

    template <typename T>
    inline void Holder<T&>::claim_ownership(void) {
        throw InvalidOperationException();
    }


} // namespace v8Bind

#endif
