#ifndef V8BIND_CONVERTER_BOOL_H_
#define V8BIND_CONVERTER_BOOL_H_

#include <v8.h>
#include "converter.h"

namespace v8Bind {

    template <>
    struct Converter<bool> {
        static inline v8::Handle<v8::Value> ToV8 (bool value) {
            return v8::Boolean::New(value);
        }

        static inline bool FromV8(v8::Handle<v8::Value> HValue) {
            return HValue->BooleanValue();
        }
    };

} //namespace v8Bind

#endif
