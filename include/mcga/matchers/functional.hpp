#pragma once

#include "mcga/matchers/detail/functional.hpp"

namespace mcga::matchers {

template<class E>
constexpr detail::ThrowsSpecificMatcher<E> throwsA() {
    return detail::ThrowsSpecificMatcher<E>();
}

constexpr detail::ThrowsAnythingMatcher throws;

}  // namespace mcga::matchers
