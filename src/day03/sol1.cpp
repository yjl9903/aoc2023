#include <cstdio>
#include <algorithm>
#include <utility>

using namespace std;

int n = 140, m = 140;

char map[150][150];

bool isDigit(char c) {
  return '0' <= c && c <= '9';
}

int main() {
  for (int i = 1; i <= n; i++) {
    scanf("%s", map[i] + 1);
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (isDigit(map[i][j])) {
        int k = j, sum = 0;
        while (k <= m && isDigit(map[i][k])) {
          sum = sum * 10 + (map[i][k] - '0');
          k++;
        }
        bool ok = false;
        for (int p = max(j - 1, 1); p <= min(k, m) && !ok; p++) {
          if (i - 1 >= 1 && !isDigit(map[i - 1][p]) && map[i - 1][p] != '.') {
            ok = true;
          }
          if (!isDigit(map[i][p]) && map[i][p] != '.') {
            ok = true;
          }
          if (i + 1 <= m && !isDigit(map[i + 1][p]) && map[i + 1][p] != '.') {
            ok = true;
          }
        }
        if (ok) {
          ans += sum;
        }
        j = k - 1;
      } else {
        continue;
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}