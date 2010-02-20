#include <cxxtest/TestSuite.h>

#include <iostream>
#include <export.h>

int sub(int x, int y) {
    return x-y;
}

struct TestClassA {

    int add(int x, int y) {
        return x + y;
    }

    bool greater(int a, int b) {
        return a > b;
    }
};

struct TestClassB {
    TestClassB(int value)
        : _value(value) { };

    int get_value() const {
        return _value;
    }

    void set_value(int value) {
        _value = value;
    }

    TestClassB get_copy() {
        return *this;
    }

    TestClassB & get_reference() {
        return *this;
    }

    const TestClassB & get_const_reference() const {
        return *this;
    }

    TestClassB * get_pointer() {
        return this;
    }

    const TestClassB * get_const_pointer() const {
        return this;
    }

    int _value;
};

class ExportTestSute : public CxxTest::TestSuite {
    public:

    v8::Handle<v8::Value> execute_string(const std::string & source) {
        v8::Handle<v8::Script> Script = v8::Script::Compile(
            v8::String::New(source.c_str()), 
            v8::Handle<v8::String>()
        );
        return Script->Run();
    }

    void setUp(void) {
        context = v8::Context::New();
    }

    void tearDown(void) { 
        context.Dispose();
    }
    
    void test_constructor(void) {
        v8::HandleScope scope;
        v8::Context::Scope cscope(context);

        v8Bind::Export<TestClassA>("TestClassA")
            .Constructor()
            .Finalize();

        TS_ASSERT_THROWS_NOTHING(
            execute_string("emb = new TestClassA;")
        );

        v8Bind::FunctionStub<TestClassA>::Get::Clear();
    }

    void test_method_call(void) {
        v8::HandleScope scope;
        v8::Context::Scope cscope(context);

        v8Bind::Export<TestClassA>("TestClassA")
            .Constructor()
            .Member("add", &TestClassA::add)
            .Finalize();

        v8::Handle<v8::Value> result;

        TS_ASSERT_THROWS_NOTHING (
            result = execute_string("emb = new TestClassA; emb.add(123, 456);")
        );

        TS_ASSERT_EQUALS(v8Bind::FromV8<int>(result), 123+456);

        v8Bind::FunctionStub<TestClassA>::Get::Clear();
    }

    void test_argument_order(void) {
        v8::HandleScope scope;
        v8::Context::Scope cscope(context);

        v8Bind::Export<TestClassA>("TestClassA")
            .Constructor()
            .Member("greater", &TestClassA::greater)
            .Finalize();

        v8::Handle<v8::Value> result;

        result = execute_string("emb = new TestClassA; emb.greater(123, 456);");

        TS_ASSERT_EQUALS(v8Bind::FromV8<bool>(result), false);

        result = execute_string("emb = new TestClassA; emb.greater(456, 123);");

        TS_ASSERT_EQUALS(v8Bind::FromV8<bool>(result), true);

        v8Bind::FunctionStub<TestClassA>::Get::Clear();
    }

    void test_construct_with_argument(void) {
        v8::HandleScope scope;
        v8::Context::Scope cscope(context);

        v8Bind::Export<TestClassB>("TestClassB")
            .Constructor<int>()
            .Member("get_value", &TestClassB::get_value)
            .Finalize();

        v8::Handle<v8::Value> result;
        result = execute_string("emb = new TestClassB(12); emb.get_value();");
        TS_ASSERT_EQUALS(v8Bind::FromV8<int>(result), 12);
        
        v8Bind::FunctionStub<TestClassB>::Get::Clear();
    }

    void test_return_by_value(void) {
        v8::HandleScope scope;
        v8::Context::Scope cscope(context);

        v8Bind::Export<TestClassB>("TestClassB")
            .Constructor<int>()
            .Member("get_value", &TestClassB::get_value)
            .Member("set_value", &TestClassB::set_value)
            .Member("get_copy", &TestClassB::get_copy)
            .Finalize();

        v8::Handle<v8::Value> result = execute_string(
            std::string("emb = new TestClassB(12);")
                + "copy = emb.get_copy();"
                + "emb.set_value(10); "
                + "copy.get_value();"
        );

        TS_ASSERT_EQUALS(v8Bind::FromV8<int>(result), 12);
        
        v8Bind::FunctionStub<TestClassB>::Get::Clear();
    }

