#pragma once

#include "mcga/matchers/matcher.hpp"

namespace mcga::matchers::detail {

struct IsNullptrMatcher : Matcher {
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

struct IsNotNullptrMatcher : Matcher {
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

}  // namespace mcga::matchers::detail
