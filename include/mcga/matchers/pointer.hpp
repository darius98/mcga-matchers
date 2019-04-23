#pragma once

#include "mcga/matchers/internal/pointer.hpp"

namespace mcga::matchers {

constexpr internal::IsNullptrMatcher isNull;

constexpr internal::IsNotNullptrMatcher isNotNull;

}  // namespace mcga::matchers
