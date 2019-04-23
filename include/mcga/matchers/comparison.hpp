#pragma once

#include "mcga/matchers/internal/comparison.hpp"

namespace mcga::matchers {

template<class T>
constexpr auto isEqualTo(const T& object) {
    return internal::EqualityMatcher<T>(object);
}

template<class T>
constexpr auto isNotEqualTo(const T& object) {
    return internal::NonEqualityMatcher<T>(object);
}

template<class T>
constexpr auto isLessThan(const T& object) {
    return internal::IsLessThanMatcher<T>(object);
}

template<class T>
constexpr auto isLessThanEqual(const T& object) {
    return internal::IsLessThanEqualMatcher<T>(object);
}

template<class T>
constexpr auto isGreaterThan(const T& object) {
    return internal::IsGreaterThanMatcher<T>(object);
}

template<class T>
constexpr auto isGreaterThanEqual(const T& object) {
    return internal::IsGreaterThanEqualMatcher<T>(object);
}

template<class T>
constexpr auto isIdenticalTo(const T& object) {
    return internal::IdentityMatcher<T>(object);
}

}  // namespace mcga::matchers
