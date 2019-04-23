#pragma once

#include <stdexcept>

#include "mcga/test_ext/matchers.hpp"

// Helpers for testing the matchers themselves.

#define EXPECT_MATCHER_FAILS(...)                                              \
    {                                                                          \
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
    }

#define EXPECT_MATCHER_MATCHES(...)                                            \
    {                                                                          \
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
    }
