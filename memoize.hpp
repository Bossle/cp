#pragma once
#include <map>
#include <tuple>
#include <type_traits>
#include <unordered_map>

// memoize(f, args) takes a function f and its args
// returns std::pair(isValid, f(args))
// complexity: O(1) if the function was called before with the same args,
//   the same as f(args) otherwise
// TODO: this implementation has an additional O(log(n)) cost
//   due to the use of std::map instead of std::unordered_map or alternatives
template<typename F, typename... I, typename O = typename std::result_of<F&&(I&&...)>::type>
std::pair<bool, O> memoize(F& f, I... args) {
  using Key = std::tuple<I...>;
  using Val = std::pair<bool, O>;
  static std::unordered_map<F*, std::map<Key, Val>> allMemos;
  auto& memo = allMemos[&f];
  Key key(args...);
  auto inserted = memo.emplace(key, Val());
  Val& val = inserted.first->second;
  if (inserted.second) {
    val.first = false;
    val.second = f(args...);
    val.first = true;
  }
  return val;
}

// Usage: call MEMOIZE(func, args) at the start of the implementation of func(args)
// Then subsequent calls to func with the same args will have complexity O(1)
#define MEMOIZE(func, args...) {\
  auto p = memoize(func, args);\
  if (p.first)\
    return p.second;\
}

