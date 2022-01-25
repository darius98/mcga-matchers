#pragma once

#include "mcga/test.hpp"
#include "mcga/test_ext/matchers.hpp"

// Helpers for testing the matchers themselves.

#define EXPECT_MATCHER_FAILS(...)                                              \
    do {                                                                       \
        bool FAILURE_STATE = false;                                            \
        ::mcga::test::String ERROR_MESSAGE;                                    \
        ::mcga::test::internal::expectMatches(                                 \
          [&](::mcga::test::String failMessage,                                \
              ::mcga::test::Context failContext) {                             \
              FAILURE_STATE = true;                                            \
              ERROR_MESSAGE = ::mcga::test::internal::move(failMessage);       \
          },                                                                   \
          __VA_ARGS__);                                                        \
        if (!FAILURE_STATE) {                                                  \
            ::mcga::test::fail("expect(" #__VA_ARGS__ ") did not fail!");      \
        }                                                                      \
    } while (false)

#define EXPECT_MATCHER_FAILS_WITH_MESSAGE(rawExpectedErrorMsg, ...)            \
    do {                                                                       \
        const auto EXPECTED_ERROR_MSG = std::string(rawExpectedErrorMsg);      \
        bool FAILURE_STATE = false;                                            \
        ::mcga::test::String ERROR_MESSAGE;                                    \
        ::mcga::test::internal::expectMatches(                                 \
          [&](::mcga::test::String failMessage,                                \
              ::mcga::test::Context failContext) {                             \
              FAILURE_STATE = true;                                            \
              ERROR_MESSAGE = ::mcga::test::internal::move(failMessage);       \
          },                                                                   \
          __VA_ARGS__);                                                        \
        if (!FAILURE_STATE) {                                                  \
            ::mcga::test::fail("expect(" #__VA_ARGS__ ") did not fail!");      \
        } else if (EXPECTED_ERROR_MSG != ERROR_MESSAGE.c_str()) {              \
            ::mcga::test::fail("expect(" #__VA_ARGS__                          \
                               ") wrong error ERROR_MESSAGE: \"\"\""           \
                               + EXPECTED_ERROR_MSG + "\"\"\"");               \
        }                                                                      \
    } while (false)

#define EXPECT_MATCHER_MATCHES(...)                                            \
    do {                                                                       \
        bool FAILURE_STATE = false;                                            \
        ::mcga::test::String ERROR_MESSAGE;                                    \
        ::mcga::test::internal::expectMatches(                                 \
          [&](::mcga::test::String failMessage,                                \
              ::mcga::test::Context failContext) {                             \
              FAILURE_STATE = true;                                            \
              ERROR_MESSAGE = ::mcga::test::internal::move(failMessage);       \
          },                                                                   \
          __VA_ARGS__);                                                        \
        if (FAILURE_STATE) {                                                   \
            ::mcga::test::fail("expect(" #__VA_ARGS__ ") failed!");            \
        }                                                                      \
    } while (false)
