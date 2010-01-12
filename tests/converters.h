#include <cxxtest/TestSuite.h>

#include <converters/bool.h>
#include <converters/double.h>
#include <converters/float.h>
#include <converters/int.h>
#include <converters/unsigned_int.h>
#include <converters/stl_string.h>
#include <converters/object.h>

#include <export.h>

struct TestClass {
    TestClass(int foo): _foo(foo) { };
    bool operator==(const TestClass & test) {
        return _foo == test._foo;
    }

    int _foo;
};

struct DerivedTestClass : TestClass { 
    DerivedTestClass(int foo) : TestClass(foo) { }
};

class ConverterTestSuite : public CxxTest::TestSuite {
    public:

    template <typename T>
    static inline T convert_test(T value) {
       return v8Bind::FromV8<T>(v8Bind::ToV8<T>(value));
    }

    void setUp(void) {
        context = v8::Context::New();
    }

    void tearDown(void) { 
        context.Dispose();
    }

    void test_bool_converter(void) {
        v8::HandleScope scope;
        v8::Context::Scope cscope(context);

        TS_ASSERT_EQUALS(convert_test(true), true);
        TS_ASSERT_EQUALS(convert_test(false), false);
    }
 
    void test_double_converter(void) {
        v8::HandleScope scope;
        v8::Context::Scope cscope(context);

        double pi = 3.14159265;
        TS_ASSERT_DELTA(convert_test(pi), pi, 1e-5);
    }

    void test_float_converter(void) {
        v8::HandleScope scope;
        v8::Context::Scope cscope(context);

        float pi = 3.14159265;
        TS_ASSERT_DELTA(convert_test(pi), pi, 1e-5);
    }

    void test_int_converter(void) {
        v8::HandleScope scope;
        v8::Context::Scope cscope(context);

        int test = 0xDEADBEEF;
        TS_ASSERT_EQUALS(convert_test(test), test);
    }

    void test_unsigned_int_converter(void) {
        v8::HandleScope scope;
        v8::Context::Scope cscope(context);

        unsigned int test = 0xDEADBEEF;
        TS_ASSERT_EQUALS(convert_test(test), test);
    }

    void test_stl_string_converter(void) {
        v8::HandleScope scope;
        v8::Context::Scope cscope(context);

        std::string test_string("HEWO 27 PUPPIES!!");
        TS_ASSERT_EQUALS(convert_test(test_string), test_string);
    }

    void test_value_object_converter(void) {
        v8::HandleScope scope;
        v8::Context::Scope cscope(context);
 
        v8Bind::Export<TestClass>("TestClass").Finalize();

        TestClass test_object(456);
        TestClass test_object_2(123);
        TS_ASSERT_EQUALS(convert_test(test_object), test_object);
        TS_ASSERT_DIFFERS(convert_test(test_object), test_object_2);

        v8Bind::FunctionStub<TestClass>::Get::Clear();
    }

    void test_derived_value_object_converter(void) {
        v8::HandleScope scope;
        v8::Context::Scope cscope(context);

        v8Bind::Export<TestClass>("TestClass").Finalize();
        v8Bind::Export<DerivedTestClass, TestClass>("DerivedTestClass").Finalize();

        DerivedTestClass derived_test_object(123);
        TestClass base_test_object(
            v8Bind::FromV8<TestClass>(
                v8Bind::ToV8<DerivedTestClass>(derived_test_object)
            )
        );

        TS_ASSERT_EQUALS(base_test_object, derived_test_object);

        v8Bind::FunctionStub<DerivedTestClass>::Get::Clear();
        v8Bind::FunctionStub<TestClass>::Get::Clear();
    }

    void test_invalid_derived_value_conversion(void) {
        v8::HandleScope scope;
        v8::Context::Scope cscope(context);

        v8Bind::Export<TestClass>("TestClass").Finalize();
        v8Bind::Export<DerivedTestClass, TestClass>("DerivedTestClass").Finalize();

        TestClass base_test_object(123);
        TS_ASSERT_THROWS(
            DerivedTestClass derived_test_object(
                v8Bind::FromV8<DerivedTestClass>(
                    v8Bind::ToV8<TestClass>(base_test_object)
                )
            ), v8Bind::TypeCastFailureException
        )

        v8Bind::FunctionStub<DerivedTestClass>::Get::Clear();
        v8Bind::FunctionStub<TestClass>::Get::Clear();
    }

    void test_non_object_to_object_conversion(void) {
        v8::HandleScope scope;
        v8::Context::Scope cscope(context);
        
        v8Bind::Export<TestClass>("TestClass").Finalize();
     
        TS_ASSERT_THROWS(
            TestClass test(
                v8Bind::FromV8<TestClass>(v8Bind::ToV8<int>(456))
            ), v8Bind::TypeCastFailureException
        );

        v8Bind::FunctionStub<TestClass>::Get::Clear();
    }

    void test_const_pointer_to_non_const(void) {
        v8::HandleScope scope;
        v8::Context::Scope cscope(context);
        v8Bind::Export<TestClass>("TestClass").Finalize();

        TestClass test_object(789);
        const TestClass * p_const(&test_object);

        TS_ASSERT_THROWS(
            TestClass * p_non_const(
                 v8Bind::FromV8<TestClass *>(v8Bind::ToV8(p_const))
            ), v8Bind::ConstCastFailureException
        );

        v8Bind::FunctionStub<TestClass>::Get::Clear();
    }

    void test_non_const_pointer_to_const(void) {
        v8::HandleScope scope;
        v8::Context::Scope cscope(context);
        v8Bind::Export<TestClass>("TestClass").Finalize();

        TestClass test_object(789);
        TestClass * p_non_const(&test_object);

        TS_ASSERT_THROWS_NOTHING(
            const TestClass * p_non_const(
                 v8Bind::FromV8<const TestClass *>(v8Bind::ToV8(p_non_const))
            )
        );

        v8Bind::FunctionStub<TestClass>::Get::Clear();
    }

    void test_const_reference_to_non_const(void) {
        v8::HandleScope scope;
        v8::Context::Scope cscope(context);
        v8Bind::Export<TestClass>("TestClass").Finalize();

        TestClass test_object(789);
        const TestClass & r_const(test_object);

        TS_ASSERT_THROWS(
            TestClass & r_non_const(
                 v8Bind::FromV8<TestClass &>(
                     v8Bind::ToV8<const TestClass &>(r_const)
                 )
            ), v8Bind::ConstCastFailureException
        );

        v8Bind::FunctionStub<TestClass>::Get::Clear();
    }

    void test_non_const_reference_to_const(void) {
        v8::HandleScope scope;
        v8::Context::Scope cscope(context);
        v8Bind::Export<TestClass>("TestClass").Finalize();

        TestClass test_object(789);
        TestClass & r_non_const(test_object);

        TS_ASSERT_THROWS_NOTHING(
            const TestClass & r_const(
                 v8Bind::FromV8<const TestClass &>(v8Bind::ToV8(r_non_const))
            )
        );

        v8Bind::FunctionStub<TestClass>::Get::Clear();
    }

    v8::Persistent<v8::Context> context;
};
