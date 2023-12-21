#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <utility>
#include <queue>
#include <tuple>

using namespace std;

const int maxn = 256;

int n, m;
bool visited[70][maxn][maxn];
char mp[maxn][maxn];

const vector<pair<int,int>> dir = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

int main() {
  int sx, sy;
  while (scanf("%s", mp[++n] + 1) == 1) {
    m = strlen(mp[n] + 1);
    for (int i = 1; i <= m; i++) {
      if (mp[n][i] == 'S') {
        sx = n;
        sy = i;
      }
    }
  }
  n--;
  queue<tuple<int,int,int>> q;
  q.push({ 0, sx, sy });
  visited[0][sx][sy] = 1;
  while (!q.empty()) {
    int cd = get<0>(q.front());
    int cx = get<1>(q.front());
    int cy = get<2>(q.front());
    q.pop();
    if (cd == 64) continue;
    for (auto& d: dir) {
      int nd = cd + 1;
      int nx = cx + d.first;
      int ny = cy + d.second;
      if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
      if (mp[nx][ny] == '#') continue;
      if (!visited[nd][nx][ny]) {
        visited[nd][nx][ny] = true;
        q.push({ nd, nx, ny });
      }
    }
  }
  int K = 50;
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      ans += visited[K][i][j];
      if (mp[i][j] == '#') {
        putchar('#');
      } else if (visited[K][i][j]) {
        putchar('O');
      } else {
        putchar('.');
      }
    }
    puts("");
  }
  printf("%d\n", ans);
  return 0;
}