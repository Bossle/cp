#pragma once

#ifndef CP_DEBUG
#define LOG(x)
#else

#include <cxxabi.h>

// LOG logs x into stderr
// This includes value, name, type and location
#define LOG(x) (cerr << __FILE__ << ":" << __LINE__ << ": " << cp_log::demangledType(x) << " " << #x << " == " << (x) << std::endl)


namespace cp_log {

// demangledType is a more human-readable alternative to typeid's name()
template<class T>
std::string demangledType(const T& v){
  int status;
  char* buffer = abi::__cxa_demangle(typeid(v).name(), NULL, NULL, &status);
  std::string name(buffer);
  free(buffer);
  return name;
}

// logContainer logs an initializer list-like representation of container
// Requires container to implement begin() and end()
template<typename T>
std::ostream& logContainer(std::ostream& os, const T& container) {
  bool first = true;
  for (const auto& elem : container) {
    os << (first ? "{" : ", ") << elem;
    first = false;
  }
  return os << '}' << std::flush;
}

// logTuple logs an initializer list-like representation of tup
// Requires tup to implement basic std::tuple functions
template<int I, class T>
typename std::enable_if<I == std::tuple_size<T>::value,
std::ostream&>::type logTuple(std::ostream& os, const T&) {
  return os << '}' << std::flush;
}
template<int I = 0, class T>
typename std::enable_if<(I < std::tuple_size<T>::value),
std::ostream&>::type logTuple(std::ostream& os, const T& tup) {
  os << (I==0 ? "{" : ", ") << std::get<I>(tup);
  return logTuple<I+1>(os, tup);
}

}  // namespace cp_log

// Overloads for operator<< (std::ostream&, const std::container&)
// These allow LOG to work on all STL container types
template<class T, std::size_t N>
std::ostream& operator<< (std::ostream& os, const std::array<T, N>& c) {
  return cp_log::logContainer(os, c);
}

template<std::size_t N>
std::ostream& operator<< (std::ostream& os, const std::bitset<N>& b) {
  return os << b.to_string() << std::flush;
}

template<class...T>
std::ostream& operator<< (std::ostream& os, const std::deque<T...>& c) {
  return cp_log::logContainer(os, c);
}

template<class...T>
std::ostream& operator<< (std::ostream& os, const std::forward_list<T...>& c) {
  return cp_log::logContainer(os, c);
}

template<class...T>
std::ostream& operator<< (std::ostream& os, const std::initializer_list<T...>& c) {
  return cp_log::logContainer(os, c);
}

template<class...T>
std::ostream& operator<< (std::ostream& os, const std::list<T...>& c) {
  return cp_log::logContainer(os, c);
}

template<class...T>
std::ostream& operator<< (std::ostream& os, const std::map<T...>& c) {
  return cp_log::logContainer(os, c);
}

template<class...T>
std::ostream& operator<< (std::ostream& os, const std::multimap<T...>& c) {
  return cp_log::logContainer(os, c);
}

template<class...T>
std::ostream& operator<< (std::ostream& os, const std::multiset<T...>& c) {
  return cp_log::logContainer(os, c);
}

template<class...T>
std::ostream& operator<< (std::ostream& os, const std::pair<T...>& tup) {
  return cp_log::logTuple(os, tup);
}

template<class...T>
std::ostream& operator<< (std::ostream& os, const std::set<T...>& c) {
  return cp_log::logContainer(os, c);
}

template<class...T>
std::ostream& operator<< (std::ostream& os, const std::tuple<T...>& tup) {
  return cp_log::logTuple(os, tup);
}

template<class...T>
std::ostream& operator<< (std::ostream& os, const std::unordered_map<T...>& c) {
  return cp_log::logContainer(os, c);
}

template<class...T>
std::ostream& operator<< (std::ostream& os, const std::unordered_multimap<T...>& c) {
  return cp_log::logContainer(os, c);
}

template<class...T>
std::ostream& operator<< (std::ostream& os, const std::unordered_multiset<T...>& c) {
  return cp_log::logContainer(os, c);
}

template<class...T>
std::ostream& operator<< (std::ostream& os, const std::unordered_set<T...>& c) {
  return cp_log::logContainer(os, c);
}

template<class...T>
std::ostream& operator<< (std::ostream& os, const std::vector<T...>& c) {
  return cp_log::logContainer(os, c);
}

#endif
