#pragma once

#include "mcga/matchers/matcher.hpp"

namespace mcga::matchers {

namespace internal {

template<class O, class T>
concept eq_comparable_with = requires(const T& t, const O& o) {
    { o == t } -> tp::boolean_testable;
    { o != t } -> tp::boolean_testable;
    { t == o } -> tp::boolean_testable;
    { t != o } -> tp::boolean_testable;
};

template<class O, class T>
concept comparable_with
  = eq_comparable_with<O, T> && requires(const T& t, const O& o) {
    { o < t } -> tp::boolean_testable;
    { o <= t } -> tp::boolean_testable;
    { o > t } -> tp::boolean_testable;
    { o >= t } -> tp::boolean_testable;
    { t < o } -> tp::boolean_testable;
    { t <= o } -> tp::boolean_testable;
    { t > o } -> tp::boolean_testable;
    { t >= o } -> tp::boolean_testable;
};

}  // namespace internal

template<class T>
struct EqualityMatcher {
    explicit constexpr EqualityMatcher(const T& target): target(target) {
    }

    template<internal::eq_comparable_with<T> O>
    bool matches(const O& obj) {
        return obj == target;
    }

    void describe(Description* description) const {
        (*description) << "'" << target << "'";
    }

    void describeFailure(Description* description) const {
        (*description) << "not '" << target << "'";
    }

  private:
    const T& target;
};

template<class Val, class T>
concept EqualityMatchableFor
  = !matchers::Matcher<
      Val> && matchers::MatcherFor<matchers::EqualityMatcher<Val>, T>;

template<class T>
struct NonEqualityMatcher {
    explicit constexpr NonEqualityMatcher(const T& target): target(target) {
    }

    template<internal::eq_comparable_with<T> O>
    bool matches(const O& obj) const {
        return obj != target;
    }

    void describe(Description* description) const {
        (*description) << "not '" << target << "'";
    }

    void describeFailure(Description* description) const {
        (*description) << "'" << target << "'";
    }

  private:
    const T& target;
};

template<class T>
struct IsLessThanMatcher {
    explicit constexpr IsLessThanMatcher(const T& target): target(target) {
    }

    template<internal::comparable_with<T> O>
    bool matches(const O& object) {
        return object < target;
    }

    void describe(Description* description) const {
        (*description) << "< '" << target << "'";
    }

    void describeFailure(Description* description) const {
        (*description) << ">= '" << target << "'";
    }

  private:
    const T& target;
};

template<class T>
struct IsLessThanEqualMatcher {
    explicit constexpr IsLessThanEqualMatcher(const T& target): target(target) {
    }

    template<internal::comparable_with<T> O>
    bool matches(const O& object) {
        return object <= target;
    }

    void describe(Description* description) const {
        (*description) << "<= '" << target << "'";
    }

    void describeFailure(Description* description) const {
        (*description) << "> '" << target << "'";
    }

  private:
    const T& target;
};

template<class T>
struct IsGreaterThanMatcher {
    explicit constexpr IsGreaterThanMatcher(const T& target): target(target) {
    }

    template<internal::comparable_with<T> O>
    bool matches(const O& object) {
        return object > target;
    }

    void describe(Description* description) const {
        (*description) << "> '" << target << "'";
    }

    void describeFailure(Description* description) const {
        (*description) << "<= '" << target << "'";
    }

  private:
    const T& target;
};

template<class T>
struct IsGreaterThanEqualMatcher {
    explicit constexpr IsGreaterThanEqualMatcher(const T& target)
            : target(target) {
    }

    template<internal::comparable_with<T> O>
    bool matches(const O& object) {
        return object >= target;
    }

    void describe(Description* description) const {
        (*description) << ">= '" << target << "'";
    }

    void describeFailure(Description* description) const {
        (*description) << "< '" << target << "'";
    }

  private:
    const T& target;
};

template<class T>
struct IdentityMatcher {
    explicit constexpr IdentityMatcher(const T& target)
            : address(static_cast<const void*>(&target)) {
    }

    template<class S>
    bool matches(const S& object) {
        obj = &object;
        return &object == address;
    }

    void describe(Description* description) const {
        (*description) << "variable at address '" << address << "'";
    }

    void describeFailure(Description* description) const {
        (*description) << "variable at address '"
                       << static_cast<const int*>(obj) << "'";
    }

  private:
    const void* obj = nullptr;
    const void* address;
};

constexpr const std::size_t relevantRange = 20;

template<>
struct EqualityMatcher<std::string> {
    explicit EqualityMatcher(std::string target): target(std::move(target)) {
    }

