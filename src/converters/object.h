#ifndef V8BIND_CONVERTER_OBJECT_H_
#define V8BIND_CONVERTER_OBJECT_H_

#include <v8.h>
#include "converter.h"
#include "function_stub.h"
#include "holder.h"

namespace v8Bind {

    /*
     * This converter is for passing classes and structures by value.
     * T is assumed to be a const qualified class, pointer-to-class, or 
     * reference-to-class type.
     */

    //TODO: Guard against T being other types
    template <class T>
    struct Converter {

        static inline v8::Handle<v8::Object> ToV8 (T value) {
            v8::Handle<v8::Object> HInstance (
                FunctionStub<T>::Get::CloneArchetype()
            );

            IHolder::StoreValueInObject<T>(HInstance, value);

            return HInstance;
        }

        static inline T FromV8(v8::Handle<v8::Value> HValue) {
            return IHolder::GetValueFromObject<T>(HValue);
        }
    };

} //namespace v8Bind

#endif
