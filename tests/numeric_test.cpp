#include "mcga/test.hpp"

#include "mcga/matchers/numeric.hpp"
#include "mcga/matchers/testing_helpers.hpp"

using mcga::matchers::isAlmostEqualTo;
using mcga::matchers::isEven;
using mcga::matchers::isNegative;
using mcga::matchers::isOdd;
using mcga::matchers::isPositive;
using mcga::matchers::isZero;
using mcga::test::group;
using mcga::test::test;
using mcga::test::TestCase;

constexpr auto kLargeLongLongNumber = 1LL << 60;

static auto t = TestCase{"Matchers::numeric"} + [] {
    group("isPositive", [&] {
        test("Matches positive numbers", [&] {
            EXPECT_MATCHER_MATCHES(3, isPositive)
            EXPECT_MATCHER_MATCHES(10, isPositive)
            EXPECT_MATCHER_MATCHES(kLargeLongLongNumber, isPositive)
            EXPECT_MATCHER_MATCHES(23u, isPositive)
            EXPECT_MATCHER_MATCHES(35.03, isPositive)
            EXPECT_MATCHER_MATCHES(3.503f, isPositive)
        });

        test("Does not match zero", [&] {
            EXPECT_MATCHER_FAILS(0, isPositive)
            EXPECT_MATCHER_FAILS(0.0, isPositive)
            EXPECT_MATCHER_FAILS(0LL, isPositive)
        });

        test("Does not match negative numbers", [&] {
            EXPECT_MATCHER_FAILS(-3, isPositive)
            EXPECT_MATCHER_FAILS(-10, isPositive)
            EXPECT_MATCHER_FAILS(-kLargeLongLongNumber, isPositive)
            EXPECT_MATCHER_FAILS(-35.03, isPositive)
            EXPECT_MATCHER_FAILS(-3.503f, isPositive)
        });
    });

    group("isNegative", [&] {
        test("Does not match positive numbers", [&] {
            EXPECT_MATCHER_FAILS(3, isNegative)
            EXPECT_MATCHER_FAILS(10, isNegative)
            EXPECT_MATCHER_FAILS(kLargeLongLongNumber, isNegative)
            EXPECT_MATCHER_FAILS(23u, isNegative)
            EXPECT_MATCHER_FAILS(35.03, isNegative)
            EXPECT_MATCHER_FAILS(3.503f, isNegative)
        });

        test("Does not match zero", [&] {
            EXPECT_MATCHER_FAILS(0, isNegative)
            EXPECT_MATCHER_FAILS(0.0, isNegative)
            EXPECT_MATCHER_FAILS(0LL, isNegative)
        });

        test("Matches negative numbers", [&] {
            EXPECT_MATCHER_MATCHES(-3, isNegative)
            EXPECT_MATCHER_MATCHES(-10, isNegative)
            EXPECT_MATCHER_MATCHES(-kLargeLongLongNumber, isNegative)
            EXPECT_MATCHER_MATCHES(-35.03, isNegative)
            EXPECT_MATCHER_MATCHES(-3.503f, isNegative)
        });
    });

    group("isEven", [&] {
        test("Matches even integers", [&] {
            EXPECT_MATCHER_MATCHES(2, isEven)
            EXPECT_MATCHER_MATCHES(0, isEven)
            EXPECT_MATCHER_MATCHES(-2, isEven)
            EXPECT_MATCHER_MATCHES(kLargeLongLongNumber, isEven)
            EXPECT_MATCHER_MATCHES(24u, isEven)
        });

        test("Does not match odd integers", [&] {
            EXPECT_MATCHER_FAILS(1, isEven)
            EXPECT_MATCHER_FAILS(13, isEven)
            EXPECT_MATCHER_FAILS(-7, isEven)
            EXPECT_MATCHER_FAILS(kLargeLongLongNumber - 1, isEven)
            EXPECT_MATCHER_FAILS(23u, isEven)
        });
    });

    group("isOdd", [&] {
        test("Does not match even integers", [&] {
            EXPECT_MATCHER_FAILS(2, isOdd)
            EXPECT_MATCHER_FAILS(0, isOdd)
            EXPECT_MATCHER_FAILS(-2, isOdd)
            EXPECT_MATCHER_FAILS(kLargeLongLongNumber, isOdd)
            EXPECT_MATCHER_FAILS(24u, isOdd)
        });

        test("Matches odd integers", [&] {
            EXPECT_MATCHER_MATCHES(1, isOdd)
            EXPECT_MATCHER_MATCHES(13, isOdd)
            EXPECT_MATCHER_MATCHES(-7, isOdd)
            EXPECT_MATCHER_MATCHES(kLargeLongLongNumber - 1, isOdd)
            EXPECT_MATCHER_MATCHES(23u, isOdd)
        });
    });

    group("isZero", [&] {
        test("Does not match positive numbers", [&] {
            EXPECT_MATCHER_FAILS(3, isZero)
            EXPECT_MATCHER_FAILS(10, isZero)
            EXPECT_MATCHER_FAILS(kLargeLongLongNumber, isZero)
            EXPECT_MATCHER_FAILS(23u, isZero)
            EXPECT_MATCHER_FAILS(35.03, isZero)
            EXPECT_MATCHER_FAILS(3.503f, isZero)
        });

        test("Matches zero", [&] {
            EXPECT_MATCHER_MATCHES(0, isZero)
            EXPECT_MATCHER_MATCHES(0.0, isZero)
            EXPECT_MATCHER_MATCHES(0LL, isZero)
        });

        test("Does not match negative numbers", [&] {
            EXPECT_MATCHER_FAILS(-3, isZero)
            EXPECT_MATCHER_FAILS(-10, isZero)
            EXPECT_MATCHER_FAILS(-kLargeLongLongNumber, isZero)
            EXPECT_MATCHER_FAILS(-35.03, isZero)
            EXPECT_MATCHER_FAILS(-3.503f, isZero)
        });
    });

    test("isAlmostEqualTo: Changing epsilon changes precision", [&] {
        EXPECT_MATCHER_MATCHES(3.05, isAlmostEqualTo(3.0, 0.1))
        EXPECT_MATCHER_MATCHES(4.99, isAlmostEqualTo(3.0, 2))
        EXPECT_MATCHER_FAILS(3 + 1e-9, isAlmostEqualTo(3.0, 1e-12))
    });
};
