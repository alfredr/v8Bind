#ifndef V8BIND_HOOK_FUNCTION_H_
#define V8BIND_HOOK_FUNCTION_H_

#include <v8.h>
#include "make_weak.h"
#include "invokers/function.h"

namespace v8Bind {
    /* FunctionData holds a function pointer and provides
     * a method for issuing calls to that pointer. This
     * struct is held as data by the exported function in
     * v8 and is used by function hook to invoke the 
     * appropriate function
     */

    template <typename FuncPtrType>
    struct FunctionData {

        FunctionData(FuncPtrType p_func)
            : _p_func(p_func) { }

        v8::Handle<v8::Value> invoke(const v8::Arguments & args) {
            return function_invoker(*_p_func, args);
        }
    
        protected:
        FuncPtrType _p_func;
    };

    /* Function is a template used for invoking functions
     * matching a specific signature. The actual function
     * being invoked is determined by the contents of
     * the FunctionData object held by the v8 function.
     */

    template <typename FuncPtrType>
    struct Function {
        typedef FunctionData<FuncPtrType> TFunctionData;

        /* Info is a helper function for building the data object that
         * holds the function pointer used by Hook in dispatching the function 
         * call.
         */
        inline static v8::Handle<v8::External> Info(FuncPtrType p_func) {
            return make_weak(new TFunctionData(p_func));
        }

        inline static v8::Handle<v8::Value> Hook(const v8::Arguments & v8args) {
            try {
           
                TFunctionData * p_stub (
                    static_cast<TFunctionData*> (
                        v8::External::Unwrap(v8args.Data())
                    )
                );
            
                return p_stub->invoke(v8args); 
            }
           
            /*
             * If an exception occurs during invocation we extract the
             * message and pass it into v8 for handling instead of allowing
             * it to terminate the program.
             */
            catch (const std::exception & e) {
                return v8::ThrowException(
                    v8::String::New(e.what())
                );
            }
        }

    };
} // namespace v8Bind

#endif
