#pragma once

#include "mcga/matchers/internal/numeric.hpp"

namespace mcga::matchers {

constexpr internal::IsPositiveMatcher isPositive;

constexpr internal::IsNegativeMatcher isNegative;

constexpr internal::IsEvenMatcher isEven;

constexpr internal::IsOddMatcher isOdd;

constexpr internal::IsZeroMatcher isZero;

constexpr internal::IsNotZeroMatcher isNotZero;

template<class T>
constexpr auto isAlmostEqualTo(const T& target, const double& eps) {
    return internal::IsAlmostEqualMatcher(target, eps);
}

}  // namespace mcga::matchers
