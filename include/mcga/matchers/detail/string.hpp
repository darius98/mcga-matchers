#pragma once

#include <cstring>

#include <string>

#include "mcga/matchers/matcher.hpp"

namespace mcga::matchers::detail {

struct CharInStringMatcher : StatelessMatcher {
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

struct IsSubstringMatcher : StatelessMatcher {
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

}  // namespace mcga::matchers::detail
