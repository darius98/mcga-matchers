#include "mcga/test.hpp"

#include "mcga/matchers/pointer.hpp"
#include "mcga/matchers/testing_helpers.hpp"

using mcga::matchers::isNotNull;
using mcga::matchers::isNull;
using mcga::test::group;
using mcga::test::setUp;
using mcga::test::tearDown;
using mcga::test::test;
using mcga::test::TestCase;

class BasicClass {};
struct BasicStruct {};

int globalInt;
BasicClass globalClass;
BasicStruct globalStruct;
double globalDouble;

static auto t = TestCase{"Matchers::pointer"} + [] {
    group("Null pointers", [] {
        int* intNullPtr = nullptr;
        BasicClass* classNullPtr = nullptr;
        BasicStruct* structNullPtr = nullptr;
        double* doubleNullPtr = nullptr;

        test("isNull matcher matches nullptr", [] {
            EXPECT_MATCHER_MATCHES(nullptr, isNull);
        });

        test("isNull matcher matches null pointer of different types", [&] {
            EXPECT_MATCHER_MATCHES(intNullPtr, isNull);
            EXPECT_MATCHER_MATCHES(classNullPtr, isNull);
            EXPECT_MATCHER_MATCHES(structNullPtr, isNull);
            EXPECT_MATCHER_MATCHES(doubleNullPtr, isNull);
        });

        test("isNotNull matcher does not match nullptr", [&] {
            EXPECT_MATCHER_FAILS(nullptr, isNotNull);
        });

        test("isNotNull matcher does not match null pointer of different types",
             [&] {
                 EXPECT_MATCHER_FAILS(intNullPtr, isNotNull);
                 EXPECT_MATCHER_FAILS(classNullPtr, isNotNull);
                 EXPECT_MATCHER_FAILS(structNullPtr, isNotNull);
                 EXPECT_MATCHER_FAILS(doubleNullPtr, isNotNull);
             });
    });

    group("Non-null pointers", [] {
        std::unique_ptr<int> intHeapPtr;
        std::unique_ptr<BasicClass> classHeapPtr;
        std::unique_ptr<BasicStruct> structHeapPtr;
        std::unique_ptr<double> doubleHeapPtr;

        int stackInt;
        BasicClass stackClass;
        BasicStruct stackStruct;
        double stackDouble;

        setUp([&] {
            intHeapPtr = std::make_unique<int>();
            classHeapPtr = std::make_unique<BasicClass>();
            structHeapPtr = std::make_unique<BasicStruct>();
            doubleHeapPtr = std::make_unique<double>();
        });

        tearDown([&] {
            intHeapPtr.reset();
            classHeapPtr.reset();
            structHeapPtr.reset();
            doubleHeapPtr.reset();
        });

        test("isNull does not match non-null heap pointers", [&] {
            EXPECT_MATCHER_FAILS(intHeapPtr.get(), isNull);
            EXPECT_MATCHER_FAILS(classHeapPtr.get(), isNull);
            EXPECT_MATCHER_FAILS(structHeapPtr.get(), isNull);
            EXPECT_MATCHER_FAILS(doubleHeapPtr.get(), isNull);
        });

        test("isNotNull matches non-null heap pointers", [&] {
            EXPECT_MATCHER_MATCHES(intHeapPtr.get(), isNotNull);
            EXPECT_MATCHER_MATCHES(classHeapPtr.get(), isNotNull);
            EXPECT_MATCHER_MATCHES(structHeapPtr.get(), isNotNull);
            EXPECT_MATCHER_MATCHES(doubleHeapPtr.get(), isNotNull);
        });

        test("isNull does not match non-null stack pointers", [&] {
            EXPECT_MATCHER_FAILS(&stackInt, isNull);
            EXPECT_MATCHER_FAILS(&stackClass, isNull);
            EXPECT_MATCHER_FAILS(&stackStruct, isNull);
            EXPECT_MATCHER_FAILS(&stackDouble, isNull);
        });

        test("isNotNull matches non-null stack pointers", [&] {
            EXPECT_MATCHER_MATCHES(&stackInt, isNotNull);
            EXPECT_MATCHER_MATCHES(&stackClass, isNotNull);
            EXPECT_MATCHER_MATCHES(&stackStruct, isNotNull);
            EXPECT_MATCHER_MATCHES(&stackDouble, isNotNull);
        });

        test("isNull does not match non-null stack pointers", [&] {
            EXPECT_MATCHER_FAILS(&globalInt, isNull);
            EXPECT_MATCHER_FAILS(&globalClass, isNull);
            EXPECT_MATCHER_FAILS(&globalStruct, isNull);
            EXPECT_MATCHER_FAILS(&globalDouble, isNull);
        });

        test("isNotNull matches non-null data segment pointers", [&] {
            EXPECT_MATCHER_MATCHES(&globalInt, isNotNull);
            EXPECT_MATCHER_MATCHES(&globalClass, isNotNull);
            EXPECT_MATCHER_MATCHES(&globalStruct, isNotNull);
            EXPECT_MATCHER_MATCHES(&globalDouble, isNotNull);
        });
    });
};
