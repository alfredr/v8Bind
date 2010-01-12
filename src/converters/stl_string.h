#ifndef V8BIND_CONVERTER_STRING_H_
#define V8BIND_CONVERTER_STRING_H_

#include <v8.h>
#include <string>
#include "converter.h"

namespace v8Bind {

    template <>
    struct Converter<std::string> {
        static inline v8::Handle<v8::Value> ToV8 (const std::string & value) {
            return v8::String::New(value.c_str());
        }

        static inline std::string FromV8(v8::Handle<v8::Value> HValue) {
            return std::string(*v8::String::Utf8Value(HValue));
        }
    };

} //namespace v8Bind

#endif
