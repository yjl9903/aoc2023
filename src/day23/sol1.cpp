#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <utility>
#include <tuple>
#include <queue>
#include <set>

using namespace std;

const int maxn = 256;

const vector<pair<int,int>> dir = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

char mp[maxn][maxn];
vector<pair<int,int>> edges[maxn][maxn];

int n, m, f[maxn][maxn];
int dfs(int x, int y, set<pair<int,int>> visited) {
  if (f[x][y] != -1) return f[x][y];
  if (edges[x][y].empty()) {
    if (x == n && y == m - 1) return 0;
    else return -1;
  }
  int mx = 0;
  for (auto& v: edges[x][y]) {
    if (visited.count({ v.first, v.second })) continue;
    visited.insert({ v.first, v.second });
    int d = dfs(v.first, v.second, visited);
    visited.erase({ v.first, v.second });
    if (d == -1) continue;
    mx = max(mx, d);
  }
  // printf("f[%d][%d] = %d\n", x, y, mx + 1);
  return f[x][y] = mx + 1;
}

int main() {
  while (scanf("%s", mp[++n] + 1) == 1) {
    m = strlen(mp[n] + 1);
  }
  n--;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (mp[i][j] == '#') continue;
      for (auto& d: dir) {
        int x = i + d.first;
        int y = j + d.second;
        if (x < 1 || x > n || y < 1 || y > m) continue;
        if (mp[x][y] == '#') continue;
        if (mp[x][y] == '>' && d.second == -1) continue;
        if (mp[x][y] == '<' && d.second == 1) continue;
        if (mp[x][y] == '^' && d.first == 1) continue;
        if (mp[x][y] == 'v' && d.first == -1) continue;
        // printf("(%d,%d) -> (%d,%d)\n", i, j, x, y);
        edges[i][j].push_back({ x, y });
      }
    }
  }

  memset(f, -1, sizeof f);
  int ans = dfs(1, 2, { { 1,2 } });
  printf("%d\n", ans - 1);

  return 0;
}