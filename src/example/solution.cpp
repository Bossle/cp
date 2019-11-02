#include "base.cpp"

int main() {
  int a, b;
  cin >> a >> b;
  LOG(a); LOG(b);
  int ans = a+b;
  LOG(ans);
  cout << ans << endl;
}

