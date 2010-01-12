#ifndef V8BIND_FUNCTION_TRAITS_H_
#define V8BIND_FUNCTION_TRAITS_H_

namespace v8Bind {

    template <typename FunctionType>
    struct FunctionTraits;
    
    template <typename R, typename C, typename... Args>
    struct FunctionTraits<R (C::*) (Args...)> {
        typedef R ReturnType;
        typedef C ClassType;
        typedef C ConstAwareClassType;
 
        typedef R (C::*AsNonConst) (Args...);
        typedef R (C::*AsConst) (Args...) const;

        static const bool Const = false;
        static const unsigned ArgCount = sizeof...(Args);
    };

    template <typename R, typename C, typename... Args>
    struct FunctionTraits<R (C::*) (Args...) const> {
        typedef R ReturnType;
        typedef C ClassType;
        typedef C const ConstAwareClassType;

        typedef R (C::*NonConst) (Args...);
        typedef R (C::*AsConst) (Args...) const;

        static const bool Const = true;
        static const unsigned ArgCount = sizeof...(Args);
    };

    template <typename R, typename... Args>
    struct FunctionTraits<R (&) (Args...)> {
        typedef R ReturnType;
        static const unsigned ArgCount = sizeof...(Args);
    };


} // namespace v8Bind

#endif
