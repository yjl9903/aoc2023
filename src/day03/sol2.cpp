#include <cstdio>
#include <algorithm>
#include <utility>

using namespace std;

int n = 140, m = 140;

char map[150][150];
int cnt[150][150], mul[150][150];

bool isDigit(char c) {
  return '0' <= c && c <= '9';
}

int main() {
  for (int i = 1; i <= n; i++) {
    scanf("%s", map[i] + 1);
  }
  long long ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (isDigit(map[i][j])) {
        int k = j, sum = 0;
        while (k <= m && isDigit(map[i][k])) {
          sum = sum * 10 + (map[i][k] - '0');
          k++;
        }
        auto check = [&](int x, int y) {
          cnt[x][y]++;
          if (cnt[x][y] == 1) {
            mul[x][y] = sum;
          } else if (cnt[x][y] == 2) {
            mul[x][y] *= sum;
            ans += mul[x][y];
          }
        };
        for (int p = max(j - 1, 1); p <= min(k, m); p++) {
          if (i - 1 >= 1 && map[i - 1][p] == '*') {
            check(i - 1, p);
          }
          if (map[i][p] == '*') {
            check(i, p);
          }
          if (i + 1 <= m && map[i + 1][p] == '*') {
            check(i + 1, p);
          }
        }
        // if (ok) {
        //   ans += sum;
        //   printf("OK %d:[%d,%d]: %d\n", i, j, k, sum);
        // }
        j = k - 1;
      } else {
        continue;
      }
    }
  }
  printf("%lld\n", ans);
  return 0;
}