#include <map>
#include <tuple>
#include <unordered_map>

// TODO: this implementation has an additional O(log(n)) cost
//   due to the use of std::map instead of std::unordered_map or alternatives
template<class F, class... I, class O = typename std::result_of<F&&(I...)>::type>
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

