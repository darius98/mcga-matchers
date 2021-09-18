#include <vector>

#include "mcga/test.hpp"

#include "mcga/matchers/comparison.hpp"
#include "mcga/matchers/testing_helpers.hpp"

using mcga::matchers::isEqualTo;
using mcga::matchers::isGreaterThan;
using mcga::matchers::isGreaterThanEqual;
using mcga::matchers::isIdenticalTo;
using mcga::matchers::isLessThan;
using mcga::matchers::isLessThanEqual;
using mcga::matchers::isNotEqualTo;
using mcga::test::expect;
using mcga::test::fail;
using mcga::test::group;
using mcga::test::test;

TEST_CASE(comparison, "Matchers::comparison") {
    group("Equality", [&] {
        test("isEqualTo matches equal values", [&] {
            EXPECT_MATCHER_MATCHES(3, isEqualTo(3))
            EXPECT_MATCHER_MATCHES(std::vector<int>{1, 2},
                                   isEqualTo(std::vector<int>{1, 2}))
            EXPECT_MATCHER_MATCHES("abc", isEqualTo("abc"))
            EXPECT_MATCHER_MATCHES("abc", isEqualTo(std::string("abc")))
            EXPECT_MATCHER_MATCHES(std::string("abc"), isEqualTo("abc"))
            EXPECT_MATCHER_MATCHES(std::string("abc"),
                                   isEqualTo(std::string("abc")))
            EXPECT_MATCHER_MATCHES(std::vector<int>{1, 2},
                                   isEqualTo(std::vector<int>{1, 2}))
        });

        test("isEqualTo fails for different integer values", [&] {
            try {
                expect(3, isEqualTo(2));
                fail("did not fail!");
            } catch (const std::exception& exc) {
                expect(std::string(exc.what())
                       == "Expected '2'\n"
                          "Got      '3'\n"
                          "Which is not '2'");
            }
        });

        test("isEqualTo fails for different string values", [&] {
            try {
                expect("Hello, World!", isEqualTo("Hello, world!"));
                fail("did not fail!");
            } catch (const std::exception& exc) {
                expect(std::string(exc.what())
                       == "Expected 'Hello, world!'\n"
                          "Got      'Hello, World!'\n"
                          "Which is different at index 7:\n"
                          "\tExpected: 'Hello, world!'\n"
                          "\t     Got: 'Hello, World!'\n"
                          "\t                  ^");
            }
        });

        // weird formatting, but good for readability in the case of this test.
        test("isEqualTo description for longer strings", [&] {
            try {
                expect(
                  "This is a long text that differs at a large position",
                  isEqualTo(
                    "This is a long text that differs at a laRge position"));
                fail("did not fail!");
            } catch (const std::exception& exc) {
                expect(std::string(exc.what())
                       == "Expected 'This is a long text that differs at a "
                          "laRge position'\n"
                          "Got      'This is a long text that differs at a "
                          "large position'\n"
                          "Which is different at index 40:\n"
                          "\tExpected: '...that differs at a laRge position'\n"
                          "\t     Got: '...that differs at a large position'\n"
                          "\t                                  ^");
            }

            try {
                expect(
                  "This is a long text that differs at a small position",
                  isEqualTo(
                    "This is a long tExt that differs at a small position"));
                fail("did not fail!");
            } catch (const std::exception& exc) {
                expect(
                  std::string(exc.what())
                  == "Expected 'This is a long tExt that differs at a small "
                     "position'\n"
                     "Got      'This is a long text that differs at a small "
                     "position'\n"
                     "Which is different at index 16:\n"
                     "\tExpected: 'This is a long tExt that differs at a...'\n"
                     "\t     Got: 'This is a long text that differs at a...'\n"
                     "\t                           ^");
            }

            try {
                expect("This is a very very very very long text that differs "
                       "at a medium-placed position",
                       isEqualTo("This is a very very very very long teXt that "
                                 "differs at a medium-placed position"));
                fail("did not fail!");
            } catch (const std::exception& exc) {
                expect(std::string(exc.what())
                       == "Expected 'This is a very very very very long teXt "
                          "that differs at a medium-placed position'\n"
                          "Got      'This is a very very very very long text "
                          "that differs at a medium-placed position'\n"
                          "Which is different at index 37:\n"
                          "\tExpected: '...ry very very long teXt that differs "
                          "at a ...'\n"
                          "\t     Got: '...ry very very long text that differs "
                          "at a ...'\n"
                          "\t                                  ^");
            }
        });

        test("isNotEqualTo matches different values", [&] {
            EXPECT_MATCHER_MATCHES(2, isNotEqualTo(3))
            EXPECT_MATCHER_MATCHES(std::vector<int>{2, 3},
                                   isNotEqualTo(std::vector<int>{1, 3}))
            EXPECT_MATCHER_MATCHES("abc", isNotEqualTo("abd"))
            EXPECT_MATCHER_MATCHES("abc", isNotEqualTo(std::string("abd")))
            EXPECT_MATCHER_MATCHES(std::string("abc"), isNotEqualTo("abd"))
            EXPECT_MATCHER_MATCHES(std::string("abc"),
                                   isNotEqualTo(std::string("abd")))
        });

        test("isNotEqualTo does not match equal values", [&] {
            EXPECT_MATCHER_FAILS(3, isNotEqualTo(3))
            EXPECT_MATCHER_FAILS(std::vector<int>{1, 2},
                                 isNotEqualTo(std::vector<int>{1, 2}))
        });
    });

    group("Identity", [&] {
        test("isIdenticalTo matches identical variables", [&] {
            int x = 4;
            EXPECT_MATCHER_MATCHES(x, isIdenticalTo(x))
        });

        test("isIdenticalTo fails for equal values", [&] {
            int x = 3, y = 3;
            EXPECT_MATCHER_FAILS(y, isIdenticalTo(x))
        });

        test("isIdenticalTo fails for different values", [&] {
            int x = 3, y = 4;
            EXPECT_MATCHER_FAILS(y, isIdenticalTo(x))
        });
    });

    group("Less than", [&] {
        test("isLessThan matches smaller values", [&] {
            EXPECT_MATCHER_MATCHES(3, isLessThan(5))
            EXPECT_MATCHER_MATCHES(-20, isLessThan(17))
            EXPECT_MATCHER_MATCHES('a', isLessThan('c'))
            EXPECT_MATCHER_MATCHES("abra", isLessThan(std::string("cadabra")))
            EXPECT_MATCHER_MATCHES("abra", isLessThan("cadabra"))
            EXPECT_MATCHER_MATCHES(std::string("abra"), isLessThan("cadabra"))
            EXPECT_MATCHER_MATCHES(std::vector<int>{1, 2, 3},
                                   isLessThan(std::vector<int>{2, 1, 3}))
        });

        test("isLessThan does not match equal values", [&] {
            EXPECT_MATCHER_FAILS(3, isLessThan(3))
            EXPECT_MATCHER_FAILS(-17, isLessThan(-17))
            EXPECT_MATCHER_FAILS('c', isLessThan('c'))
            EXPECT_MATCHER_FAILS("cadabra", isLessThan(std::string("cadabra")))
            EXPECT_MATCHER_FAILS(std::vector<int>{2, 1, 3},
                                 isLessThan(std::vector<int>{2, 1, 3}))
        });

        test("isLessThan does not match greater values", [&] {
            EXPECT_MATCHER_FAILS(5, isLessThan(3))
            EXPECT_MATCHER_FAILS(17, isLessThan(-20))
            EXPECT_MATCHER_FAILS('c', isLessThan('a'))
            EXPECT_MATCHER_FAILS("cadabra", isLessThan(std::string("abra")))
            EXPECT_MATCHER_FAILS(std::vector<int>{2, 1, 3},
                                 isLessThan(std::vector<int>{1, 2, 3}))
        });
    });

    group("Less than or equal to", [&] {
        test("isLessThanEqual matches smaller values", [&] {
            EXPECT_MATCHER_MATCHES(3, isLessThanEqual(5))
            EXPECT_MATCHER_MATCHES(-20, isLessThanEqual(17))
            EXPECT_MATCHER_MATCHES('a', isLessThanEqual('c'))
            EXPECT_MATCHER_MATCHES("abra", isLessThanEqual(std::string("cada")))
            EXPECT_MATCHER_MATCHES("abra", isLessThanEqual("cada"))
            EXPECT_MATCHER_MATCHES(std::string("abra"), isLessThanEqual("cada"))
            EXPECT_MATCHER_MATCHES(std::vector<int>{1, 2, 3},
                                   isLessThanEqual(std::vector<int>{2, 1, 3}))
        });

        test("isLessThanEqual matches equal values", [&] {
            EXPECT_MATCHER_MATCHES(3, isLessThanEqual(3))
            EXPECT_MATCHER_MATCHES(-17, isLessThanEqual(-17))
            EXPECT_MATCHER_MATCHES('c', isLessThanEqual('c'))
            EXPECT_MATCHER_MATCHES("cada", isLessThanEqual(std::string("cada")))
            EXPECT_MATCHER_MATCHES(std::vector<int>{2, 1, 3},
                                   isLessThanEqual(std::vector<int>{2, 1, 3}))
        });

        test("isLessThanEqual does not match greater values", [&] {
            EXPECT_MATCHER_FAILS(5, isLessThanEqual(3))
            EXPECT_MATCHER_FAILS(17, isLessThanEqual(-20))
            EXPECT_MATCHER_FAILS('c', isLessThanEqual('a'))
            EXPECT_MATCHER_FAILS("cada", isLessThanEqual(std::string("abra")))
            EXPECT_MATCHER_FAILS(std::vector<int>{2, 1},
                                 isLessThanEqual(std::vector<int>{1, 2}))
        });
    });

    group("Greater than", [&] {
        test("isGreaterThan does not match smaller values", [&] {
            EXPECT_MATCHER_FAILS(3, isGreaterThan(5))
            EXPECT_MATCHER_FAILS(-20, isGreaterThan(17))
            EXPECT_MATCHER_FAILS('a', isGreaterThan('c'))
            EXPECT_MATCHER_FAILS("abra", isGreaterThan(std::string("cadabra")))
            EXPECT_MATCHER_FAILS(std::string("abra"), isGreaterThan("cadabra"))
            EXPECT_MATCHER_FAILS("abra", isGreaterThan("cadabra"))
            EXPECT_MATCHER_FAILS(std::vector<int>{1, 2},
                                 isGreaterThan(std::vector<int>{2, 1}))
        });

        test("isGreaterThan does not match equal values", [&] {
            EXPECT_MATCHER_FAILS(3, isGreaterThan(3))
            EXPECT_MATCHER_FAILS(-17, isGreaterThan(-17))
            EXPECT_MATCHER_FAILS('c', isGreaterThan('c'))
            EXPECT_MATCHER_FAILS("cadabra",
                                 isGreaterThan(std::string("cadabra")))
            EXPECT_MATCHER_FAILS(std::vector<int>{2, 1},
                                 isGreaterThan(std::vector<int>{2, 1}))
        });

        test("isGreaterThan matches greater values", [&] {
            EXPECT_MATCHER_MATCHES(5, isGreaterThan(3))
            EXPECT_MATCHER_MATCHES(17, isGreaterThan(-20))
            EXPECT_MATCHER_MATCHES('c', isGreaterThan('a'))
            EXPECT_MATCHER_MATCHES("cadabra",
                                   isGreaterThan(std::string("abra")))
            EXPECT_MATCHER_MATCHES(std::vector<int>{2, 1, 3},
                                   isGreaterThan(std::vector<int>{1, 2, 3}))
        });
    });

    group("Greater than or equal to", [&] {
        test("isGreaterThanEqual does not match smaller values", [&] {
            EXPECT_MATCHER_FAILS(3, isGreaterThanEqual(5))
            EXPECT_MATCHER_FAILS(-20, isGreaterThanEqual(17))
            EXPECT_MATCHER_FAILS('a', isGreaterThanEqual('c'))
            EXPECT_MATCHER_FAILS("abra",
                                 isGreaterThanEqual(std::string("cada")))
            EXPECT_MATCHER_FAILS(std::string("abra"),
                                 isGreaterThanEqual("cada"))
            EXPECT_MATCHER_FAILS("abra", isGreaterThanEqual("cada"))
            EXPECT_MATCHER_FAILS(std::vector<int>{1, 2},
                                 isGreaterThanEqual(std::vector<int>{2, 1}))
        });

        test("isGreaterThanEqual matches equal values", [&] {
            EXPECT_MATCHER_MATCHES(3, isGreaterThanEqual(3))
            EXPECT_MATCHER_MATCHES(-17, isGreaterThanEqual(-17))
            EXPECT_MATCHER_MATCHES('c', isGreaterThanEqual('c'))
            EXPECT_MATCHER_MATCHES("cada",
                                   isGreaterThanEqual(std::string("cada")))
            EXPECT_MATCHER_MATCHES(std::vector<int>{2, 1},
                                   isGreaterThanEqual(std::vector<int>{2, 1}))
        });

        test("isGreaterThanEqual matches greater values", [&] {
            EXPECT_MATCHER_MATCHES(5, isGreaterThanEqual(3))
            EXPECT_MATCHER_MATCHES(17, isGreaterThanEqual(-20))
            EXPECT_MATCHER_MATCHES('c', isGreaterThanEqual('a'))
            EXPECT_MATCHER_MATCHES("cada",
                                   isGreaterThanEqual(std::string("abra")))
            EXPECT_MATCHER_MATCHES(std::vector<int>{2, 1},
                                   isGreaterThanEqual(std::vector<int>{1, 2}))
        });
    });
}
