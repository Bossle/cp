#include "log.hpp"

int main() {
  FLOG(std::cout, 1.3);
  FLOG(std::cout, "hello");
  FLOG(std::cout, std::string("world"));
  FLOG(std::cout, std::vector<int>{1, 2, 3, 4});
  FLOG(std::cout, std::deque<int>{1, 2, 3, 4});
  FLOG(std::cout, std::forward_list<int>{1, 2, 3, 4});
  FLOG(std::cout, std::list<int>{1, 2, 3, 4});
  FLOG(std::cout, std::set<int>{1, 2, 3, 4});
  FLOG(std::cout, std::multiset<int>{1, 1, 2, 3});
  FLOG(std::cout, std::map<int, double>{{1, 1.1}, {2, 2.1}, {3, 3.1}, {4, 4}});
  FLOG(std::cout, std::multimap<int, double>{{1, 1.1}, {1, 2.1}, {2, 2.1}, {3, 3}});
  FLOG(std::cout, std::unordered_set<int>{1, 2, 3, 4});
  FLOG(std::cout, std::unordered_multiset<int>{1, 1, 2, 3});
  FLOG(std::cout, std::unordered_map<int, double>{{1, 1.1}, {2, 2.1}, {3, 3.1}, {4, 4}});
  FLOG(std::cout, std::unordered_multimap<int, double>{{1, 1.1}, {1, 2.1}, {2, 2.1}, {3, 3}});
  FLOG(std::cout, std::initializer_list<int>{1, 2, 3, 4});
  FLOG(std::cout, std::array<int, 5>{1, 2, 3, 4});
  FLOG(std::cout, std::bitset<100>("0100110"));
  FLOG(std::cout, std::pair<int, double>{3, 4.0});
  FLOG(std::cout, std::tuple<int, double, std::string>{2, 3.14, "test"});
}

