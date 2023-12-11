#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <unistd.h>

using namespace std;

const int inf = 1e9;

int n, m;
char mp[256][256];

vector<pair<int,int>> edge[256][256];
int dis[256][256];
bool mt[256][256], mb[256][256], ml[256][256], mr[256][256];

bool overflow(int x, int y) {
  return x < 1 || x > n || y < 1 || y > m;
}

void adde(int sx, int sy, int dx, int dy) {
  if (!overflow(sx, sy) && !overflow(dx, dy)) {
    edge[sx][sy].push_back({ dx, dy });
    edge[dx][dy].push_back({ sx, sy });
  }
}

int main() {
  while (scanf("%s", mp[++n] + 1) == 1) {
    m = strlen(mp[n] + 1);
  }
  n--;

  int stx, sty;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      dis[i][j] = inf;
      if (mp[i][j] == '|') {
        mt[i][j] = true;
        mb[i][j] = true;
        // adde(i - 1, j, i, j);
        // adde(i, j, i + 1, j);
      } else if (mp[i][j] == '-') {
        ml[i][j] = true;
        mr[i][j] = true;
        // adde(i, j - 1, i, j);
        // adde(i, j, i, j + 1);
      } else if (mp[i][j] == 'L') {
        mt[i][j] = true;
        mr[i][j] = true;
        // adde(i - 1, j, i, j);
        // adde(i, j, i, j + 1);
      } else if (mp[i][j] == 'J') {
        mt[i][j] = true;
        ml[i][j] = true;
        // adde(i - 1, j, i, j);
        // adde(i, j, i, j - 1);
      } else if (mp[i][j] == '7') {
        ml[i][j] = true;
        mb[i][j] = true;
        // adde(i, j - 1, i, j);
        // adde(i, j, i + 1, j);
      } else if (mp[i][j] == 'F') {
        mr[i][j] = true;
        mb[i][j] = true;
        // adde(i, j + 1, i, j);
        // adde(i, j, i + 1, j);
      } else if (mp[i][j] == 'S') {
        stx = i;
        sty = j;
        ml[i][j] = mr[i][j] = mt[i][j] = mb[i][j] = true;
      }
    }
  }

  dis[stx][sty] = 0;
  queue<pair<int,int>> q;
  q.push({ stx, sty });
  while (!q.empty()) {
    auto cur = q.front();
    q.pop();
    auto push = [&](int x, int y) {
      int nd = dis[cur.first][cur.second] + 1;
      if (nd < dis[x][y]) {
        dis[x][y] = nd;
        q.push({ x, y });
      }  
    };
    if (mt[cur.first][cur.second] && mb[cur.first - 1][cur.second]) {
      push(cur.first - 1, cur.second);
    }
    if (ml[cur.first][cur.second] && mr[cur.first][cur.second - 1]) {
      push(cur.first, cur.second - 1);
    }
    if (mb[cur.first][cur.second] && mt[cur.first + 1][cur.second]) {
      push(cur.first + 1, cur.second);
    }
    if (mr[cur.first][cur.second] && ml[cur.first][cur.second + 1]) {
      push(cur.first, cur.second + 1);
    }
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (dis[i][j] != inf) {
        ans = max(ans, dis[i][j]);
        // printf("%d", dis[i][j]);
      } else {
        // putchar('.');
      }
    }
    // puts("");
  }

  if (isatty(fileno(stdout))) {
    printf("%d\n", ans);
  } else {
    printf("%d %d\n", n, m);
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        if (j > 1) putchar(' ');
        if (dis[i][j] != inf) {
          printf("%d", dis[i][j]);
          if (dis[i][j] == 0) {
            if (mr[i][j - 1] && mb[i - 1][j]) mp[i][j] = 'J';
            else if (mr[i][j - 1] && mt[i + 1][j]) mp[i][j] = '7';
            else if (ml[i][j + 1] && mt[i + 1][j]) mp[i][j] = 'F';
            else mp[i][j] = 'L';
          }
        } else {
          mp[i][j] = '.';
          putchar('-');
          putchar('1');
        }
      }
      puts("");
    }
    for (int i = 1; i <= n; i++) {
      puts(mp[i] + 1);
    }
  }
  return 0;
}