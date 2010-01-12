#ifndef V8BIND_CONVERTER_H_
#define V8BIND_CONVERTER_H_

#include <v8.h>

namespace v8Bind {

    //TODO: potentially type-check arguments for value types

    template <typename T>
    struct Converter;

    template <typename T>
    inline v8::Handle<v8::Value> ToV8(T value) {
        return Converter<T>::ToV8(value);
    }

    template <typename T>
    inline T FromV8(v8::Handle<v8::Value> value) {
        return Converter<T>::FromV8(value);
    }

} // namespace v8Bind

#endif
