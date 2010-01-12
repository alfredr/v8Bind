#ifndef V8BIND_HOOK_CONSTRUCTOR_H_
#define V8BIND_HOOK_CONSTRUCTOR_H_

#include <v8.h>

#include "invokers/constructor.h"
#include <stdexcept>

namespace v8Bind {

    template <typename ClassType, typename... Args>
    struct Constructor {
        inline static v8::Handle<v8::Value> Hook(const v8::Arguments & v8args) {
            if(!v8args.IsConstructCall())
                return v8::Undefined();
         
            try {
                return constructor_invoke<ClassType, Args...>(v8args);
            } 
            
            catch (std::exception & e) {
                  return v8::ThrowException(
                    v8::String::New(e.what())
                  );
            } 
        }
    };

} // namespace v8Bind

#endif
