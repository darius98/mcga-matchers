#pragma once

#include <stdexcept>

#include "mcga/test_ext/matchers.hpp"

// Helpers for testing the matchers themselves.

#define EXPECT_MATCHER_FAILS(...)                                              \
    do {                                                                       \
        bool failed;                                                           \
        try {                                                                  \
            mcga::test::expect(__VA_ARGS__);                                   \
            failed = false;                                                    \
        } catch (const std::exception&) {                                      \
            failed = true;                                                     \
        }                                                                      \
        if (!failed) {                                                         \
            mcga::test::fail("expect(" #__VA_ARGS__ ") did not fail!");        \
        }                                                                      \
    } while (false)

#define EXPECT_MATCHER_MATCHES(...)                                            \
    do {                                                                       \
        bool failed;                                                           \
        try {                                                                  \
            mcga::test::expect(__VA_ARGS__);                                   \
            failed = false;                                                    \
        } catch (const std::exception&) {                                      \
            failed = true;                                                     \
        }                                                                      \
        if (failed) {                                                          \
            mcga::test::fail("expect(" #__VA_ARGS__ ") failed!");              \
        }                                                                      \
    } while (false)
