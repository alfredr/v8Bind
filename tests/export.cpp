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
#include "./export.h"

static ExportTestSute suite_ExportTestSute;

static CxxTest::List Tests_ExportTestSute = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ExportTestSute( "./export.h", 52, "ExportTestSute", suite_ExportTestSute, Tests_ExportTestSute );

static class TestDescription_ExportTestSute_test_constructor : public CxxTest::RealTestDescription {
public:
 TestDescription_ExportTestSute_test_constructor() : CxxTest::RealTestDescription( Tests_ExportTestSute, suiteDescription_ExportTestSute, 71, "test_constructor" ) {}
 void runTest() { suite_ExportTestSute.test_constructor(); }
} testDescription_ExportTestSute_test_constructor;

static class TestDescription_ExportTestSute_test_method_call : public CxxTest::RealTestDescription {
public:
 TestDescription_ExportTestSute_test_method_call() : CxxTest::RealTestDescription( Tests_ExportTestSute, suiteDescription_ExportTestSute, 86, "test_method_call" ) {}
 void runTest() { suite_ExportTestSute.test_method_call(); }
} testDescription_ExportTestSute_test_method_call;

static class TestDescription_ExportTestSute_test_argument_order : public CxxTest::RealTestDescription {
public:
 TestDescription_ExportTestSute_test_argument_order() : CxxTest::RealTestDescription( Tests_ExportTestSute, suiteDescription_ExportTestSute, 106, "test_argument_order" ) {}
 void runTest() { suite_ExportTestSute.test_argument_order(); }
} testDescription_ExportTestSute_test_argument_order;

static class TestDescription_ExportTestSute_test_construct_with_argument : public CxxTest::RealTestDescription {
public:
 TestDescription_ExportTestSute_test_construct_with_argument() : CxxTest::RealTestDescription( Tests_ExportTestSute, suiteDescription_ExportTestSute, 128, "test_construct_with_argument" ) {}
 void runTest() { suite_ExportTestSute.test_construct_with_argument(); }
} testDescription_ExportTestSute_test_construct_with_argument;

static class TestDescription_ExportTestSute_test_return_by_value : public CxxTest::RealTestDescription {
public:
 TestDescription_ExportTestSute_test_return_by_value() : CxxTest::RealTestDescription( Tests_ExportTestSute, suiteDescription_ExportTestSute, 144, "test_return_by_value" ) {}
 void runTest() { suite_ExportTestSute.test_return_by_value(); }
} testDescription_ExportTestSute_test_return_by_value;

static class TestDescription_ExportTestSute_test_return_by_reference : public CxxTest::RealTestDescription {
public:
 TestDescription_ExportTestSute_test_return_by_reference() : CxxTest::RealTestDescription( Tests_ExportTestSute, suiteDescription_ExportTestSute, 166, "test_return_by_reference" ) {}
 void runTest() { suite_ExportTestSute.test_return_by_reference(); }
} testDescription_ExportTestSute_test_return_by_reference;

static class TestDescription_ExportTestSute_test_return_by_pointer : public CxxTest::RealTestDescription {
public:
 TestDescription_ExportTestSute_test_return_by_pointer() : CxxTest::RealTestDescription( Tests_ExportTestSute, suiteDescription_ExportTestSute, 193, "test_return_by_pointer" ) {}
 void runTest() { suite_ExportTestSute.test_return_by_pointer(); }
} testDescription_ExportTestSute_test_return_by_pointer;

#include <cxxtest/Root.cpp>
