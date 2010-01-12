#ifndef V8BIND_FUNCTION_STUB_POPULATOR_H_
#define V8BIND_FUNCTION_STUB_POPULATOR_H_

#include "typeinfo.h"
#include "function_stub.h"

namespace v8Bind {

    template <typename... Derivation>
    struct FunctionStubPopulator;

    template < >
    struct FunctionStubPopulator< > {
        static void Setup(void) { };
    };

    template <typename Derived, typename... Bases>
    struct FunctionStubPopulator<Derived, Bases...> {
        static void Setup(void) {
            FunctionStub<Derived>::Get::SetTypeinfo(&_typeinfo);
            FunctionStubPopulator<Bases...>::Setup();
        }

        protected:
        static Typechain<Derived, Bases...> _typeinfo;
    };

    template <typename Derived, typename... Bases> Typechain<Derived, Bases...>
    FunctionStubPopulator<Derived, Bases...>::_typeinfo;
}

#endif
