#pragma once
#include <cxxabi.h>

#include <array>
#include <bitset>
#include <deque>
#include <forward_list>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template<typename T>
std::string typeof(const T& v) {
  int status;
  char* buffer = abi::__cxa_demangle(typeid(v).name(), NULL, NULL, &status);
  std::string name(buffer);
  free(buffer);
  return name;
}

#define LOG(v...) (std::cerr << __FILE__ << ":" << __LINE__ << ": " << typeof(v) << " " << #v << " == " << (v) << std::endl)

template<class T>
std::ostream& printContainer(std::ostream& os, const T& v) {
  bool first = true;
  for (const auto& i : v) {
    os << (first ? "{" : ", ") << i;
    first = false;
  }
  return os << '}' << std::flush;
}

#define MAKE_PRINT_CONTAINER(container) \
template<class...Ts>\
std::ostream& operator<< (std::ostream& os, const container<Ts...>& v) {\
  return printContainer(os, v);\
}
MAKE_PRINT_CONTAINER(std::vector);
MAKE_PRINT_CONTAINER(std::deque);
MAKE_PRINT_CONTAINER(std::forward_list);
MAKE_PRINT_CONTAINER(std::list);
MAKE_PRINT_CONTAINER(std::set);
MAKE_PRINT_CONTAINER(std::multiset);
MAKE_PRINT_CONTAINER(std::map);
MAKE_PRINT_CONTAINER(std::multimap);
MAKE_PRINT_CONTAINER(std::unordered_set);
MAKE_PRINT_CONTAINER(std::unordered_multiset);
MAKE_PRINT_CONTAINER(std::unordered_map);
MAKE_PRINT_CONTAINER(std::unordered_multimap);
MAKE_PRINT_CONTAINER(std::initializer_list);
template<class T, size_t N>
std::ostream& operator<< (std::ostream& os, const std::array<T, N>& v) {
  return printContainer(os, v);
}

template<size_t N>
std::ostream& operator<< (std::ostream& os, const std::bitset<N>& v) {
  return os << v.to_string();
}

template<int I, class T>
typename std::enable_if<std::tuple_size<T>::value == I,
  std::ostream&>::type printTuple(std::ostream& os, const T& v) {
  return os << '}' << std::flush;
}
template<int I=0, class T>
typename std::enable_if<(std::tuple_size<T>::value > I),
  std::ostream&>::type printTuple(std::ostream& os, const T& v) {
  os << (I==0 ? "{" : ", ") << std::get<I>(v);
  return printTuple<I+1>(os, v);
}

template<class...Ts>
std::ostream& operator<< (std::ostream& os, std::pair<Ts...> v) {
  return printTuple(os, v);
}
template<class...Ts>
std::ostream& operator<< (std::ostream& os, std::tuple<Ts...> v) {
  return printTuple(os, v);
}

