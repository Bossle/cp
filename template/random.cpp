#pragma once

namespace cp_random {

#ifdef BOSSLE_DEBUG
  const auto seed = 0;
#else
  seed_seq seed{
    chrono::steady_clock::now().time_since_epoch().count(),
    (long int)random_device()()
  };
#endif

}  // namespace cp_random

mt19937 RNG(cp_random::seed);

// shuffle(v.begin(), v.end(), RNG);
// uniform_int_distribution<int>(min, max)(RNG);
