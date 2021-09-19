#include "mcga/test.hpp"

#include "mcga/matchers/testing_helpers.hpp"
#include "mcga/matchers/truth.hpp"

using mcga::matchers::isFalse;
using mcga::matchers::isTrue;
using mcga::test::test;

TEST_CASE("Matchers::truth") {
    test("isTrue matcher matches true",
         [] { EXPECT_MATCHER_MATCHES(true, isTrue) });

    test("isTrue matcher does not match false",
         [] { EXPECT_MATCHER_FAILS(false, isTrue) });

    test("isFalse matcher does not match true",
         [] { EXPECT_MATCHER_FAILS(true, isFalse) });

    test("isFalse matcher matches false",
         [] { EXPECT_MATCHER_MATCHES(false, isFalse) });
}
