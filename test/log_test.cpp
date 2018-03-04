#include "log.hpp"

int main() {
  LOG(1.3);
  LOG("hello");
  LOG(std::string("world"));
  LOG(std::vector<int>{1, 2, 3, 4});
  LOG(std::deque<int>{1, 2, 3, 4});
  LOG(std::forward_list<int>{1, 2, 3, 4});
  LOG(std::list<int>{1, 2, 3, 4});
  LOG(std::set<int>{1, 2, 3, 4});
  LOG(std::multiset<int>{1, 1, 2, 3});
  LOG(std::map<int, double>{{1, 1.1}, {2, 2.1}, {3, 3.1}, {4, 4}});
  LOG(std::multimap<int, double>{{1, 1.1}, {1, 2.1}, {2, 2.1}, {3, 3}});
  LOG(std::unordered_set<int>{1, 2, 3, 4});
  LOG(std::unordered_multiset<int>{1, 1, 2, 3});
  LOG(std::unordered_map<int, double>{{1, 1.1}, {2, 2.1}, {3, 3.1}, {4, 4}});
  LOG(std::unordered_multimap<int, double>{{1, 1.1}, {1, 2.1}, {2, 2.1}, {3, 3}});
  LOG(std::initializer_list<int>{1, 2, 3, 4});
  LOG(std::array<int, 5>{1, 2, 3, 4});
  LOG(std::bitset<100>("0100110"));
  LOG(std::pair<int, double>{3, 4.0});
  LOG(std::tuple<int, double, std::string>{2, 3.14, "test"});
}
