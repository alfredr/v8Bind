#ifndef V8BIND_INVOKER_FUNCTION_H_
#define V8BIND_INVOKER_FUNCTION_H_

#include "conversions.h"
#include "function_traits.h"

namespace v8Bind {
    
    template <typename FunctionType, typename... Args>
    struct FunctionInvoker;

    template <typename FunctionType>
    struct FunctionInvoker<FunctionType> {
        typedef typename FunctionTraits<FunctionType>::ReturnType ReturnType;

        template <typename... CallingArgs>
        inline static ReturnType Invoke(FunctionType f,
                const v8::Arguments &v8args, unsigned n, CallingArgs... args) {

            return (f)(args...);
        }
    };

    template <typename FunctionType, typename Head, typename... Tail>
    struct FunctionInvoker<FunctionType, Head, Tail...> {
        typedef typename FunctionTraits<FunctionType>::ReturnType ReturnType;

        template <typename... CallingArgs> inline static
        ReturnType Invoke(FunctionType f, const v8::Arguments &v8args, 
                unsigned n, CallingArgs... args) {

            return FunctionInvoker<FunctionType, Tail...>::
                Invoke(f, v8args, n+1, args..., FromV8<Head>(v8args[n]));
        }
    };

    /*
     * The specialization of FunctionInvokerAdapter handles the case where the
     * function wishes to return void. There doesn't seem to be a 
     * cleaner way.
     */

    template <typename ReturnType>
    struct FunctionInvokerAdapter {
        template <typename... Args> inline static
        v8::Handle<v8::Value> Invoke(ReturnType (&f) (Args...), 
                const v8::Arguments & v8args) {

            typedef ReturnType (&FunctionType) (Args...);

            return ToV8<ReturnType>(
                FunctionInvoker<FunctionType, Args...>::Invoke(f, v8args, 0)
            );
        }
    };
 
    template < >
    struct FunctionInvokerAdapter<void> {
        template <typename... Args> inline static
        v8::Handle<v8::Value> Invoke(void (&f) (Args...), 
                const v8::Arguments & v8args) {
            
            typedef void (&FunctionType) (Args...);

            FunctionInvoker<FunctionType, Args...>::Invoke(f, v8args, 0);
            return v8::Undefined();
        }
    };
 
    /*
     * function_invoker calls a native c++ function using v8::Arguments and returns
     * the result encapsulated as a value for v8.
     */

    template <typename ReturnType, typename... Args> inline static
    v8::Handle<v8::Value> function_invoker(ReturnType (&f) (Args...), 
            const v8::Arguments & v8args) {

        typedef ReturnType (&FunctionType) (Args...);

        if(v8args.Length() != FunctionTraits<FunctionType>::ArgCount)
            throw ArgumentCountException();

        return FunctionInvokerAdapter<ReturnType>::Invoke(f, v8args);
    }

} // namespace v8Bind

#endif
