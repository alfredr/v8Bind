#ifndef V8BIND_CONVERTER_UNSIGNED_INT_H_
#define V8BIND_CONVERTER_UNSIGNED_INT_H_

#include <v8.h>
#include "converter.h"

namespace v8Bind {

    template <>
    struct Converter<unsigned int> {
        static inline v8::Handle<v8::Value> ToV8 (unsigned int value) {
            return v8::Number::New(value);
        }

        static inline unsigned int FromV8(v8::Handle<v8::Value> HValue) {
            return HValue->Uint32Value();
        }
    };

} //namespace v8Bind

#endif
