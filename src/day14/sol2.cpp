#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <map>

using namespace std;

const int maxn = 256;

int n, m, cubes[maxn][maxn];
char mp[maxn][maxn];

void north() {
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
}
void west() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m;) {
      if (mp[i][j] == '#') {
        j++;
        continue;
      }
      int k = j, cnt = 0;
      while (k <= m && mp[i][k] != '#') {
        if (mp[i][k] == 'O') cnt++;
        k++;
      }
      for (int p = j; p < k; p++) {
        if (cnt > 0) {
          mp[i][p] = 'O';
          cnt--;
        } else {
          mp[i][p] = '.';
        }
      }
      j = k;
    }
  }
}
void south() {
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
      for (int p = k - 1; p >= i; p--) {
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
}
void east() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m;) {
      if (mp[i][j] == '#') {
        j++;
        continue;
      }
      int k = j, cnt = 0;
      while (k <= m && mp[i][k] != '#') {
        if (mp[i][k] == 'O') cnt++;
        k++;
      }
      for (int p = k - 1; p >= j; p--) {
        if (cnt > 0) {
          mp[i][p] = 'O';
          cnt--;
        } else {
          mp[i][p] = '.';
        }
      }
      j = k;
    }
  }
}

int main() {
  while (scanf("%s", mp[++n] + 1) == 1) {
    m = strlen(mp[n] + 1);
  }
  n--;

  vector<string> old;
  for (int i = 1; i <= n; i++) old.push_back(mp[i] + 1);
  map<vector<string>,int> visited;
  visited[old] = 0;

  const int T = 1000000000;
  int loop = 0;
  for (int t = 1; t <= T; t++) {
    north(); west(); south(); east();
    vector<string> cur;
    for (int i = 1; i <= n; i++) cur.push_back(mp[i] + 1);
    if (visited.count(cur)) {
      printf("Start: %d, Len: %d\n", visited[cur], t - visited[cur]);
      loop = (T - t) % (t - visited[cur]);
      break;
    }
    visited[cur] = t;

    // puts("---");
    // for (int i = 1; i <= n; i++) {
    //   puts(mp[i] + 1);
    // }
  }
  for (int i = 0; i < loop; i++) {
    north(); west(); south(); east();
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