#pragma once

#include <functional>

#include "mcga/matchers/matcher.hpp"

namespace mcga::matchers {

struct ThrowsAnythingMatcher {
    bool matches(const std::function<void()>& func) const {
        try {
            func();
            return false;
        } catch (...) {
            return true;
        }
    }

    void describe(Description* description) const {
        (*description) << "a function that throws";
    }

    void describeFailure(Description* description) const {
        (*description) << "a function that did not throw";
    }
};

template<class E>
struct ThrowsSpecificMatcher {
    bool matches(const std::function<void()>& func) {
        try {
            func();
            state = DOESNT_THROW;
            return false;
        } catch (const E& exception) {
            state = THROWS_CORRECTLY;
            return true;
        } catch (...) {
            state = THROWS_DIFFERENT;
            return false;
        }
    }

    void describe(Description* description) const {
        (*description) << "a function that throws " << typeid(E).name();
    }

    void describeFailure(Description* description) const {
        if (state == DOESNT_THROW) {
            (*description) << "a function that did not throw";
        }
        if (state == THROWS_DIFFERENT) {
            (*description) << "a function that throws something else";
        }
    }

  private:
    enum {
        THROWS_CORRECTLY,
        DOESNT_THROW,
        THROWS_DIFFERENT,
    } state;
};

template<class E>
constexpr auto throwsA() {
    return ThrowsSpecificMatcher<E>();
}

constexpr ThrowsAnythingMatcher throws;

}  // namespace mcga::matchers
