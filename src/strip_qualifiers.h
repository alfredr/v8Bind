#ifndef V8BIND_STRIP_QUALIFIERS_H_
#define V8BIND_STRIP_QUALIFIERS_H_

namespace v8Bind {

    template <typename T>
    struct StripQualifiers {
        typedef T Type;
    };

    template <typename T>
    struct StripQualifiers<T *> {
        typedef typename StripQualifiers<T>::Type Type;
    };

    template <typename T>
    struct StripQualifiers<T const> {
        typedef typename StripQualifiers<T>::Type Type;
    };

    template <typename T>
    struct StripQualifiers<T &> {
        typedef typename StripQualifiers<T>::Type Type;
    };

    template <typename T>
    struct StripQualifiers<T volatile> {
        typedef typename StripQualifiers<T>::Type Type;
    };


} // namespace v8Bind

#endif

