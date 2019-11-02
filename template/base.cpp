#pragma once

#include <bits/stdc++.h>
using namespace std;

#ifdef CP_DEBUG
  #include "log.cpp"
#else
  #define LOG(...)
  #pragma STDC FENV_ACCESS OFF
  #pragma STDC FP_CONTRACT ON
  #pragma STDC CX_LIMITED_RANGE ON
  #define pragma GCC optimize O3
#endif

namespace cp_base {

auto init = (
  ios::sync_with_stdio(false),
  cin.tie(nullptr)
);

}  // namespace cp_base

