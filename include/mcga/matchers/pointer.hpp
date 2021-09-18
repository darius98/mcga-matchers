#pragma once

#include "mcga/matchers/matcher.hpp"

namespace mcga::matchers {

struct IsNullptrMatcher {
    bool matches(void* const& obj) const {
        return obj == nullptr;
    }

    void describe(Description* description) const {
        (*description) << "nullptr";
    }

    void describeFailure(Description* description) const {
        (*description) << "non-null pointer";
    }
};

struct IsNotNullptrMatcher {
    bool matches(void* const& obj) const {
        return obj != nullptr;
    }

    void describe(Description* description) const {
        (*description) << "non-null pointer";
    }

    void describeFailure(Description* description) const {
        (*description) << "nullptr";
    }
};

constexpr IsNullptrMatcher isNull;

constexpr IsNotNullptrMatcher isNotNull;

}  // namespace mcga::matchers
