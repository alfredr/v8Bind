#ifndef V8BIND_EXPORT_HELPERS_H_
#define V8BIND_EXPORT_HELPERS_H_

#include <v8.h>
#include "function_stub.h"

namespace v8Bind {

    struct TFunction {
        template <typename ObjectType>
        static inline v8::Handle<v8::FunctionTemplate> Get(void) {
            return FunctionStub<ObjectType>::Get::
                GetTemplate();
        }
    };

    struct TPrototype {
        template <typename ObjectType>
        static inline v8::Handle<v8::ObjectTemplate> Get(void) {
            return FunctionStub<ObjectType>::Get::
                GetTemplate()->PrototypeTemplate();
        }
    };

    struct TInstance {
        template <typename ObjectType>
        static inline v8::Handle<v8::ObjectTemplate> Get(void) {
            return FunctionStub<ObjectType>::Get::
                GetTemplate()->InstanceTemplate();
        }
    };

} // namespace v8Bind;

#endif
