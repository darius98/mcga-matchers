#pragma once

#include "../../../../../../../../Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX11.3.sdk/usr/include/c++/v1/type_traits"

#include "../../../../../../../../Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX11.3.sdk/usr/include/c++/v1/sstream"
#include "../../../../../../../../Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX11.3.sdk/usr/include/c++/v1/string"
#include "../../../../../../../../Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX11.3.sdk/usr/include/c++/v1/tuple"
#include "../../../../../../../../Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX11.3.sdk/usr/include/c++/v1/utility"

namespace mcga::matchers::tp {

namespace internal {

template<class T>
constexpr decltype(std::begin(std::declval<const T&>())) Begin();

template<class T>
constexpr decltype(std::begin(std::declval<const T&>())) End();

template<class T>
constexpr T& Ref(T);

template<class T>
decltype(Begin<T>() != End<T>(),
         ++Ref(Begin<T>()),
         *Begin<T>(),
         std::true_type())
  IsIterableImpl(int /*unused*/) {
    return std::true_type();
}

template<class T>
std::false_type IsIterableImpl(...) {
    return std::false_type();
}

template<class T>
struct IsPairImpl : std::false_type {};

template<class A, class B>
struct IsPairImpl<std::pair<A, B>> : std::true_type {};

template<class T>
struct IsTupleImpl : std::false_type {};

template<class... Items>
struct IsTupleImpl<std::tuple<Items...>> : std::true_type {};

template<class T>
decltype(Ref(std::declval<std::stringstream>()) << std::declval<T>(),
         std::true_type())
  IsSstreamableImpl(int /*unused*/) {
    return std::true_type();
}

template<class T>
std::false_type IsSstreamableImpl(...) {
    return std::false_type();
}

}  // namespace internal

template<class T>
constexpr bool IsStringLike
  = std::is_same_v<
      T,
      std::
        string> || std::is_same_v<T, std::string_view> || (std::is_pointer_v<T> && std::is_same_v<char, std::remove_pointer_t<T>>)
  || (std::is_array_v<T> && std::is_same_v<char, std::remove_all_extents_t<T>>);

template<class T>
constexpr bool IsIterable = decltype(internal::IsIterableImpl<T>(0))::value;

template<class T>
constexpr bool IsPair = internal::IsPairImpl<T>::value;

template<class T>
constexpr bool IsTuple = internal::IsTupleImpl<T>::value;

template<class T>
constexpr bool IsNullptrT = std::is_same_v<T, std::nullptr_t>;

template<class T>
constexpr bool IsSstreamable
  = decltype(internal::IsSstreamableImpl<T>(0))::value;

template<class S, std::size_t I = 0, class... Items>
typename std::enable_if_t<I == sizeof...(Items), void>
  StreamTuple(S& stream, const std::tuple<Items...>& t) {
}

template<class S, std::size_t I = 0, class... Items>
  typename std::enable_if_t < I<sizeof...(Items), void>
  StreamTuple(S& stream, const std::tuple<Items...>& t) {
    if (I != 0) {
        stream << ',';
    }
    stream << std::get<I>(t);
    StreamTuple<I + 1, Items...>(stream, t);
}

template<class From, class To>
concept convertible_to = std::is_convertible_v<From, To> && requires(
  std::add_rvalue_reference_t<From> (&f)()) {
    static_cast<To>(f());
};

template<class B>
concept helper_boolean_testable = convertible_to<B, bool>;

template<class B>
concept boolean_testable = helper_boolean_testable<B> && requires(B&& b) {
    { !std::forward<B>(b) } -> helper_boolean_testable;
};

}  // namespace mcga::matchers::tp
