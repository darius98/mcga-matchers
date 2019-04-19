#pragma once

#include <stdexcept>

#include "mcga/test_ext/matchers.hpp"

// Helpers for testing the matchers themselves.

#define EXPECT_MATCHER_FAILS(...)                                              \
    try {                                                                      \
        mcga::test::expect(__VA_ARGS__);                                       \
        fail("expect(" #__VA_ARGS__ ") did not fail!");                        \
    } catch (const std::exception&) {                                          \
    }

#define EXPECT_MATCHER_MATCHES(...)                                            \
    try {                                                                      \
        mcga::test::expect(__VA_ARGS__);                                       \
    } catch (const std::exception&) {                                          \
        fail("expect(" #__VA_ARGS__ ") failed!");                              \
    }
