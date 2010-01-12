/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/ErrorPrinter.h>

int main() {
 return CxxTest::ErrorPrinter().run();
}
#include "./converters.h"

static ConverterTestSuite suite_ConverterTestSuite;

static CxxTest::List Tests_ConverterTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ConverterTestSuite( "./converters.h", 26, "ConverterTestSuite", suite_ConverterTestSuite, Tests_ConverterTestSuite );

static class TestDescription_ConverterTestSuite_test_bool_converter : public CxxTest::RealTestDescription {
public:
 TestDescription_ConverterTestSuite_test_bool_converter() : CxxTest::RealTestDescription( Tests_ConverterTestSuite, suiteDescription_ConverterTestSuite, 42, "test_bool_converter" ) {}
 void runTest() { suite_ConverterTestSuite.test_bool_converter(); }
} testDescription_ConverterTestSuite_test_bool_converter;

static class TestDescription_ConverterTestSuite_test_double_converter : public CxxTest::RealTestDescription {
public:
 TestDescription_ConverterTestSuite_test_double_converter() : CxxTest::RealTestDescription( Tests_ConverterTestSuite, suiteDescription_ConverterTestSuite, 50, "test_double_converter" ) {}
 void runTest() { suite_ConverterTestSuite.test_double_converter(); }
} testDescription_ConverterTestSuite_test_double_converter;

static class TestDescription_ConverterTestSuite_test_float_converter : public CxxTest::RealTestDescription {
public:
 TestDescription_ConverterTestSuite_test_float_converter() : CxxTest::RealTestDescription( Tests_ConverterTestSuite, suiteDescription_ConverterTestSuite, 58, "test_float_converter" ) {}
 void runTest() { suite_ConverterTestSuite.test_float_converter(); }
} testDescription_ConverterTestSuite_test_float_converter;

static class TestDescription_ConverterTestSuite_test_int_converter : public CxxTest::RealTestDescription {
public:
 TestDescription_ConverterTestSuite_test_int_converter() : CxxTest::RealTestDescription( Tests_ConverterTestSuite, suiteDescription_ConverterTestSuite, 66, "test_int_converter" ) {}
 void runTest() { suite_ConverterTestSuite.test_int_converter(); }
} testDescription_ConverterTestSuite_test_int_converter;

static class TestDescription_ConverterTestSuite_test_unsigned_int_converter : public CxxTest::RealTestDescription {
public:
 TestDescription_ConverterTestSuite_test_unsigned_int_converter() : CxxTest::RealTestDescription( Tests_ConverterTestSuite, suiteDescription_ConverterTestSuite, 74, "test_unsigned_int_converter" ) {}
 void runTest() { suite_ConverterTestSuite.test_unsigned_int_converter(); }
} testDescription_ConverterTestSuite_test_unsigned_int_converter;

static class TestDescription_ConverterTestSuite_test_stl_string_converter : public CxxTest::RealTestDescription {
public:
 TestDescription_ConverterTestSuite_test_stl_string_converter() : CxxTest::RealTestDescription( Tests_ConverterTestSuite, suiteDescription_ConverterTestSuite, 82, "test_stl_string_converter" ) {}
 void runTest() { suite_ConverterTestSuite.test_stl_string_converter(); }
} testDescription_ConverterTestSuite_test_stl_string_converter;

static class TestDescription_ConverterTestSuite_test_value_object_converter : public CxxTest::RealTestDescription {
public:
 TestDescription_ConverterTestSuite_test_value_object_converter() : CxxTest::RealTestDescription( Tests_ConverterTestSuite, suiteDescription_ConverterTestSuite, 90, "test_value_object_converter" ) {}
 void runTest() { suite_ConverterTestSuite.test_value_object_converter(); }
} testDescription_ConverterTestSuite_test_value_object_converter;

static class TestDescription_ConverterTestSuite_test_derived_value_object_converter : public CxxTest::RealTestDescription {
public:
 TestDescription_ConverterTestSuite_test_derived_value_object_converter() : CxxTest::RealTestDescription( Tests_ConverterTestSuite, suiteDescription_ConverterTestSuite, 104, "test_derived_value_object_converter" ) {}
 void runTest() { suite_ConverterTestSuite.test_derived_value_object_converter(); }
} testDescription_ConverterTestSuite_test_derived_value_object_converter;

static class TestDescription_ConverterTestSuite_test_invalid_derived_value_conversion : public CxxTest::RealTestDescription {
public:
 TestDescription_ConverterTestSuite_test_invalid_derived_value_conversion() : CxxTest::RealTestDescription( Tests_ConverterTestSuite, suiteDescription_ConverterTestSuite, 124, "test_invalid_derived_value_conversion" ) {}
 void runTest() { suite_ConverterTestSuite.test_invalid_derived_value_conversion(); }
} testDescription_ConverterTestSuite_test_invalid_derived_value_conversion;

static class TestDescription_ConverterTestSuite_test_non_object_to_object_conversion : public CxxTest::RealTestDescription {
public:
 TestDescription_ConverterTestSuite_test_non_object_to_object_conversion() : CxxTest::RealTestDescription( Tests_ConverterTestSuite, suiteDescription_ConverterTestSuite, 144, "test_non_object_to_object_conversion" ) {}
 void runTest() { suite_ConverterTestSuite.test_non_object_to_object_conversion(); }
} testDescription_ConverterTestSuite_test_non_object_to_object_conversion;

static class TestDescription_ConverterTestSuite_test_const_pointer_to_non_const : public CxxTest::RealTestDescription {
public:
 TestDescription_ConverterTestSuite_test_const_pointer_to_non_const() : CxxTest::RealTestDescription( Tests_ConverterTestSuite, suiteDescription_ConverterTestSuite, 159, "test_const_pointer_to_non_const" ) {}
 void runTest() { suite_ConverterTestSuite.test_const_pointer_to_non_const(); }
} testDescription_ConverterTestSuite_test_const_pointer_to_non_const;

static class TestDescription_ConverterTestSuite_test_non_const_pointer_to_const : public CxxTest::RealTestDescription {
public:
 TestDescription_ConverterTestSuite_test_non_const_pointer_to_const() : CxxTest::RealTestDescription( Tests_ConverterTestSuite, suiteDescription_ConverterTestSuite, 176, "test_non_const_pointer_to_const" ) {}
 void runTest() { suite_ConverterTestSuite.test_non_const_pointer_to_const(); }
} testDescription_ConverterTestSuite_test_non_const_pointer_to_const;

static class TestDescription_ConverterTestSuite_test_const_reference_to_non_const : public CxxTest::RealTestDescription {
public:
 TestDescription_ConverterTestSuite_test_const_reference_to_non_const() : CxxTest::RealTestDescription( Tests_ConverterTestSuite, suiteDescription_ConverterTestSuite, 193, "test_const_reference_to_non_const" ) {}
 void runTest() { suite_ConverterTestSuite.test_const_reference_to_non_const(); }
} testDescription_ConverterTestSuite_test_const_reference_to_non_const;

static class TestDescription_ConverterTestSuite_test_non_const_reference_to_const : public CxxTest::RealTestDescription {
public:
 TestDescription_ConverterTestSuite_test_non_const_reference_to_const() : CxxTest::RealTestDescription( Tests_ConverterTestSuite, suiteDescription_ConverterTestSuite, 212, "test_non_const_reference_to_const" ) {}
 void runTest() { suite_ConverterTestSuite.test_non_const_reference_to_const(); }
} testDescription_ConverterTestSuite_test_non_const_reference_to_const;

#include <cxxtest/Root.cpp>
