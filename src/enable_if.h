#ifndef V8BIND_ENABLE_IF_H_
#define V8BIND_ENABLE_IF_H_

namespace v8Bind {

    template <typename T, bool condition>
    struct EnableIf;

    template <typename T>
    struct EnableIf<T, true> {
        typedef T Type; 
    };

}

#endif
