#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 256;

int n, m, cubes[maxn][maxn];
char mp[maxn][maxn];

int main() {
  while (scanf("%s", mp[++n] + 1) == 1) {
    m = strlen(mp[n] + 1);
  }
  n--;

  for (int j = 1; j <= m; j++) {
    for (int i = 1; i <= n;) {
      if (mp[i][j] == '#') {
        i++;
        continue;
      }
      int k = i, cnt = 0;
      while (k <= n && mp[k][j] != '#') {
        if (mp[k][j] == 'O') cnt++;
        k++;
      }
      for (int p = i; p < k; p++) {
        if (cnt > 0) {
          mp[p][j] = 'O';
          cnt--;
        } else {
          mp[p][j] = '.';
        }
      }
      i = k;
    }
  }

  // for (int i = 1; i <= n; i++) {
  //   puts(mp[i] + 1);
  // }
  for (int j = 1; j <= m; j++) {
    for (int i = n; i >= 1; i--) {
      cubes[i][j] += cubes[i][j + 1];
      if (mp[i][j] == '#') cubes[i][j]++;
    }
  }
  int ans = 0;
  for (int j = 1; j <= m; j++) {
    for (int i = 1; i <= n; i++) {
      if (mp[i][j] == 'O') {
        ans += n - i + 1 - cubes[i][j];
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}