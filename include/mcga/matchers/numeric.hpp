#pragma once

#include "mcga/matchers/matcher.hpp"

namespace mcga::matchers {

struct IsPositiveMatcher {
    template<class T>
    bool matches(const T& object) const {
        return object > 0;
    }

    void describe(Description* description) const {
        (*description) << "a positive number";
    }

    void describeFailure(Description* description) const {
        (*description) << "non-positive";
    }
};

struct IsNegativeMatcher {
    template<class T>
    bool matches(const T& object) const {
        return object < 0;
    }

    void describe(Description* description) const {
        (*description) << "a negative number";
    }

    void describeFailure(Description* description) const {
        (*description) << "non-negative";
    }
};

struct IsEvenMatcher {
    template<class T>
    bool matches(const T& object) const {
        return object % 2 == 0;
    }

    void describe(Description* description) const {
        (*description) << "an even number";
    }

    void describeFailure(Description* description) const {
        (*description) << "odd";
    }
};

struct IsOddMatcher {
    template<class T>
    bool matches(const T& object) const {
        return object % 2 == 1 || object % 2 == -1;
    }

    void describe(Description* description) const {
        (*description) << "an odd number";
    }

    void describeFailure(Description* description) const {
        (*description) << "even";
    }
};

struct IsZeroMatcher {
    template<class T>
    bool matches(const T& object) const {
        return object == 0;
    }

    void describe(Description* description) const {
        (*description) << "zero";
    }

    void describeFailure(Description* description) const {
        (*description) << "non-zero";
    }
};

struct IsNotZeroMatcher {
    template<class T>
    bool matches(const T& object) const {
        return object != 0;
    }

    void describe(Description* description) const {
        (*description) << "non-zero";
    }

    void describeFailure(Description* description) const {
        (*description) << "zero";
    }
};

template<class T>
struct IsAlmostEqualMatcher {
    constexpr IsAlmostEqualMatcher(const T& target, const double& eps)
            : target(target), eps(eps) {
    }

    bool matches(const T& object) const {
        T delta = object - target;
        return -eps < delta && delta < eps;
    }

    void describe(Description* description) const {
        (*description) << "a number within " << eps << " of " << target;
    }

    void describeFailure(Description* description) const {
        (*description) << "a number not within " << eps << " of " << target;
    }

  private:
    const T& target;
    double eps;
};

constexpr IsPositiveMatcher isPositive;

constexpr IsNegativeMatcher isNegative;

constexpr IsEvenMatcher isEven;

constexpr IsOddMatcher isOdd;

constexpr IsZeroMatcher isZero;

constexpr IsNotZeroMatcher isNotZero;

template<class T>
constexpr auto isAlmostEqualTo(const T& target, const double& eps) {
    return IsAlmostEqualMatcher(target, eps);
}

}  // namespace mcga::matchers
