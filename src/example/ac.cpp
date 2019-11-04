#include "base.cpp"
#include "log.cpp"

typedef long long int lli;

int main() {
  lli a, b;
  cin >> a >> b;
  LOG(a); LOG(b);
  lli ans = a+b;
  LOG(ans);
  printf("%lld\n", ans);
}

