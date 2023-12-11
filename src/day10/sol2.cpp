#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <queue>
#include <cassert>

using namespace std;

const int maxn = 256;

int n, m;
int mp[maxn][maxn];
char g[maxn][maxn];
bool visited[maxn][maxn];
bool chk[maxn][maxn];

const vector<pair<int,int>> dir = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

int main() {
  scanf("%d%d", &n, &m);
  memset(mp, -1, sizeof mp);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      scanf("%d", &mp[i][j]);
    }
  }
  for (int i = 1; i <= n; i++) {
    scanf("%s", g[i] + 1);
  }

  queue<pair<int,int>> q;
  visited[0][0] = true;
  q.push({ 0, 0 });
  while (!q.empty()) {
    auto cur = q.front();
    q.pop();
    for (auto& d: dir) {
      int nx = cur.first + d.first;
      int ny = cur.second + d.second;
      if (nx < 0 || nx > n + 1 || ny < 0 || ny > m + 1) continue;
      if (mp[nx][ny] != -1) continue;
      if (!visited[nx][ny]) {
        visited[nx][ny] = true;
        q.push({ nx, ny });
      }
    }
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    bool in = false;
    for (int j = 1; j <= m; j++) {
      if (g[i][j] == '|') {
        chk[i][j] = in;
        in = !in;
      } else if (g[i][j] == 'L' || g[i][j] == 'F') {
        char cur = g[i][j];
        g[i][j++] = in;
        while (j <= m && g[i][j] == '-') chk[i][j++] = in;
        if (g[i][j] != '7' && g[i][j] != 'J') {
          printf("Error: %d %d %c\n", i, j, g[i][j]);
        }
        assert(g[i][j] == '7' || g[i][j] == 'J');
        chk[i][j] = in;
        if (cur == 'L' && g[i][j] == 'J') {}
        else if (cur == 'F' && g[i][j] == '7') {}
        else in = !in;
      } else {
        chk[i][j] = in;
      }
    }
    for (int j = 1; j <= m; j++) {
      if (!visited[i][j] && mp[i][j] == -1 && chk[i][j]) ans++;
    }
  }
  printf("%d\n", ans);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (!visited[i][j] && mp[i][j] == -1 && chk[i][j]) putchar('I');
      else if (mp[i][j] != -1) putchar('*');
      else putchar('.');
    }
    puts("");
  }
  return 0;
}