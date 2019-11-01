#ifdef BOSSLE_DEBUG
  const auto seed = 0;
#else
  const auto seed = seed_seq{
    chrono::steady_clock::now().time_since_epoch().count(),
    random_device()(),
  };
#endif

mt19937 RNG(seed);

// shuffle(v.begin(), v.end(), RNG);
// uniform_int_distribution<int>(min, max)(RNG);
