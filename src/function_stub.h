#ifndef V8BIND_FUNCTION_STUB_H_
#define V8BIND_FUNCTION_STUB_H_

#include <v8.h>
#include <string>

#include "typeinfo.h"
#include "strip_qualifiers.h"

namespace v8Bind {

    static const int FIELDCOUNT = 2;
    
    /*
     * This is a structure for associating a v8 object type
     * with a c++ object type. It should be accessed through
     * FunctionStub<T>::Get.
     */
    template <typename T>
    struct _FunctionStub {
        static inline const std::string & GetName(void);
        static inline void SetName(const std::string &name);

        static inline void SetTypeinfo(const ITypeinfo * ptypeinfo);
        static inline const ITypeinfo * GetTypeinfo(void);

        static inline v8::Handle<v8::FunctionTemplate> GetTemplate(void);
        static inline v8::Handle<v8::Function> GetFunction(void);

        /*
         * Creates an archetypal object for cloning. This should be
         * done after any function/object template customizations but 
         * before a CallHandler is set for this FunctionTemplate.
         */

        static inline v8::Handle<v8::Object> CloneArchetype(void);
        static inline void FinalizeArchetype(void);

        static inline void Clear(void);

        protected:
        static std::string _name;
        static v8::Handle<v8::FunctionTemplate> _template;
        static v8::Handle<v8::Object> _archetype;
        static const ITypeinfo * _p_typeinfo;
    };

    template <typename T>
    inline const std::string & _FunctionStub<T>::GetName(void) {
        return _name;
    }

    template <typename T>
    inline void _FunctionStub<T>::SetName(const std::string & name) {
        _name = name;
        GetTemplate()->SetClassName(v8::String::New(_name.c_str()));
    }

    template <typename T>
    inline const ITypeinfo * _FunctionStub<T>::GetTypeinfo(void) {
        return _p_typeinfo;
    }

    template <typename T>
    inline void _FunctionStub<T>::SetTypeinfo(const ITypeinfo * ptypeinfo) {
        _p_typeinfo = ptypeinfo;
    }
        
    template <typename T>
    inline v8::Handle<v8::FunctionTemplate> 
    _FunctionStub<T>::GetTemplate(void) {
        if(!_template.IsEmpty())
            return _template;

        _template = v8::FunctionTemplate::New();
        _template->InstanceTemplate()->SetInternalFieldCount(FIELDCOUNT);
        _template->SetClassName(v8::String::New(GetName().c_str()));

        return _template;
    }

    template <typename T>
    inline v8::Handle<v8::Function> _FunctionStub<T>::GetFunction() {
        return GetTemplate()->GetFunction();
    }

    template <typename T>
    inline v8::Handle<v8::Object> _FunctionStub<T>::CloneArchetype(void) {
        return _archetype->Clone();
    }

    template <typename T>
    inline void _FunctionStub<T>::FinalizeArchetype(void) {
        _archetype = GetTemplate()->InstanceTemplate()->NewInstance();
    }

    template <typename T>
    inline void _FunctionStub<T>::Clear(void) {
        _archetype.Clear();
        _template.Clear();
        SetTypeinfo(NULL);
    }

    template <typename T>
    std::string _FunctionStub<T>::_name("UnidentifiedObject");

    template <typename T>
    v8::Handle<v8::FunctionTemplate> _FunctionStub<T>::_template;

    template <typename T>
    v8::Handle<v8::Object> _FunctionStub<T>::_archetype;
 
    template <typename T>
    const ITypeinfo * _FunctionStub<T>::_p_typeinfo;

    /*
     * This is a structure which associates to
     * a given type T the appropriate _FunctionStub
     * for that type. The idea here is to boil
     * away any extra type qualifiers on T.
     *
     * For example, FunctionStub<T const *>::Get
     * should be the same as FunctionStub<T>::Get.
     */
    template <typename T>
    struct FunctionStub {
        typedef _FunctionStub <
            typename StripQualifiers<T>::Type
        > Get;
    };

} // namespace v8bind

#endif
