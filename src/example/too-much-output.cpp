#include "base.cpp"
#include "log.cpp"

int main() {
  lli a, b;
  cin >> a >> b;
  LOG(a); LOG(b);
  lli ans = a+b;
  LOG(ans);
  printf("%lld\n", ans);
  printf("%lld\n", ans);
}

