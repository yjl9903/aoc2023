#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <utility>
#include <tuple>

using namespace std;

const int maxn = 256;

int n, m, cnt[maxn][maxn];
bool visited[maxn][maxn][4];
char mp[maxn][maxn];

const vector<pair<int,int>> dir {
  { -1, 0 },
  { 0, -1 },
  { 1, 0 },
  { 0, 1 }
};

// /
const vector<pair<int,int>> dir1 {
  { 0, 1 },
  { 1, 0 },
  { 0, -1 },
  { -1, 0 }
};
int ndir1[] = { 3, 2, 1, 0 };

const vector<pair<int,int>> dir2 {
  { 0, -1 },
  { -1, 0 },
  { 0, 1 },
  { 1, 0 }
};
int ndir2[] = { 1, 0, 3, 2 };

int main() {
  while (scanf("%s", mp[++n] + 1) == 1) {
    m = strlen(mp[n] + 1);
  }
  n--;

  vector<tuple<int,int,int>> cur;
  // 0 -> U, 1 -> L, 2 -> D, 3 -> R
  cur.push_back({ 1, 1, 3 });
  for (int i = 0; i < cur.size(); i++) {
    int cx = get<0>(cur[i]);
    int cy = get<1>(cur[i]);
    int cd = get<2>(cur[i]);
    cnt[cx][cy] = 1;

    auto next = [&](int nx, int ny, int nd) {
      if (nx < 1 || nx > n || ny < 1 || ny > m) return;
      if (!visited[nx][ny][nd]) {
        visited[nx][ny][nd] = true;
        cur.push_back({ nx, ny, nd });
      }
    };
    
    if (mp[cx][cy] == '.') {
      int nx = cx + dir[cd].first;
      int ny = cy + dir[cd].second;
      int nd = cd;
      next(nx, ny, nd);
    } else if (mp[cx][cy] == '|') {
      if (cd == 1 || cd == 3) {
        next(cx, cy, 0);
        next(cx, cy, 2);
      } else {
        int nx = cx + dir[cd].first;
        int ny = cy + dir[cd].second;
        int nd = cd;
        next(nx, ny, nd);
      }
    } else if (mp[cx][cy] == '-') {
      if (cd == 1 || cd == 3) {
        int nx = cx + dir[cd].first;
        int ny = cy + dir[cd].second;
        int nd = cd;
        next(nx, ny, nd);
      } else {
        next(cx, cy, 1);
        next(cx, cy, 3);
      }
    } else if (mp[cx][cy] == '/') {
      int nx = cx + dir1[cd].first;
      int ny = cy + dir1[cd].second;
      int nd = ndir1[cd];
      next(nx, ny, nd);
    } else if (mp[cx][cy] == '\\') {
      int nx = cx + dir2[cd].first;
      int ny = cy + dir2[cd].second;
      int nd = ndir2[cd];
      next(nx, ny, nd);
    }
  }

  int ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      // putchar(cnt[i][j] ? '#' : '.');
      ans += cnt[i][j];
    }
    // puts("");
  }
  printf("%d\n", ans);

  return 0;
}