    void test_return_by_reference(void) {
        v8::HandleScope scope;
        v8::Context::Scope cscope(context);

        v8Bind::Export<TestClassB>("TestClassB")
            .Constructor<int>()
            .Member("get_value", &TestClassB::get_value)
            .Member("set_value", &TestClassB::set_value)
            .Member("get_reference", &TestClassB::get_reference)
            .Member("get_const_reference", 
                &TestClassB::get_const_reference)
            .Finalize();

        v8::Handle<v8::Value> result = execute_string(
           std::string("emb = new TestClassB(12);")
               + "ref = emb.get_reference();"
               + "emb.set_value(13);"
               + "ref.get_value();"
        );

        TS_ASSERT_EQUALS(v8Bind::FromV8<int>(result), 13);
    
        v8::TryCatch trycatch;

        execute_string(
            std::string("cref = emb.get_const_reference();")
                + "cref.set_value(11);"
        );

        TS_ASSERT_EQUALS(v8Bind::ConstCastFailureException::Message,
            *v8::String::AsciiValue(trycatch.Exception())
        );

        v8Bind::FunctionStub<TestClassB>::Get::Clear();
    }

    void test_return_by_pointer(void) {
        v8::HandleScope scope;
        v8::Context::Scope cscope(context);

        v8Bind::Export<TestClassB>("TestClassB")
            .Constructor<int>()
            .Member("get_value", &TestClassB::get_value)
            .Member("set_value", &TestClassB::set_value)
            .Member("get_pointer", &TestClassB::get_pointer)
            .Member("get_const_pointer", &TestClassB::get_const_pointer)
            .Finalize();

        v8::Handle<v8::Value> result = execute_string(
            std::string("emb = new TestClassB(12);")
                + "ref = emb.get_pointer();" 
                + "emb.set_value(13);" 
                + "ref.get_value();"
        );
        TS_ASSERT_EQUALS(v8Bind::FromV8<int>(result), 13);

        v8::TryCatch trycatch;

        execute_string(
            std::string("pref = emb.get_const_pointer();")
                + "pref.set_value(11);"
        );

        TS_ASSERT_EQUALS(v8Bind::ConstCastFailureException::Message,
            *v8::String::AsciiValue(trycatch.Exception())
        );


        v8Bind::FunctionStub<TestClassB>::Get::Clear();
    }

    void test_function(void) {
        v8::HandleScope scope;
        v8::Context::Scope cscope(context);

        v8Bind::Export<TestClassA>("TestClassA")
            .Constructor()
            .Function("sub", &sub)
            .Finalize();

        v8::Handle<v8::Value> result = execute_string("TestClassA.sub(100,50);");
        TS_ASSERT_EQUALS(v8Bind::FromV8<int>(result), 50);
        v8Bind::FunctionStub<TestClassA>::Get::Clear();
    }

    void test_value(void) {
        v8::HandleScope scope;
        v8::Context::Scope cscope(context);

        v8Bind::Export<TestClassB>("TestClassB")
            .Constructor<int>()
            .Member("get_value", &TestClassB::get_value)
            .Finalize();

        TestClassB B(4);
        v8Bind::Export<TestClassA>("TestClassA")
            .Constructor()
            .Value("MYCONST", 6)
            .Value("TESTCLASS", &B)
            .Finalize();

        v8::Handle<v8::Value> result;
        result = execute_string("TestClassA.MYCONST;");
        TS_ASSERT_EQUALS(v8Bind::FromV8<int>(result), 6);

        result = execute_string("TestClassA.TESTCLASS.get_value();");
        TS_ASSERT_EQUALS(v8Bind::FromV8<int>(result), 4);
 
        result = execute_string("TestClassA.TESTCLASS;");
        TS_ASSERT_EQUALS(v8Bind::FromV8<TestClassB&>(result).get_value(), 4);

       result = execute_string("TestClassA.TESTCLASS.get_value();");
        TS_ASSERT_EQUALS(v8Bind::FromV8<int>(result), 4);


        v8Bind::FunctionStub<TestClassA>::Get::Clear();
    }

    v8::Persistent<v8::Context> context;
};
