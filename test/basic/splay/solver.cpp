#include "splay.hpp"

int main() {
  libossle::Splay<int> s;
  s.insert(s.begin(), libossle::Splay<int>(1)) += 1;
}
