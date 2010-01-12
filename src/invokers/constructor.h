#ifndef V8BIND_INVOKER_CONSTRUCTOR_H_
#define V8BIND_INVOKER_CONSTRUCTOR_H_

#include "conversions.h"
#include "invokers/function.h"

namespace v8Bind {

    template <typename ClassType, typename... Args>
    struct ConstructorInvoker {
        inline static ClassType * Invoke(Args... args) {
            return new ClassType(args...);
        }
    };

    template <typename ClassType, typename... Args>
    v8::Handle<v8::Object> constructor_invoke(const v8::Arguments & v8args) {
        typedef ClassType * (&FunctionType) (Args...);

        if(v8args.Length() != FunctionTraits<FunctionType>::ArgCount)
            throw ArgumentCountException();

        ClassType * p_obj =
            FunctionInvoker<FunctionType, Args...>::Invoke (
                ConstructorInvoker<ClassType, Args...>::Invoke, 
                v8args, 0
            );

        IHolder * p_holder = new Holder<ClassType *>(p_obj);
        p_holder->claim_ownership();

        IHolder::StoreInObject(v8args.Holder(), p_holder);

        return v8args.Holder();
    }

} // namespace v8Bind

#endif
