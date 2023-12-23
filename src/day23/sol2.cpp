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

int n, m;
int cnt = 0, siz[maxn * maxn], bel[maxn][maxn];
vector<int> edges[maxn * maxn];

namespace Builder {
  int neib[maxn][maxn];
  bool visited[maxn][maxn];
  vector<pair<int,int>> stk;

  void dfs(int x, int y) {
    int sum = 0;
    for (auto& d: dir) {
      int nx = x + d.first;
      int ny = y + d.second;
      if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
      if (mp[nx][ny] == '#') continue;
      if (visited[nx][ny]) continue;
      visited[nx][ny] = true;
      sum++;

      if (neib[nx][ny] >= 3) {
        // printf("%d %d: size %d\n", nx, ny, stk.size());
        // Create block
        cnt++;
        siz[cnt] = stk.size();
        for (auto& p: stk) {
          bel[p.first][p.second] = cnt;
        }
        stk.clear();
        // Create block
        int mid = ++cnt;
        bel[nx][ny] = mid;
        siz[mid] = 1;

        for (auto& d: dir) {
          int cx = nx + d.first;
          int cy = ny + d.second;
          if (cx < 1 || cx > n || cy < 1 || cy > m) continue;
          if (mp[cx][cy] == '#') continue;
          if (visited[cx][cy]) continue;
          visited[cx][cy] = true;
          stk.push_back({ cx, cy });
          dfs(cx, cy);
        }        
      } else {
        stk.push_back({ nx, ny });
        dfs(nx, ny);
      }
    }
    if (sum == 0) {
      cnt++;
      siz[cnt] = stk.size();
      for (auto& p: stk) {
        bel[p.first][p.second] = cnt;
      }
      stk.clear();
    }
  }

  void build() {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        if (mp[i][j] == '#') continue;
        for (auto& d: dir) {
          int x = i + d.first;
          int y = j + d.second;
          if (x < 1 || x > n || y < 1 || y > m) continue;
          if (mp[x][y] == '#') continue;
          neib[i][j]++;
        }
      }
    }
    visited[1][2] = true;
    stk.push_back({ 1, 2 });
    dfs(1, 2);

    set<pair<int,int>> egs;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        if (!bel[i][j]) continue;
        for (auto& d: dir) {
          int x = i + d.first;
          int y = j + d.second;
          if (bel[x][y]) {
            egs.insert({ bel[i][j], bel[x][y] });
            egs.insert({ bel[x][y], bel[i][j] });
          }
        }
      }
    }
    // printf("%d %d\n", cnt, egs.size());
    // printf("%d %d\n", bel[1][2], bel[n][m - 1]);
    // for (int i = 1; i <= cnt; i++) {
    //   printf("%d\n", siz[i]);
    // }
    for (auto& e: egs) {
      // printf("%d %d\n", e.first, e.second);
      edges[e.first].push_back(e.second);
    }
    // for (int i = 1; i <= n; i++) {
    //   for (int j = 1; j <= m; j++) {
    //     printf("%3d ", bel[i][j]);
    //   }
    //   puts("");
    // }
  }
}

int ans, cur = 0;
set<int> visited;
void dfs(int u) {
  if (u == bel[n][m - 1]) {
    if (cur > ans) {
      ans = max(ans, cur);
      printf("ans: %d\n", ans);
    }
    return;
  }
  for (int v: edges[u]) {
    if (visited.count(v)) continue;
    visited.insert(v);
    cur += siz[v];
    dfs(v);
    cur -= siz[v];
    visited.erase(v);
  }
}

int main() {
  while (scanf("%s", mp[++n] + 1) == 1) {
    m = strlen(mp[n] + 1);
  }
  n--;

  Builder::build();
  int st = bel[1][2];
  cur += siz[st] - 1;
  visited.insert(st);
  dfs(st);
  printf("%d\n", ans);

  return 0;
}