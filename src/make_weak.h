#ifndef V8BIND_MAKE_WEAK_H_
#define V8BIND_MAKE_WEAK_H_

namespace v8Bind {

    template <typename T>
    void weak_cleanup(v8::Persistent<v8::Value>, void *p) {
        if(T * ptr = static_cast<T*>(p))
            delete ptr;
    }

    template <typename T>
    inline v8::Persistent<v8::External> make_weak(T* p) {
        v8::Persistent<v8::External> HExt (
            v8::Persistent<v8::External>::New (
                v8::External::New(p)
            )
        );

        HExt.MakeWeak(p, weak_cleanup<T>);

        return HExt;
    }

} // v8Bind

#endif
