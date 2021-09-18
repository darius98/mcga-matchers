#pragma once

#include "mcga/matchers/matcher.hpp"

namespace mcga::matchers {

struct IsTrueMatcher {
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

struct IsFalseMatcher {
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

constexpr IsTrueMatcher isTrue;

constexpr IsFalseMatcher isFalse;

}  // namespace mcga::matchers
