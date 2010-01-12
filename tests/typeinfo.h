#include <cxxtest/TestSuite.h>
#include <typeinfo.h>

struct Base { };
struct Intermediate : Base { };
struct Derived : Intermediate { };
struct Other { };

class TypeinfoTestSuite : public CxxTest::TestSuite {
    public:
       
    void test_typeid(void) {
        TS_ASSERT(typeid(Base) == typeid(const Base));
    }

    void test_typeinfo(void) {
        v8Bind::Typechain<Derived, Base> nfo;
        TS_ASSERT_EQUALS(v8Bind::InChain<Base>(nfo), true);
        TS_ASSERT_EQUALS(v8Bind::InChain<Derived>(nfo), true);
        TS_ASSERT_EQUALS(v8Bind::InChain<Other>(nfo), false);
        TS_ASSERT_EQUALS(v8Bind::InChain<Intermediate>(nfo), false);
    }
};
