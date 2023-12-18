#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>

using namespace std;

const int maxn = 1024;

int mp[maxn][maxn], cnt[maxn][maxn];

int main() {
  vector<pair<char,int>> cmds;
  char dir[2], rgb[32];
  int len;
  while (scanf("%s %d %s", dir, &len, rgb) == 3) {
    cmds.push_back({ dir[0], len });
  }
  int cx = 500, cy = 300;
  int n = cx, m = cy;
  mp[cx][cy] = 1;
  for (auto& cmd: cmds) {
    int dx = 0, dy = 0;
    if (cmd.first == 'U') dx = -1;
    else if (cmd.first == 'L') dy = -1;
    else if (cmd.first == 'D') dx = 1;
    else if (cmd.first == 'R') dy = 1;
    for (int i = 0; i < cmd.second; i++) {
      cx += dx;
      cy += dy;
      if (cx < 1 || cy < 1) {
        printf("%d %d\n", cx, cy);
      }
      mp[cx][cy] = 1;
      n = max(cx, n);
      m = max(cy, m);
    }
  }

  int ans = 0;
  for (int i = 1; i <= n; i++) {
    bool in = false;
    for (int j = 1; j <= m;) {
      if (mp[i][j]) {
        int k = j;
        while (k <= m && mp[i][k]) {
          ans++;
          k++;
        }
        if (j != k - 1 && mp[i - 1][j] && mp[i - 1][k - 1]) {}
        else if (j != k - 1 && mp[i + 1][j] && mp[i + 1][k - 1]) {}
        else in = !in;
        j = k;
      } else {
        cnt[i][j] = in;
        ans += in;
        j++;
      }
    }
  }
  // for (int i = 1; i <= n; i++) {
  //   for (int j = 1; j <= m; j++) {
  //     putchar(mp[i][j] || cnt[i][j] ? '#' : '.');
  //   }
  //   puts("");
  // }
  printf("%d\n", ans);
  return 0;
}