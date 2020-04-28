#pragma once
#include "base.cpp"

template<class T>
T pow(T n, lli p) {
  if (p == 1)
    return n;
  if (p%2 == 1)
    return n*pow(n, p-1);
  T aux = pow(n, p/2);
  return aux*aux;
}

int log2(unsigned lli x) {
  return 8*sizeof(x)-1 - __builtin_clzll(x);
}


lli gcd(lli a, lli b) {
  return (a == 0 ? b : gcd(b%a, a));
}

