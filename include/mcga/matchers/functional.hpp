#pragma once

#include "mcga/matchers/internal/functional.hpp"

namespace mcga::matchers {

template<class E>
constexpr internal::ThrowsSpecificMatcher<E> throwsA() {
    return internal::ThrowsSpecificMatcher<E>();
}

constexpr internal::ThrowsAnythingMatcher throws;

}  // namespace mcga::matchers