    bool matches(const std::string& object) {
        obj = object;
        return obj == target;
    }

    bool matches(const char* object) {
        obj = object;
        return obj == target;
    }

    void describe(Description* description) const {
        (*description) << "'" << target << "'";
    }

    void describeFailure(Description* description) const {
        std::size_t mismatchIndex = 0;
        while (mismatchIndex < std::min(target.size(), obj.size())
               && target[mismatchIndex] == obj[mismatchIndex]) {
            mismatchIndex += 1;
        }

        // number of spaces we must place the mismatch caret to the right:
        std::size_t numSpaces = std::string("Expected: '").length()
          + std::min(mismatchIndex, relevantRange);
        if (mismatchIndex > relevantRange) {
            numSpaces += 3;
        }
        // TODO(darius98): There is a problem with the design here: we need to
        //             count how many characters will be changed by the Streamer
        //             implementation to be represented here by two characters
        //             (so we know where to position the mismatch caret).
        //             This class should not be inter-dependent with the
        //             implementation of Streamer.
        for (std::size_t index = mismatchIndex >= relevantRange
               ? mismatchIndex - relevantRange
               : 0;
             index < mismatchIndex;
             ++index) {
            if (target[index] == '\n' || target[index] == '\r'
                || target[index] == '\t') {
                numSpaces += 1;
            }
        }

        (*description) << "different at index " << mismatchIndex << ":";
        description->appendRawString("\n\tExpected: '");
        (*description) << extractRelevantSection(target, mismatchIndex);
        description->appendRawString("'\n\t     Got: '");
        (*description) << extractRelevantSection(obj, mismatchIndex);
        description->appendRawString("'\n\t" + std::string(numSpaces, ' ')
                                     + "^");
    }

    template<std::size_t n>
    operator EqualityMatcher<char[n]>() const;  // NOLINT

  protected:
    std::string obj;
    std::string target;

  private:
    static std::string extractRelevantSection(const std::string& s,
                                              const std::size_t index) {
        auto firstIndex = index >= relevantRange ? index - relevantRange : 0;
        auto lastIndex = std::min(index + relevantRange, s.size() - 1);
        auto relevantSection = s.substr(firstIndex, lastIndex - firstIndex + 1);

        if (index + relevantRange + 1 < s.size()) {
            relevantSection += "...";
        }
        if (index > relevantRange) {
            relevantSection = "..." + relevantSection;
        }
        return relevantSection;
    }
};

template<std::size_t n>
struct EqualityMatcher<char[n]> : EqualityMatcher<std::string> {
    using EqualityMatcher<std::string>::EqualityMatcher;
};

template<std::size_t n>
EqualityMatcher<std::string>::operator EqualityMatcher<char[n]>() const {
    return EqualityMatcher<char[n]>(target);
}

template<>
struct NonEqualityMatcher<std::string> {
    explicit NonEqualityMatcher(std::string target): target(std::move(target)) {
    }

    bool matches(const std::string& obj) const {
        return obj != target;
    }

    bool matches(const char* obj) const {
        return obj != target;
    }

    void describe(Description* description) const {
        (*description) << "not '" << target << "'";
    }

    void describeFailure(Description* description) const {
        (*description) << "'" << target << "'";
    }

    template<std::size_t n>
    operator NonEqualityMatcher<char[n]>() const;  // NOLINT

  protected:
    std::string target;
};

template<std::size_t n>
struct NonEqualityMatcher<char[n]> : NonEqualityMatcher<std::string> {
    using NonEqualityMatcher<std::string>::NonEqualityMatcher;
};

template<std::size_t n>
NonEqualityMatcher<std::string>::operator NonEqualityMatcher<char[n]>() const {
    return EqualityMatcher<char[n]>(target);
}

template<>
struct IsLessThanMatcher<std::string> {
    explicit IsLessThanMatcher(std::string target): target(std::move(target)) {
    }

    bool matches(const std::string& obj) const {
        return obj < target;
    }

    bool matches(const char* obj) const {
        return obj < target;
    }

    void describe(Description* description) const {
        (*description) << "< '" << target << "'";
    }

    void describeFailure(Description* description) const {
        (*description) << ">= '" << target << "'";
    }

    template<std::size_t n>
    operator IsLessThanMatcher<char[n]>() const;  // NOLINT

