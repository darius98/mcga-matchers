#pragma once

#include "mcga/matchers/matcher.hpp"

namespace mcga::matchers::internal {

struct IsTrueMatcher : Matcher {
    bool matches(const bool& object) const {
        return object;
    }

    void describe(Description* description) const {
        (*description) << "true";
    }

    void describeFailure(Description* description) const {
        (*description) << "false";
    }
};

struct IsFalseMatcher : Matcher {
    bool matches(const bool& object) const {
        return !object;
    }

    void describe(Description* description) const {
        (*description) << "false";
    }

    void describeFailure(Description* description) const {
        (*description) << "true";
    }
};

}  // namespace mcga::matchers::internal
