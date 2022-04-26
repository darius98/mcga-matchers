#pragma once

#include "mcga/matchers/comparison.hpp"

namespace mcga::matchers {

struct IsEmptyMatcher {
    template<class T>
    requires requires(T object) {
        { object.empty() } -> tp::boolean_testable;
    }
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

struct IsNotEmptyMatcher {
    template<class T>
    requires requires(const T& object) {
        { object.empty() } -> tp::boolean_testable;
    }
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

template<Matcher M>
struct IterableSizeMatcher {
    explicit constexpr IterableSizeMatcher(M sizeMatcher)
            : sizeMatcher(std::move(sizeMatcher)) {
    }

    template<class T>
    requires requires(const T& object) {
        { object.size() } -> IsMatchableBy<M>;
    }
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
struct IterableEachMatcher {
    explicit constexpr IterableEachMatcher(M elementMatcher)
            : elementMatcher(std::move(elementMatcher)) {
    }

    template<class T>
    requires requires(const T& object) {
        { *object.begin() } -> IsMatchableBy<M>;
    }
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
struct IterableAnyMatcher {
    explicit constexpr IterableAnyMatcher(M elementMatcher)
            : elementMatcher(std::move(elementMatcher)) {
    }

    template<class T>
    requires requires(const T& object) {
        { *object.begin() } -> IsMatchableBy<M>;
    }
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

template<class T>
constexpr auto hasSize(const T& size) {
    if constexpr (Matcher<T>) {
        return IterableSizeMatcher<T>(size);
    } else {
        return IterableSizeMatcher(isEqualTo(static_cast<std::size_t>(size)));
    }
}

template<class T>
constexpr auto eachElement(const T& each) {
    if constexpr (Matcher<T>) {
        return IterableEachMatcher<T>(each);
    } else {
        return IterableEachMatcher(isEqualTo(each));
    }
}

template<class T>
constexpr auto anyElement(const T& any) {
    if constexpr (Matcher<T>) {
        return IterableAnyMatcher<T>(any);
    } else {
        return IterableAnyMatcher(isEqualTo(any));
    }
}

constexpr IsEmptyMatcher isEmpty;

constexpr IsNotEmptyMatcher isNotEmpty;

}  // namespace mcga::matchers
