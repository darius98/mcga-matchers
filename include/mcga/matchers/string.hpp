#pragma once

#include <cstring>

#include <string>

#include "mcga/matchers/matcher.hpp"

namespace mcga::matchers {

struct CharInStringMatcher {
    constexpr CharInStringMatcher(const char* container,
                                  const char* expectation)
            : container(container), expectation(expectation) {
    }

    bool matches(const char& ch) const {
        return strchr(container, ch) != nullptr;
    }

    void describe(Description* description) const {
        if (expectation != nullptr) {
            (*description) << expectation;
        } else {
            (*description) << "character in '" << container << "'";
        }
    }

    void describeFailure(Description* description) const {
        if (expectation != nullptr) {
            (*description) << "not " << expectation;
        } else {
            (*description) << "character that is not in '" << container << "'";
        }
    }

  private:
    const char* container;
    const char* expectation;
};

struct IsSubstringMatcher {
  public:
    explicit IsSubstringMatcher(std::string container)
            : container(std::move(container)) {
    }

    bool matches(const std::string& object) const {
        return container.find(object) != std::string::npos;
    }

    void describe(Description* description) const {
        (*description) << "a substring of '" << container << "'";
    }

    void describeFailure(Description* description) const {
        (*description) << "not a substring";
    }

  private:
    std::string container;
};

constexpr CharInStringMatcher
  isLetter("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", "a letter");

constexpr CharInStringMatcher isDigit("0123456789", "a digit");

constexpr CharInStringMatcher isLowercaseLetter("abcdefghijklmnopqrstuvwxyz",
                                                "a lowercase letter");

constexpr CharInStringMatcher isUppercaseLetter("ABCDEFGHIJKLMNOPQRSTUVWXYZ",
                                                "an uppercase letter");

constexpr CharInStringMatcher isBinaryDigit("01", "a binary digit");

constexpr CharInStringMatcher isOctDigit("01234567", "an oct digit");

constexpr CharInStringMatcher isHexDigit("0123456789ABCDEFabcdef",
                                         "a hex digit");

constexpr CharInStringMatcher isWhitespace(" \t\r\n\f\v",
                                           "a whitespace character");

inline auto isSubstringOf(const std::string& s) {
    return IsSubstringMatcher(s);
}

}  // namespace mcga::matchers
