#pragma once

#include "mcga/matchers/internal/composite.hpp"

namespace mcga::matchers {

template<class A, class B>
constexpr auto both(const A& a, const B& b) {
    if constexpr (isMatcher<A>) {
        if constexpr (isMatcher<B>) {
            return internal::AndMatcher(a, b);
        } else {
            return internal::AndMatcher(a, isEqualTo(b));
        }
    } else {
        if constexpr (isMatcher<B>) {
            return internal::AndMatcher(isEqualTo(a), b);
        } else {
            return internal::AndMatcher(isEqualTo(a), isEqualTo(b));
        }
    }
}

template<class A, class B>
constexpr auto either(const A& a, const B& b) {
    if constexpr (isMatcher<A>) {
        if constexpr (isMatcher<B>) {
            return internal::OrMatcher(a, b);
        } else {
            return internal::OrMatcher(a, isEqualTo(b));
        }
    } else {
        if constexpr (isMatcher<B>) {
            return internal::OrMatcher(isEqualTo(a), b);
        } else {
            return internal::OrMatcher(isEqualTo(a), isEqualTo(b));
        }
    }
}

template<class T>
constexpr auto isNot(const T& x) {
    if constexpr (isMatcher<T>) {
        return internal::NotMatcher<T>(x);
    } else {
        return internal::NotMatcher(isEqualTo(x));
    }
}

}  // namespace mcga::matchers
