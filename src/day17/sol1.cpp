#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <utility>
#include <tuple>
#include <queue>

using namespace std;

const int maxn = 256;

char mp[maxn][maxn];
int n, m, dis[maxn][maxn][4][4];

// ULDR
const vector<pair<int,int>> dir {
  { -1, 0 },
  { 0, -1 },
  { 1, 0 },
  { 0, 1 }
};

int main() {
  while (scanf("%s", mp[++n] + 1) == 1) {
    m = strlen(mp[n] + 1);
  }
  n--;

  memset(dis, -1, sizeof dis);
  priority_queue<tuple<int,int,int,int,int>> q;
  q.push({ 0, 1, 1, 2, 0 });
  dis[1][1][2][0] = 0;
  while (!q.empty()) {
    int cc = get<0>(q.top());
    int cx = get<1>(q.top());
    int cy = get<2>(q.top());
    int cd = get<3>(q.top());
    int cl = get<4>(q.top());
    q.pop();
    // printf("cur(%d): %d %d %d %d\n", cc, cx, cy, cd, cl);
    if (-cc != dis[cx][cy][cd][cl]) continue;
    // printf("Vis: (%d,%d,%d,%d), len: %d\n", cx, cy, cd, cl, -cc);

    for (int i = 0; i < 4; i++) {
      int nx = cx + dir[i].first;
      int ny = cy + dir[i].second;
      int nd = i;
      int nl = i == cd ? cl + 1 : 1;
      if (abs(cd - nd) == 2) continue;
      if (nl > 3) continue;
      if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
      if (dis[nx][ny][nd][nl] == -1 || dis[nx][ny][nd][nl] > dis[cx][cy][cd][cl] + (mp[nx][ny] - '0')) {
        dis[nx][ny][nd][nl] = dis[cx][cy][cd][cl] + (mp[nx][ny] - '0');
        q.push({ -dis[nx][ny][nd][nl], nx, ny, nd, nl });
      }
    }
  }

  int ans = 1e9;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (dis[n][m][i][j] != -1) {
        ans = min(ans, dis[n][m][i][j]);
      }
    }
  }
  printf("%d\n", ans);

  return 0;
}