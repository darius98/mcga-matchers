#pragma once

#include "mcga/matchers/detail/pointer.hpp"

namespace mcga::matchers {

constexpr detail::IsNullptrMatcher isNull;

constexpr detail::IsNotNullptrMatcher isNotNull;

}  // namespace mcga::matchers
