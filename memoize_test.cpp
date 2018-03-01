#include "memoize.hpp"

#include <functional>
#include <iostream>

int fibonacci(int n) {
  MEMOIZE(fibonacci, n);
  if (n<2)
    return n;
  return fibonacci(n-1)+fibonacci(n-2);
}

class fib {
 public:
  int operator() (int n) {
    MEMOIZE(*this, n);
    if (n<2)
      return n;
    return (*this)(n-1)+(*this)(n-2);
  }
};

int main() {
  std::function<int(int)> f = [&](int n) {
    MEMOIZE(f, n);
    if (n<2)
      return n;
    return f(n-1)+f(n-2);
  };
  for (int i=0; i<45; ++i)
    std::cout << fibonacci(i) << ' ' << fib()(i) << ' ' << f(i) << std::endl;
}

