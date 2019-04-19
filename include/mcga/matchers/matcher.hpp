#pragma once

#include "mcga/matchers/detail/type_helpers.hpp"

namespace mcga::matchers {

class Description {
  public:
    template<class T>
    Description& operator<<(const T& obj) {
        if constexpr (tp::IsStringLike<T>) {
            appendString(obj);
        } else if constexpr (tp::IsIterable<T>) {
            appendIterable(obj);
        } else if constexpr (tp::IsPair<T>) {
            appendPair(obj);
        } else if constexpr (tp::IsTuple<T>) {
            appendTuple(obj);
        } else if constexpr (tp::IsNullptrT<T>) {
            stream << static_cast<int*>(obj);
        } else if constexpr (tp::IsSstreamable<T>) {
            stream << obj;
        } else {
            stream << "[OBJECT]";
        }
        return *this;
    }

    Description& appendRawString(const std::string& str) {
        stream << str;
        return *this;
    }

    void appendString(std::string obj) {
        std::size_t pos = 0;
        while ((pos = obj.find('\n', pos)) != std::string::npos) {
            obj.replace(pos, 1, "\\n");
            pos += 2;
        }
        pos = 0;
        while ((pos = obj.find('\t', pos)) != std::string::npos) {
            obj.replace(pos, 1, "\\t");
            pos += 2;
        }
        pos = 0;
        while ((pos = obj.find('\r', pos)) != std::string::npos) {
            obj.replace(pos, 1, "\\r");
            pos += 2;
        }
        stream << obj;
    }

    template<class T>
    void appendIterable(const T& obj) {
        stream << '[';
        bool first = true;
        for (const auto& item: obj) {
            if (first) {
                first = false;
            } else {
                stream << ',';
            }
            *this << item;
        }
        stream << ']';
    }

    template<class A, class B>
    void appendPair(const std::pair<A, B>& p) {
        stream << '(';
        (*this) << p.first;
        stream << ", ";
        (*this) << p.second;
        stream << ')';
    }

    template<class... Items>
    void appendTuple(const std::tuple<Items...>& t) {
        stream << '(';
        tp::StreamTuple(*this, t);
        stream << ')';
    }

    std::string toString() const {
        return stream.str();
    }

  private:
    std::stringstream stream;
};

struct Matcher {};

}  // namespace mcga::matchers
