#ifndef V8BIND_CONVERTER_FLOAT_H_
#define V8BIND_CONVERTER_FLOAT_H_

#include <v8.h>
#include "converter.h"

namespace v8Bind {

    template <>
    struct Converter<float> {
        static inline v8::Handle<v8::Value> ToV8 (float value) {
            return v8::Number::New(value);
        }

        static inline float FromV8(v8::Handle<v8::Value> HValue) {
            return HValue->NumberValue();
        }
    };

} //namespace v8Bind

#endif
