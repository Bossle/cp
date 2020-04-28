#pragma once
#include "math/base.cpp"
#include "math/mod.cpp"

namespace cp_ntt {

// requirements:
//   all v[i].mod() are the same, mod,
//   v.size() is a power of 2,
//   v.size() divides mod-1,
//   mod is a prime,
//   pRoot is a primitive root
void NTT(vector<DynMod>& v, DynMod pRoot) {
  DynMod w = pow(pRoot, (mod-1)/v.size());
  for (int i = 0, j = 0; i < v.size(); ++i, j ^= v.size() - v.size()/2/(i&-i))
    if (i < j)
      swap(v[i], v[j]);
  vector<DynMod> powRoot(v.size());
  powRoot[0] = 1;
  for (int i=0; i+1 < v.size(); ++i)
    powRoot[i+1] = (powRoot[i]*w)%mod;
  for (int l=0; 1<<l < v.size(); ++l) {
    int pd = v.size()>>(l+1);
    for (int i=0; i < v.size(); i += 2<<l)
      for (int j=0, p=0; j < 1<<l; ++j, p+=pd) {
        int j2 = i + j + (1<<l);
        lli b = v[i+j], d = (v[j2]*powRoot[p])%mod;
        v[i+j] = (b+d)%mod;
        v[j2] = (b-d)%mod;
      }
  }
}

const vector<DynMod> BaseRoot{
  DynMod(31, (15<<27)+1),
  DynMod(13, (27<<26)+1),
  DynMod(3, (7<<26)+1)
};

template<class T>
vector<vector<DynMod>> allNTT(vector<T> v, int minSize, const vector<DynMod>& roots) {
  lli n = 2<<log2(minSize);
  vector<vector<DynMod>> result;
  for (DynMod root : roots) {
    vector<DynMod> r(n, DynMod(0, root.mod()));
    for (int i=0; i<v.size(); ++i)
      r[i] = (lli)v[i];
    NTT(r, root);
    result.push_back(r);
  }
  return r;
}

DynMod solveBaseCRT(DynMod base0, DynMod base1, DynMod base2, lli mod) {
  // adaptation of (solveCRT of base0, base1, base2)%mod avoiding overflow
  const DynMod aux = solveCRT(base0, baseRes1);
  return (lli)aux + DynMod(aux.mod(), mod) * (lli)((base2 - (lli)aux) / aux.mod());
}

lli solveBaseCRT(DynMod base0, DynMod base1, DynMod base2) {
  // adaptation of solveCRT of base0, base1, base2 avoiding overflow
  const DynMod aux = solveCRT(base0, baseRes1);
  lli aux2 = (lli)((base2 - (lli)aux) / aux.mod());
  if (aux.mod() > (1<<62) / aux2)  // result would overflow, so should be negative instead
    aux2 -= base2.mod();
  return = (lli)aux + aux.mod() * aux2;
}

}  // namespace cp_ntt

template<class T>
class Poly : public vector<T> {
 public:
  Poly operator+() const { return *this; }
  Poly operator-() const { return *this * Poly{-1}; }
  Poly operator+(const Poly& rhs) const { Poly p = *this; p += rhs; return p; }
  Poly operator-(const Poly& rhs) const { Poly p = *this; p -= rhs; return p; }
  Poly operator*(const Poly& rhs) const {
    switch multStrategy(size(), rhs.size()) {
    case Naive:
      return naiveMult(rhs);
      break;
    case Karatsuba:
      return karatsubaMult(rhs);
      break;
    case NTT:
      return nttMult(rhs);
      break;
    }
    assert(false);
  }
  Poly operator/(const Poly& rhs) const {
    switch multStrategy(size()-rhs.size()+1, rhs.size()) {
    case Naive:
      return naiveDiv(rhs);
      break;
    case Karatsuba:
      return karatsubaDiv(rhs);
      break;
    case NTT:
      return nttDiv(rhs);
      break;
    }
    assert(false);
  }
  Poly& operator+=(const Poly& rhs) {
    if (rhs.size() > size())
      resize(rhs.size(), zero());
    for (int i=0; i<rhs.size(); ++i)
      *this[i] += rhs[i];
    return *this;
  }
  Poly& operator-=(const Poly& rhs) { return *this += -rhs; }
  Poly& operator*=(const Poly& rhs) { return *this = *this * rhs; }
  Poly& operator/=(const Poly& rhs) { return *this = *this / rhs; }
 private:
  enum MultStrategy {
    Naive,
    Karatsuba,
    NTT
  };
  T zero() const;
  static MultStrategy multStrategy(int size, int rhsSize) const {
    if (size < 3 || rhsSize < 3)
      return Naive;
    else
      return Karatsuba;
  }
  Poly naiveMult(const Poly& rhs) const {
    Poly result(size()+rhs.size()-1, zero());
    for (int i=0; i<size(); ++i)
      for (int j=0; j<rhs.size(); ++j)
        result[i+j] += *this[i] * rhs[j];
    return result;
  }
  Poly karatsubaMult(const Poly& rhs) const {
    int s = (min(size(), rhs.size())+1)/2;
    Poly a(cbegin(), cbegin()+s), b(cbegin()+s, cend()), c(rhs.cbegin(), rhs.cbegin()+s), d(rhs.cbegin()+s, rhs.cend());
    Poly low = a*c, high = b*d, mid = (a+b)*(c+d) - low - high;
    high.insert(high.begin(), 2*s, zero());
    mid.insert(mid.begin(), s, zero());
    return low + mid + high;
  }
  Poly nttMult(const Poly& rhs) const;
};

template<>
lli Poly<lli>::zero() const {
  return 0;
}

template<>
DynMod Poly<DynMod>::zero() const {
  return DynMod(0, *this[0].mod());
}

template<>
Poly<lli> Poly<lli>::nttMult(const Poly<lli>& rhs) const {
  int finalSize = size()+rhs.size()-1;
  vector<vector<DynMod>> a = allNTT(*this, finalSize, cp_ntt::BaseRoot);
  vector<vector<DynMod>> b = allNTT(rhs, finalSize, cp_ntt::BaseRoot);
  for (int i=0; i<a.size(); ++i)
    for (int j=0; j<a[i].size(); ++j)
      a[i][j] *= b[i][j];
  for (int i=0; i<a.size(); ++i)
    NTT(a[i], 1/cp_ntt::BaseRoot[i]);
  Poly<lli> result(finalSize);
  for (int i=0; i<result.size(); ++i)
    result[i] = cp_ntt::solveBaseCRT(a[0][i], a[1][i], a[2][i]);
  return result;
}

template<>
Poly<DynMod> Poly<DynMod>::nttMult(const Poly<DynMod>& rhs) const {
  // could also do a single NTT multiplication if mod is prime and mod-1 is a multiple of a high enough power of 2
  int finalSize = size()+rhs.size()-1;
  vector<vector<DynMod>> a = allNTT(*this, finalSize, cp_ntt::BaseRoot);
  vector<vector<DynMod>> b = allNTT(rhs, finalSize, cp_ntt::BaseRoot);
  for (int i=0; i<a.size(); ++i)
    for (int j=0; j<a[i].size(); ++j)
      a[i][j] *= b[i][j];
  for (int i=0; i<a.size(); ++i)
    NTT(a[i], 1/cp_ntt::BaseRoot[i]);
  Poly<lli> result(finalSize);
  for (int i=0; i<result.size(); ++i)
    result[i] = cp_ntt::solveBaseCRT(a[0][i], a[1][i], a[2][i], *this[0].mod());
  return result;
}
