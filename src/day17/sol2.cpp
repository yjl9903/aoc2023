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
int n, m, dis[maxn][maxn][4];

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
  priority_queue<tuple<int,int,int,int>> q;
  q.push({ 0, 1, 1, 0 });
  q.push({ 0, 1, 1, 1 });
  dis[1][1][0] = 0;
  dis[1][1][1] = 0;
  while (!q.empty()) {
    int cc = get<0>(q.top());
    int cx = get<1>(q.top());
    int cy = get<2>(q.top());
    int cd = get<3>(q.top());
    q.pop();
    // printf("cur(%d): %d %d %d %d\n", cc, cx, cy, cd, cl);
    if (-cc != dis[cx][cy][cd]) continue;
    // printf("Vis: (%d,%d,%d,%d), len: %d\n", cx, cy, cd, cl, -cc);

    for (int i = 0; i < 4; i++) {
      int nd = i;
      // Must turning
      if (nd == cd || abs(cd - nd) == 2) continue;
      int nx = cx;
      int ny = cy;
      int cost = 0;
      for (int l = 1; l <= 10; l++) {
        nx += dir[i].first;
        ny += dir[i].second;
        cost += mp[nx][ny] - '0';
        if (nx < 1 || nx > n || ny < 1 || ny > m) break;
        if (l < 4) continue;
        if (dis[nx][ny][nd] == -1 || dis[nx][ny][nd] > dis[cx][cy][cd] + cost) {
          dis[nx][ny][nd] = dis[cx][cy][cd] + cost;
          q.push({ -dis[nx][ny][nd], nx, ny, nd });
        }
      }
    }
  }

  int ans = 1e9;
  for (int i = 0; i < 4; i++) {
    if (dis[n][m][i] != -1) {
      ans = min(ans, dis[n][m][i]);
    }
  }
  printf("%d\n", ans);

  return 0;
}