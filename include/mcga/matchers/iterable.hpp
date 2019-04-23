#pragma once

#include "mcga/matchers/internal/iterable.hpp"

namespace mcga::matchers {

template<class T>
constexpr auto hasSize(const T& size) {
    if constexpr (std::is_base_of_v<Matcher, T>) {
        return internal::IterableSizeMatcher<T>(size);
    } else {
        return internal::IterableSizeMatcher(isEqualTo(size));
    }
}

template<class T>
constexpr auto eachElement(const T& each) {
    if constexpr (std::is_base_of_v<Matcher, T>) {
        return internal::IterableEachMatcher<T>(each);
    } else {
        return internal::IterableEachMatcher(isEqualTo(each));
    }
}

template<class T>
constexpr auto anyElement(const T& any) {
    if constexpr (std::is_base_of_v<Matcher, T>) {
        return internal::IterableAnyMatcher<T>(any);
    } else {
        return internal::IterableAnyMatcher(isEqualTo(any));
    }
}

constexpr internal::IsEmptyMatcher isEmpty;

constexpr internal::IsNotEmptyMatcher isNotEmpty;

}  // namespace mcga::matchers
