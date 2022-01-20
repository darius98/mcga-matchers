#include "mcga/test.hpp"

#include "mcga/matchers/functional.hpp"
#include "mcga/matchers/testing_helpers.hpp"

using mcga::matchers::throws;
using mcga::matchers::throwsA;
using mcga::test::expect;
using mcga::test::group;
using mcga::test::test;
using mcga::test::TestCase;

void simpleFunction() {
}

void simpleFunctionThrow() {
    throw std::runtime_error("Some error.");
}

void simpleFunctionThrow3() {
    throw 3;
}

static auto t = TestCase("Matchers::functional") + [] {
    group("Lambdas", [] {
        test("throws matcher matches lambda throwing exception", [] {
            EXPECT_MATCHER_MATCHES(
              [] {
                  throw std::runtime_error("Some error.");
              },
              throws);
        });

        test("throws matcher matches lambda throwing 3", [] {
            expect(
              [] {
                  throw 3;
              },
              throws);
        });

        test("throws matcher does not match lambda that does not throw", [] {
            EXPECT_MATCHER_FAILS([] {}, throws);
        });

        test("throwsA matcher matches lambda throwing exact error type", [] {
            EXPECT_MATCHER_MATCHES(
              [] {
                  throw std::runtime_error("Some error.");
              },
              throwsA<std::runtime_error>());
        });

        test("throwsA matcher matches lambda throwing subtype", [] {
            EXPECT_MATCHER_MATCHES(
              [] {
                  throw std::range_error("Some range error.");
              },
              throwsA<std::runtime_error>());
        });

        test("throwsA matcher does not match lambda throwing supertype", [] {
            EXPECT_MATCHER_FAILS(
              [] {
                  throw std::runtime_error("Some error.");
              },
              throwsA<std::range_error>());
        });

        test("throwsA matcher does not match lambda throwing different types",
             [] {
                 EXPECT_MATCHER_FAILS(
                   [] {
                       throw 3;
                   },
                   throwsA<std::runtime_error>());
             });

        test("throwsA matcher does not match lambda that does not throw", [] {
            EXPECT_MATCHER_FAILS([] {}, throwsA<std::runtime_error>());
        });
    });

    group("Simple global functions", [] {
        test("throws matcher matches function throwing an exception", [] {
            EXPECT_MATCHER_MATCHES(simpleFunctionThrow, throws);
        });

        test("throws matcher matches function throwing 3", [] {
            EXPECT_MATCHER_MATCHES(simpleFunctionThrow3, throws);
        });

        test("throws matcher does not match function not throwing", [] {
            EXPECT_MATCHER_FAILS(simpleFunction, throws);
        });

        test("throwsA matcher matches function throwing specific type", [] {
            EXPECT_MATCHER_MATCHES(simpleFunctionThrow,
                                   throwsA<std::runtime_error>());
            EXPECT_MATCHER_MATCHES(simpleFunctionThrow3, throwsA<int>());
        });

        test("throwsA matcher does not match function throwing different type",
             [] {
                 EXPECT_MATCHER_FAILS(simpleFunctionThrow3,
                                      throwsA<std::runtime_error>());
                 EXPECT_MATCHER_FAILS(simpleFunctionThrow, throwsA<int>());
             });

        test("throwsA matcher does not match function not throwing", [] {
            EXPECT_MATCHER_FAILS(simpleFunction, throwsA<std::runtime_error>());
            EXPECT_MATCHER_FAILS(simpleFunction, throwsA<int>());
        });
    });
};
