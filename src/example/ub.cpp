#include "base.cpp"
#include "log.cpp"

int main() {
  int a, b;
  cin >> a >> b;
  LOG(a); LOG(b);
  int ans = a+b;
  LOG(ans);
  printf("%d\n", ans);
}

