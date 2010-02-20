#ifndef V8BIND_HOOK_MEMBER_H_
#define V8BIND_HOOK_MEMBER_H_

#include <stdexcept>

#include <v8.h>
#include "function_traits.h"
#include "conversions.h"
#include "invokers/member.h"
#include "make_weak.h"

namespace v8Bind {

    /* Below are classes for facilitating invocation od
     * member functions. Their roles are exactly analogous
     * to those for the Function hooks. See the notes
     * there.
     */

    template <typename MemberPtrType>
    struct MemberData {

        typedef FunctionTraits<MemberPtrType> Traits;

        MemberData(MemberPtrType p_member) 
            : _p_member(p_member) { }

        v8::Handle<v8::Value> invoke(typename Traits::ConstAwareClassType * p_that, 
                const v8::Arguments& v8args) {
            return member_invoker(p_that, _p_member, v8args);
        }

        protected:
        MemberPtrType _p_member;
    };

    template <typename MemberPtrType>
    struct Member {
        typedef MemberData<MemberPtrType> TMemberData;
        typedef FunctionTraits<MemberPtrType> Traits;

        inline static v8::Handle<v8::External> Info(MemberPtrType p_member) {
            return make_weak( new TMemberData(p_member) );
        }

        inline static v8::Handle<v8::Value> Hook(const v8::Arguments & v8args) {
            try {
                typename Traits::ConstAwareClassType * p_that 
                    = FromV8<typename Traits::ConstAwareClassType *>(v8args.This());
            
                TMemberData * p_member_stub (
                    static_cast<TMemberData*> (
                        v8::External::Unwrap(v8args.Data())
                    )
                );
            
                return p_member_stub->invoke(p_that, v8args); 
            }
            
            catch (const std::exception & e) {
                return v8::ThrowException(
                    v8::String::New(e.what())
                );
            }
        }
    };

} // namespace v8Bind

#endif
