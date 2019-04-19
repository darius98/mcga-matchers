#pragma once

#include "mcga/matchers/comparison.hpp"

namespace mcga::matchers::detail {

template<class M1, class M2>
struct AndMatcher : Matcher {
    constexpr AndMatcher(M1 m1, M2 m2): m1(std::move(m1)), m2(std::move(m2)) {
    }

    template<class T>
    bool matches(const T& obj) {
        m1Matches = m1.matches(obj);
        m2Matches = m2.matches(obj);
        return m1Matches && m2Matches;
    }

    void describe(Description* description) const {
        m1.describe(description);
        (*description) << " and ";
        m2.describe(description);
    }

    void describeFailure(Description* description) const {
        if (m1Matches) {
            m2.describeFailure(description);
        } else {
            m1.describeFailure(description);
        }
    }

  private:
    bool m1Matches = false;
    M1 m1;

    bool m2Matches = false;
    M2 m2;
};

template<class M1, class M2>
struct OrMatcher : Matcher {
    constexpr OrMatcher(M1 m1, M2 m2): m1(std::move(m1)), m2(std::move(m2)) {
    }

    template<class T>
    bool matches(const T& obj) {
        m1Matches = m1.matches(obj);
        m2Matches = m2.matches(obj);
        return m1Matches || m2Matches;
    }

    void describe(Description* description) const {
        m1.describe(description);
        (*description) << " or ";
        m2.describe(description);
    }

    void describeFailure(Description* description) const {
        m1.describeFailure(description);
        (*description) << " and ";
        m2.describeFailure(description);
    }

  private:
    bool m1Matches = false;
    M1 m1;

    bool m2Matches = false;
    M2 m2;
};

template<class M>
struct NotMatcher : Matcher {
    constexpr explicit NotMatcher(M matcher): matcher(std::move(matcher)) {
    }

    template<class T>
    bool matches(const T& obj) {
        return !matcher.matches(obj);
    }

    void describe(Description* description) const {
        (*description) << "not ";
        matcher.describe(description);
    }

    void describeFailure(Description* description) const {
        matcher.describe(description);
    }

  private:
    M matcher;
};

}