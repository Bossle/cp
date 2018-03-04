#pragma once
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

// LOG logs its parameter into cerr
// This includes value, name, type and location
// Use LOG({value1, value2, ...}) to log multiple values at once
#define LOG(...) (std::cerr << __FILE__ << ":" << __LINE__ << ": " << typeof(__VA_ARGS__) << " " << #__VA_ARGS__ << " == " << (__VA_ARGS__) << std::endl)

// typeof is a more human-readable alternative to typeid's name()
template<class T>
std::string typeof(const T&);

// Overloads for operator<< (std::ostream&, const std::container&)
// These allow LOG to work on all STL container types

template<class T, int N>
std::ostream& operator<< (std::ostream&, const std::array<T, N>&);

template<int N>
std::ostream& operator<< (std::ostream&, const std::bitset<N>&);

template<class...T>
std::ostream& operator<< (std::ostream&, const std::deque<T...>&);

template<class...T>
std::ostream& operator<< (std::ostream&, const std::forward_list<T...>&);

template<class...T>
std::ostream& operator<< (std::ostream&, const std::initializer_list<T...>&);

template<class...T>
std::ostream& operator<< (std::ostream&, const std::list<T...>&);

template<class...T>
std::ostream& operator<< (std::ostream&, const std::map<T...>&);

template<class...T>
std::ostream& operator<< (std::ostream&, const std::multimap<T...>&);

template<class...T>
std::ostream& operator<< (std::ostream&, const std::multiset<T...>&);

template<class...T>
std::ostream& operator<< (std::ostream&, const std::pair<T...>&);

template<class...T>
std::ostream& operator<< (std::ostream&, const std::set<T...>&);

template<class...T>
std::ostream& operator<< (std::ostream&, const std::tuple<T...>&);

template<class...T>
std::ostream& operator<< (std::ostream&, const std::unordered_map<T...>&);

template<class...T>
std::ostream& operator<< (std::ostream&, const std::unordered_multimap<T...>&);

template<class...T>
std::ostream& operator<< (std::ostream&, const std::unordered_multiset<T...>&);

template<class...T>
std::ostream& operator<< (std::ostream&, const std::unordered_set<T...>&);

template<class...T>
std::ostream& operator<< (std::ostream&, const std::vector<T...>&);

#include "log_impl.hpp"

