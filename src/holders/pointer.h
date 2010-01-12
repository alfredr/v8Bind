#ifndef V8BIND_HOLDER_POINTER_H_
#define V8BIND_HOLDER_POINTER_H_

#include <type_traits>

#include "holder.h"
#include "function_stub.h"
#include "strip_qualifiers.h"

namespace v8Bind {

    template <typename T>
    struct Holder<T *> : IHolder {
        virtual ~Holder();
        inline Holder(T * p_value);
        
        inline virtual bool is_a(const std::type_info & type) const;
        inline virtual bool is_const(void) const;
        inline virtual const std::string & get_name(void) const;
        void * get_raw(void);

        inline virtual void claim_ownership(void);

        protected:
        T * _p_value;
        bool _const;
        bool _owner;
    };

    template <typename T>
    Holder<T*>::~Holder() { 
        if(_owner)
            delete _p_value;            
    };

    template <typename T>
    inline Holder<T*>::Holder(T * p_value) 
        : _p_value(p_value), _const(std::is_const<T>::value), _owner(false) { }

    template <typename T>
    inline bool Holder<T*>::is_const(void) const {
        return _const;
    }

    template <typename T>
    inline bool Holder<T*>::is_a(const std::type_info & type) const {
        return FunctionStub<T>::Get::GetTypeinfo()->in_chain(type);
    }

    template <typename T>
    inline const std::string & Holder<T*>::get_name(void) const {
        return FunctionStub<T>::Get::GetName();
    }

    template <typename T>
    inline void * Holder<T*>::get_raw(void) {
        return (void *) _p_value;
    }

    template <typename T>
    inline void Holder<T*>::claim_ownership(void) {
        _owner = true;
    }


} // namespace v8Bind;


#endif
