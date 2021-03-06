#pragma once

#include "mcga/matchers/comparison.hpp"

namespace mcga::matchers::internal {

struct IsEmptyMatcher : Matcher {
    template<class T>
    bool matches(const T& object) const {
        return object.empty();
    }

    void describe(Description* description) const {
        (*description) << "empty iterable";
    }

    void describeFailure(Description* description) const {
        (*description) << "a non-empty iterable";
    }
};

struct IsNotEmptyMatcher : Matcher {
    template<class T>
    bool matches(const T& object) const {
        return !object.empty();
    }

    void describe(Description* description) const {
        (*description) << "non-empty iterable";
    }

    void describeFailure(Description* description) const {
        (*description) << "empty iterable";
    }
};

template<class M>
struct IterableSizeMatcher : Matcher {
    explicit constexpr IterableSizeMatcher(M sizeMatcher)
            : sizeMatcher(std::move(sizeMatcher)) {
    }

    template<class T>
    bool matches(const T& obj) {
        return sizeMatcher.matches(obj.size());
    }

    void describe(Description* description) const {
        (*description) << "iterable where size is ";
        sizeMatcher.describe(description);
    }

    void describeFailure(Description* description) const {
        (*description) << "iterable where size is ";
        sizeMatcher.describeFailure(description);
    }

  private:
    M sizeMatcher;
};

template<class M>
struct IterableEachMatcher : Matcher {
    explicit constexpr IterableEachMatcher(M elementMatcher)
            : elementMatcher(std::move(elementMatcher)) {
    }

    template<class T>
    bool matches(const T& iterable) {
        index = -1;
        for (const auto& obj: iterable) {
            index += 1;
            if (!elementMatcher.matches(obj)) {
                return false;
            }
        }
        return true;
    }

    void describe(Description* description) const {
        (*description) << "an iterable where each element is ";
        elementMatcher.describe(description);
    }

    void describeFailure(Description* description) const {
        (*description) << "an iterable where at index " << index
                       << " the element is ";
        elementMatcher.describeFailure(description);
    }

  private:
    int index = -1;
    M elementMatcher;
};

template<class M>
struct IterableAnyMatcher : Matcher {
    explicit constexpr IterableAnyMatcher(M elementMatcher)
            : elementMatcher(std::move(elementMatcher)) {
    }

    template<class T>
    bool matches(const T& iterable) {
        for (const auto& obj: iterable) {
            if (elementMatcher.matches(obj)) {
                return true;
            }
        }
        return false;
    }

    void describe(Description* description) const {
        (*description) << "an iterable where at least one element is ";
        elementMatcher.describe(description);
    }

    void describeFailure(Description* description) const {
        (*description) << "an iterable where no element is ";
        elementMatcher.describe(description);
    }

  private:
    M elementMatcher;
};

}  // namespace mcga::matchers::internal
