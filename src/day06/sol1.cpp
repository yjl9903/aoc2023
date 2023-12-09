#include <cstdio>

using namespace std;

int main() {
  long long n, m;
  long long ans = 1;
  while (scanf("%lld%lld", &n, &m) == 2) {
    int cnt = 0;
    for (int i = 1; i < n; i++) {
      long long len = 1ll * (n - i) * i;
      if (len > m) {
        cnt++;
      }
    }
    ans *= cnt;
  }
  printf("%lld\n", ans);
  return 0;
}