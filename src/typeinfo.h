#ifndef V8BIND_TYPEINFO_H_
#define V8BIND_TYPEINFO_H_

#include <typeinfo>
#include <type_traits>

#include "enable_if.h"

namespace v8Bind {
    struct ITypeinfo {
        virtual bool in_chain(const std::type_info & typeinfo) const = 0;
    };

    template <typename T>
    inline bool InChain(const ITypeinfo & typeinfo) {
        return typeinfo.in_chain(typeid(T));
    }

    /* Typechain encodes a derivation sequence and
     * provides a runtime check for testing if a
     * given typeid belongs to that sequence
     */

    template <typename... Derivation>
    struct Typechain;

    template <typename ObjectType>
    struct Typechain <ObjectType> : ITypeinfo {

        //guard against const types
        typedef typename EnableIf< ObjectType,
            ! std::is_const< ObjectType >::value
        >::Type ObjectTypeIsNonConst;

        static inline bool InChain(const std::type_info & type) {
            return typeid(ObjectType) == type;
        }

        virtual inline bool in_chain(const std::type_info & type) const {
            return InChain(type);
        }
   };

    template <typename ObjectType, typename Base, typename... Ancestors>
    struct Typechain <ObjectType, Base , Ancestors...> 
        : Typechain <Base, Ancestors...> { 
        
        //guard against non-const types
        typedef typename EnableIf< ObjectType,
            ! std::is_const< ObjectType >::value
        >::Type ObjectTypeIsNonConst;

        //guard against invalid type heirarchies
        typedef typename EnableIf< ObjectType, 
            std::is_base_of<Base, ObjectType>::value 
        >::Type BaseIsValid;

        static inline bool InChain(const std::type_info & type) {
            if(typeid(ObjectType) == type)
                return true;

            return Typechain<Base, Ancestors...>::InChain(type);
        }

        virtual inline bool in_chain(const std::type_info &type) const {
            return InChain(type);
        }
    };

} // namespace v8Bind

#endif