  protected:
    std::string target;
};

template<std::size_t n>
struct IsLessThanMatcher<char[n]> : IsLessThanMatcher<std::string> {
    using IsLessThanMatcher<std::string>::IsLessThanMatcher;
};

template<std::size_t n>
IsLessThanMatcher<std::string>::operator IsLessThanMatcher<char[n]>() const {
    return IsLessThanMatcher<char[n]>(target);
}

template<>
struct IsLessThanEqualMatcher<std::string> {
    explicit IsLessThanEqualMatcher(std::string target)
            : target(std::move(target)) {
    }

    bool matches(const std::string& obj) const {
        return obj <= target;
    }

    bool matches(const char* obj) const {
        return obj <= target;
    }

    void describe(Description* description) const {
        (*description) << "<= '" << target << "'";
    }

    void describeFailure(Description* description) const {
        (*description) << "> '" << target << "'";
    }

    template<std::size_t n>
    operator IsLessThanEqualMatcher<char[n]>() const;  // NOLINT

  protected:
    std::string target;
};

template<std::size_t n>
struct IsLessThanEqualMatcher<char[n]> : IsLessThanEqualMatcher<std::string> {
    using IsLessThanEqualMatcher<std::string>::IsLessThanEqualMatcher;
};

template<std::size_t n>
IsLessThanEqualMatcher<std::string>::operator IsLessThanEqualMatcher<char[n]>()
  const {
    return IsLessThanEqualMatcher<char[n]>(target);
}

template<>
struct IsGreaterThanMatcher<std::string> {
    explicit IsGreaterThanMatcher(std::string target)
            : target(std::move(target)) {
    }

    bool matches(const std::string& obj) const {
        return obj > target;
    }

    bool matches(const char* obj) const {
        return std::string(obj) > target;
    }

    void describe(Description* description) const {
        (*description) << "> '" << target << "'";
    }

    void describeFailure(Description* description) const {
        (*description) << "<= '" << target << "'";
    }

    template<std::size_t n>
    operator IsGreaterThanMatcher<char[n]>() const;  // NOLINT

  protected:
    std::string target;
};

template<std::size_t n>
struct IsGreaterThanMatcher<char[n]> : IsGreaterThanMatcher<std::string> {
    using IsGreaterThanMatcher<std::string>::IsGreaterThanMatcher;
};

template<std::size_t n>
IsGreaterThanMatcher<std::string>::operator IsGreaterThanMatcher<char[n]>()
  const {
    return IsGreaterThanMatcher<char[n]>(target);
}

template<>
struct IsGreaterThanEqualMatcher<std::string> {
    explicit IsGreaterThanEqualMatcher(std::string target)
            : target(std::move(target)) {
    }

    bool matches(const std::string& obj) const {
        return obj >= target;
    }

    bool matches(const char* obj) const {
        return obj >= target;
    }

    void describe(Description* description) const {
        (*description) << ">= '" << target << "'";
    }

    void describeFailure(Description* description) const {
        (*description) << "< '" << target << "'";
    }

    template<std::size_t n>
    operator IsGreaterThanEqualMatcher<char[n]>() const;  // NOLINT

  protected:
    std::string target;
};

template<std::size_t n>
struct IsGreaterThanEqualMatcher<char[n]>
        : IsGreaterThanEqualMatcher<std::string> {
    using IsGreaterThanEqualMatcher<std::string>::IsGreaterThanEqualMatcher;
};

template<std::size_t n>
IsGreaterThanEqualMatcher<std::string>::operator IsGreaterThanEqualMatcher<
  char[n]>() const {
    return IsGreaterThanEqualMatcher<char[n]>(target);
}

template<class T>
constexpr auto isEqualTo(const T& object) {
    return EqualityMatcher<T>(object);
}

template<class T>
constexpr auto isNotEqualTo(const T& object) {
    return NonEqualityMatcher<T>(object);
}

template<class T>
constexpr auto isLessThan(const T& object) {
    return IsLessThanMatcher<T>(object);
}

template<class T>
constexpr auto isLessThanEqual(const T& object) {
    return IsLessThanEqualMatcher<T>(object);
}

template<class T>
constexpr auto isGreaterThan(const T& object) {
    return IsGreaterThanMatcher<T>(object);
}

template<class T>
constexpr auto isGreaterThanEqual(const T& object) {
    return IsGreaterThanEqualMatcher<T>(object);
}

template<class T>
constexpr auto isIdenticalTo(const T& object) {
    return IdentityMatcher<T>(object);
}

}  // namespace mcga::matchers
