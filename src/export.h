#ifndef V8BIND_EXPORT_H_
#define V8BIND_EXPORT_H_

#include <v8.h>
#include <string>

#include "conversions.h"
#include "function_stub_populator.h"

#include "hooks/constructor.h"
#include "hooks/function.h"
#include "hooks/member.h"

#include "export_helpers.h"

namespace v8Bind {

    template <typename... Derivation>
    struct Export;

    template <typename ObjectType, typename... Bases>
    struct Export<ObjectType, Bases...> {
        Export(const std::string &name);

        template <typename... Args>
        Export<ObjectType, Bases...> & Constructor(void);

        template <typename ObjectTemplate = TPrototype, typename FuncPtrType>
        Export<ObjectType, Bases...> & Member(const std::string &name, FuncPtrType p_f);

        template <typename ObjectTemplate = TFunction, typename FuncPtrType>
        Export<ObjectType, Bases...> & Function(const std::string &name, FuncPtrType p_f);

        template <typename ObjectTemplate = TFunction, typename T>
        Export<ObjectType, Bases...> & Value(const std::string &name, T value);

        void Finalize(void) const;

        protected:
        v8::InvocationCallback _ctor_hook;
    };

    template <typename ObjectType, typename... Bases> 
    Export<ObjectType, Bases...>::Export(const std::string &name) 
            :_ctor_hook(0) {
        
        FunctionStubPopulator<ObjectType, Bases...>::Setup();
        FunctionStub<ObjectType>::Get::SetName(name);
    }

    template <typename ObjectType, typename... Bases> 
    template <typename... Args>
    Export<ObjectType, Bases...> & 
    Export<ObjectType, Bases...>::Constructor(void) {

        _ctor_hook = v8Bind::Constructor<ObjectType, Args...>::Hook;
        return *this;
    }


    template <typename ObjectType, typename... Bases>
    template <typename ObjectTemplate, typename FuncPtrType> 
    Export<ObjectType, Bases...> &
    Export<ObjectType, Bases...>::Member(const std::string &name, FuncPtrType p_f) {

        v8::Handle<v8::FunctionTemplate> HFuncTmpl (
            v8::FunctionTemplate::New(
                v8Bind::Member<FuncPtrType>::Hook, 
                v8Bind::Member<FuncPtrType>::Info(p_f)
            )
        );

        ObjectTemplate::template Get<ObjectType>()->Set(
            v8::String::New(name.c_str()), HFuncTmpl
        );

        return *this;
    }

    template <typename ObjectType, typename... Bases>
    template <typename ObjectTemplate, typename FuncPtrType> 
    Export<ObjectType, Bases...> &
    Export<ObjectType, Bases...>::Function(const std::string &name, FuncPtrType p_f) {

        v8::Handle<v8::FunctionTemplate> HFuncTmpl (
            v8::FunctionTemplate::New(
                v8Bind::Function<FuncPtrType>::Hook, 
                v8Bind::Function<FuncPtrType>::Info(p_f)
            )
        );

        ObjectTemplate::template Get<ObjectType>()->Set(
            v8::String::New(name.c_str()), HFuncTmpl
        );

        return *this;
    }

    template <typename ObjectType, typename... Bases>
    template <typename ObjectTemplate, typename T> 
    Export<ObjectType, Bases...> &
    Export<ObjectType, Bases...>::Value(const std::string &name, T value) {
        ObjectTemplate::template Get<ObjectType>()->Set(
            v8::String::New(name.c_str()), v8Bind::ToV8<T>(value)
        );

        return *this;
    }

    template <typename ObjectType, typename... Bases>
    void Export<ObjectType, Bases...>::Finalize(void) const {
        const std::string & name(
            FunctionStub<ObjectType>::Get::GetName()
        );

        /* Create an archetypal for cloning. This will fail
         * if the constructor is expecting arguments, which
         * is why it's done first.
         */
        
        FunctionStub<ObjectType>::Get::FinalizeArchetype();

        if(_ctor_hook)
            FunctionStub<ObjectType>::Get::GetTemplate()
                ->SetCallHandler(_ctor_hook);

        v8::Handle<v8::Object> HGlobal(v8::Context::GetCurrent()->Global());
        HGlobal->Set(ToV8(name), FunctionStub<ObjectType>::Get::GetFunction());
    }

} // namespace v8Bind

#endif
