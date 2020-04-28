#pragma once
#include "math/base.cpp"

// invMod(a, b)*a + invMod(b, a)*b = gcd(a, b) = g
// ranges from -(b/g-1) to b/g-1
lli invMod(lli a, lli b) {
  lli c = 1, d = 0;
  while (a != 0)
    tie(a, b, c, d) = tie(b%a, a, d-c*(b/a), c);
  return d;  // also b contains the gcd of the input
}

lli normalizeMod(lli v, lli N) {
  return ((v%N)+N)%N;
}

// requires a%gcd(N, M) == b%gcd(N, M)
// solveCRT(a, N, b, M) % N == a
// solveCRT(a, N, b, M) == solveCRT(b, M, a, N)
// ranges from 0 to N*M/gcd(N, M)
// pass gcd(N, M) as g if already known, to make this O(1)
lli solveCRT(lli a, lli N, lli b, lli M, lli g) {
  assert(gcd(N, M) == g);
  return a + N * normalizeMod((b-a%M)/g * invMod(N/g, M/g), M/g));
}
lli solveCRT(lli a, lli N, lli b, lli M) {
  lli g = gcd(N, M);
  assert(a%g == b%g);
  return solveCRT(a, N, b, M, g);
}


/* Use with the following for static modulo N:
class Mod : public DynMod {
 public:
  Mod(lli v) : DynMod(v, N) {}
}
 * or with the following for dynamic modulo:
typedef DynMod Mod
*/
class DynMod {
 public:
  DynMod(lli v, lli N) : v(normalizeMod(v, N)), N(N) {}
  DynMod(const DynMod& rhs) = default;
  DynMod& operator=(const DynMod& rhs) = default;
  
  DynMod& operator=(lli _v) { v = _v; return *this; }

  explicit operator lli() const { return v; }

  lli mod() const { return N; }

  // Opinion: operators should not change N
  DynMod operator+(lli rhs) const { return DynMod(v + rhs, N); }
  DynMod operator-(lli rhs) const { return DynMod(v - rhs, N); }
  DynMod operator*(lli rhs) const { return DynMod(v * (rhs%N), N); }
  DynMod operator/(lli rhs) const { assert(gcd(rhs, N) == 1); return *this * invMod(rhs, N); }
  DynMod& operator+=(lli rhs) { return *this = *this + rhs; }
  DynMod& operator-=(lli rhs) { return *this = *this - rhs; }
  DynMod& operator*=(lli rhs) { return *this = *this * rhs; }
  DynMod& operator/=(lli rhs) { return *this = *this / rhs; }
  bool operator==(lli rhs) const { return v == normalizeMod(rhs, N); }
  bool operator!=(lli rhs) const { return v != normalizeMod(rhs, N); }
  DynMod operator+() const { return *this; }
  DynMod operator-() const { return DynMod(-v, N); }
  DynMod& operator++() { return *this += 1; }
  DynMod& operator--() { return *this -= 1; }
  DynMod operator++(int) { DynMod ans = *this; *this += 1; return ans; }
  DynMod operator--(int) { DynMod ans = *this; *this -= 1; return ans; }
  DynMod operator+(const DynMod& rhs) const { assert(N == rhs.N); return *this + (rhs.v); }
  DynMod operator-(const DynMod& rhs) const { assert(N == rhs.N); return *this - (rhs.v); }
  DynMod operator*(const DynMod& rhs) const { assert(N == rhs.N); return *this * (rhs.v); }
  DynMod operator/(const DynMod& rhs) const { assert(N == rhs.N); return *this / (rhs.v); }
  DynMod& operator+=(const DynMod& rhs) { assert(N == rhs.N); return *this += (rhs.v); }
  DynMod& operator-=(const DynMod& rhs) { assert(N == rhs.N); return *this -= (rhs.v); }
  DynMod& operator*=(const DynMod& rhs) { assert(N == rhs.N); return *this *= (rhs.v); }
  DynMod& operator/=(const DynMod& rhs) { assert(N == rhs.N); return *this /= (rhs.v); }
  bool operator==(const DynMod& rhs) const { assert(N == rhs.N); return v == rhs.v; }
  bool operator!=(const DynMod& rhs) const { assert(N == rhs.N); return v != rhs.v; }
 private:
  lli N;
  lli v;  // ranges from 0 to N-1
};
DynMod operator+(lli lhs, const DynMod& rhs) { return DynMod(lhs, r.mod()) + (lli)rhs; }
DynMod operator-(lli lhs, const DynMod& rhs) { return DynMod(lhs, r.mod()) - (lli)rhs; }
DynMod operator*(lli lhs, const DynMod& rhs) { return DynMod(lhs, r.mod()) * (lli)rhs; }
DynMod operator/(lli lhs, const DynMod& rhs) { return DynMod(lhs, r.mod()) / (lli)rhs; }

DynMod solveCRT(const DynMod& a, const DynMod& b) {
  return DynMod(solveCRT((lli)a, a.mod(), (lli)b, b.mod()), a.mod()*(b.mod()/gcd(a.mod(), b.mod())));
}

