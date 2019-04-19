#pragma once

#include "mcga/matchers/detail/numeric.hpp"

namespace mcga::matchers {

constexpr detail::IsPositiveMatcher isPositive;

constexpr detail::IsNegativeMatcher isNegative;

constexpr detail::IsEvenMatcher isEven;

constexpr detail::IsOddMatcher isOdd;

constexpr detail::IsZeroMatcher isZero;

constexpr detail::IsNotZeroMatcher isNotZero;

template<class T>
constexpr auto isAlmostEqualTo(const T& target, const double& eps) {
    return detail::IsAlmostEqualMatcher(target, eps);
}

}  // namespace mcga::matchers
