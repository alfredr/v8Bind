#ifndef V8BIND_CONVERTER_INT_H_
#define V8BIND_CONVERTER_INT_H_

#include <v8.h>
#include "converter.h"

namespace v8Bind {

    template <>
    struct Converter<int> {
        static inline v8::Handle<v8::Value> ToV8 (int value) {
            return v8::Number::New(value);
        }

        static inline int FromV8(v8::Handle<v8::Value> HValue) {
            return HValue->Int32Value();
        }
    };

} //namespace v8Bind

#endif
