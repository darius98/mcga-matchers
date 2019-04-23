#pragma once

#include "mcga/matchers/internal/string.hpp"

namespace mcga::matchers {

constexpr internal::CharInStringMatcher
  isLetter("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", "a letter");

constexpr internal::CharInStringMatcher isDigit("0123456789", "a digit");

constexpr internal::CharInStringMatcher
  isLowercaseLetter("abcdefghijklmnopqrstuvwxyz", "a lowercase letter");

constexpr internal::CharInStringMatcher
  isUppercaseLetter("ABCDEFGHIJKLMNOPQRSTUVWXYZ", "an uppercase letter");

constexpr internal::CharInStringMatcher isBinaryDigit("01", "a binary digit");

constexpr internal::CharInStringMatcher isOctDigit("01234567", "an oct digit");

constexpr internal::CharInStringMatcher isHexDigit("0123456789ABCDEFabcdef",
                                                   "a hex digit");

constexpr internal::CharInStringMatcher isWhitespace(" \t\r\n\f\v",
                                                     "a whitespace character");

inline internal::IsSubstringMatcher isSubstringOf(const std::string& s) {
    return internal::IsSubstringMatcher(s);
}

}  // namespace mcga::matchers
