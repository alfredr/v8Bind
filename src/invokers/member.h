#ifndef V8BIND_INVOKER_MEMBER_H_
#define V8BIND_INVOKER_MEMBER_H_

#include "conversions.h"
#include "function_traits.h"
#include "except.h"

namespace v8Bind {
    
    template <typename MemberPtrType, unsigned ArgIndex, typename... Args>
    struct MemberInvoker;

    template <typename MemberPtrType, unsigned ArgIndex>
    struct MemberInvoker<MemberPtrType, ArgIndex> {

        typedef FunctionTraits<MemberPtrType> Traits;
        
        template <typename... CallingArgs>
        static typename Traits::ReturnType
        Invoke(typename Traits::ConstAwareClassType * p_that, MemberPtrType p_member,
                const v8::Arguments & v8args, CallingArgs... args) {

            return (p_that->*p_member)(args...);
        }
    };

    template <typename MemberPtrType,
                unsigned ArgIndex,
                typename Head, 
                typename... Tail>

    struct MemberInvoker<MemberPtrType, ArgIndex, Head, Tail...> {

        typedef FunctionTraits<MemberPtrType> Traits;

        template <typename... CallingArgs>
        static typename Traits::ReturnType
        Invoke(typename Traits::ConstAwareClassType * p_that, MemberPtrType p_member,
                const v8::Arguments & v8args, CallingArgs... args) {

            return MemberInvoker<MemberPtrType, ArgIndex+1, Tail...>::Invoke(
                    p_that, p_member, v8args, args..., FromV8<Head>(v8args[ArgIndex])
            );
        }
    };

    template <typename ReturnType>
    struct MemberInvokerAdapter {

        template <typename ClassType, typename... Args>
         static v8::Handle<v8::Value> Invoke(ClassType * p_that,
                ReturnType (ClassType::* p_member) (Args...), 
                const v8::Arguments & v8Args) {

            typedef ReturnType (ClassType::*MemberPtrType) (Args...);

            return ToV8<ReturnType>(
                MemberInvoker<MemberPtrType, 0, Args...>::
                    Invoke(p_that, p_member, v8Args)
            );
        }

        template <typename ClassType, typename... Args>
         static v8::Handle<v8::Value> Invoke(const ClassType * p_that,
                ReturnType (ClassType::* p_member) (Args...) const, 
                const v8::Arguments & v8Args) {

            typedef ReturnType (ClassType::*MemberPtrType) (Args...) const;

            return ToV8<ReturnType>(
                MemberInvoker<MemberPtrType, 0, Args...>::
                    Invoke(p_that, p_member, v8Args)
            );
        }
    };


    template <>
    struct MemberInvokerAdapter<void> {

        template <typename ClassType, typename... Args>
         static v8::Handle<v8::Value> Invoke(ClassType * p_that, 
                void (ClassType::* p_member) (Args...), 
                const v8::Arguments & v8Args) {
 
            typedef void (ClassType::*MemberPtrType) (Args...);
       
            MemberInvoker<MemberPtrType, 0, Args...>::
                Invoke(p_that, p_member, v8Args);

            return v8::Undefined();
        }

        template <typename ClassType, typename... Args>
         static v8::Handle<v8::Value> Invoke(const ClassType * p_that, 
                void (ClassType::* p_member) (Args...) const, 
                const v8::Arguments & v8Args) {
 
            typedef void (ClassType::*MemberPtrType) (Args...) const;
       
            MemberInvoker<MemberPtrType, 0, Args...>::
                Invoke(p_that, p_member, v8Args);

            return v8::Undefined();
        }
    };


    /*
     * member_invoker calls a native c++ function using v8::Arguments and returns
     * the result encapsulated as a value for v8.
     */

    template <typename ClassType, typename MemberPtrType> 
     static v8::Handle<v8::Value> member_invoker(ClassType * p_that,
            MemberPtrType p_member, const v8::Arguments & v8args) {

        typedef typename FunctionTraits<MemberPtrType>::ReturnType ReturnType;

        if(v8args.Length() != FunctionTraits<MemberPtrType>::ArgCount)
            throw ArgumentCountException();

        return MemberInvokerAdapter<ReturnType>::Invoke(p_that, p_member, v8args);
    }

} // namespace v8Bind

#endif
