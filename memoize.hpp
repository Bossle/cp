#pragma once
#include <type_traits>
#include <utility>

// MEMOIZE can be used to reduce the running time of functions
// It skips the function's processing if it was called previously with the same arguments
// It may change function behavior if the function has side effects or uses non-local variables
// Usage: call MEMOIZE(function, arguments) at the start of the implementation of function(arguments)
#define MEMOIZE(function, arguments...) {\
  auto p = memoize(function, arguments);\
  if (p.first)\
    return p.second;\
}

// memoize(function, arguments) provides the storage logic to MEMOIZE
// You should probably use MEMOIZE instead.
// The first return argument denotes a failure in storage,
//   it is used to prevent infinite loops,
//   since function calls memoize and memoize may call function
template<class F, class... I, class O = typename std::result_of<F&&(I...)>::type>
std::pair<bool, O> memoize(F& f, I... args);

#include "memoize_impl.hpp"
