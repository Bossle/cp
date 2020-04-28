#include "base.cpp"
#include "log.cpp"

int main() {
  lli a, b;
  cin >> a >> b;
  LOG(a); LOG(b);
  lli ans = a+b;
  LOG(ans);
  for (lli i=0; i<(lli)1e18; ++i)
    if (i == ans)
      printf("%lld\n", ans);
}

