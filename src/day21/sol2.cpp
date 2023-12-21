#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
#include <string>
#include <utility>
#include <queue>
#include <tuple>

using namespace std;

const int maxn = 140;
const int K = 50;

int n, m;
long long ans = 0;
char mp[maxn][maxn];

const vector<pair<int,int>> dir = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

// pair<int,int> left[maxn][maxn], right[maxn][maxn], top[maxn][maxn], bottom[maxn][maxn];

int main() {
  int sx, sy;
  while (scanf("%s", mp[n]) == 1) {
    m = strlen(mp[n]);
    for (int i = 0; i < m; i++) {
      if (mp[n][i] == 'S') {
        sx = n;
        sy = i;
      }
    }
    n++;
  }

  vector<vector<int>> dis(7 * n, vector<int>(7 * m, -1));
  {
    int ssx = sx + 3 * n;
    int ssy = sy + 3 * m;
    queue<pair<int,int>> q;
    q.push({ ssx, ssy });
    dis[ssx][ssy] = 0;
    while (!q.empty()) {
      int cx = q.front().first;
      int cy = q.front().second;
      q.pop();
      for (auto& d: dir) {
        int nx = cx + d.first;
        int ny = cy + d.second;
        if (nx < 0 || nx >= 7 * n || ny < 0 || ny >= 7 * m) continue;
        if (mp[nx % n][ny % m] == '#') continue;
        if (dis[nx][ny] == -1) {
          dis[nx][ny] = dis[cx][cy] + 1;
          q.push({ nx, ny });
        }
      }
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (mp[i][j] == '#') continue;
      int l1 = dis[3 * n + i][j];
      int l2 = dis[3 * n + i][j + m];
      if (l1 == -1 || l2 == -1) {
        assert(l1 == -1 && l2 == -1);
        continue;
      }
      int k = l1 - l2, b = l2 - k;
      assert(l1 % k == l2 % k && l2 == b + k && l1 == b + k + k);
      // left[i][j] = { k, b };
      int pre = ans;
      for (int c = 1; c * k + b <= K; c++) {
        ans += (1ll * c * k + b - K) % 2 == 0;
      }
      if (i + 1 == 4 && j + 1 == 8) {
        printf("%d %d\n", k, b);
      }
      printf("(%d,%d): %d\n", i + 1, j + 1, ans - pre);
    }
  }
  // for (int i = 0; i < n; i++) {
  //   for (int j = 0; j < m; j++) {
  //     if (mp[i][j] == '#') continue;
  //     int l1 = dis[3 * n + i][j + 6 * m];
  //     int l2 = dis[3 * n + i][j + 5 * m];
  //     if (l1 == -1 || l2 == -1) {
  //       assert(l1 == -1 && l2 == -1);
  //       continue;
  //     }
  //     int k = l1 - l2, b = l2 - k;
  //     assert(l1 % k == l2 % k);
  //     // left[i][j] = { k, b };
  //     for (int c = 1; c * k + b <= K; c++) {
  //       ans += (1ll * c * k + b - K) % 2 == 0;
  //     }
  //   }
  // }
  // for (int i = 0; i < n; i++) {
  //   for (int j = 0; j < m; j++) {
  //     if (mp[i][j] == '#') continue;
  //     int l1 = dis[i][j + 3 * m];
  //     int l2 = dis[i + n][j + 3 * m];
  //     if (l1 == -1 || l2 == -1) {
  //       assert(l1 == -1 && l2 == -1);
  //       continue;
  //     }
  //     int k = l1 - l2, b = l2 - k;
  //     assert(l1 % k == l2 % k);
  //     // left[i][j] = { k, b };
  //     for (int c = 1; c * k + b <= K; c++) {
  //       ans += (1ll * c * k + b - K) % 2 == 0;
  //     }
  //   }
  // }
  // for (int i = 0; i < n; i++) {
  //   for (int j = 0; j < m; j++) {
  //     if (mp[i][j] == '#') continue;
  //     int l1 = dis[i + 6 * n][j + 3 * m];
  //     int l2 = dis[i + 5 * m][j + 3 * m];
  //     if (l1 == -1 || l2 == -1) {
  //       assert(l1 == -1 && l2 == -1);
  //       continue;
  //     }
  //     int k = l1 - l2, b = l2 - k;
  //     assert(l1 % k == l2 % k);
  //     // left[i][j] = { k, b };
  //     for (int c = 1; c * k + b <= K; c++) {
  //       ans += (1ll * c * k + b - K) % 2 == 0;
  //     }
  //   }
  // }

  {
    // Center
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        {
          int l = dis[i + 3 * n][j + 3 * m];
          if (l != -1 && l <= K) {
            ans += (l - K) % 2 == 0;
          }
        }
        {
          int l = dis[i + 3 * n][j + 2 * m];
          if (l != -1 && l <= K) {
            ans += (l - K) % 2 == 0;
          }
        }
        {
          int l = dis[i + 3 * n][j + 4 * m];
          if (l != -1 && l <= K) {
            ans += (l - K) % 2 == 0;
          }
        }
        // {
        //   int l = dis[i + 2 * n][j + 3 * m];
        //   if (l != -1 && l <= K) {
        //     ans += (l - K) % 2 == 0;
        //   }
        // }
        // {
        //   int l = dis[i + 4 * n][j + 3 * m];
        //   if (l != -1 && l <= K) {
        //     ans += (l - K) % 2 == 0;
        //   }
        // }
      }
    }
  }

  // {
  //   // Left-top
  //   int count[2] = { 0, 0 };
  //   for (int i = 0; i < n; i++) {
  //     for (int j = 0; j < m; j++) {
  //       int l1 = dis[i][j];
  //       int l2 = dis[n - 1][m - 1];
  //       if (l1 == -1) continue;
  //       count[(l1 - l2) % 2]++;
  //     }
  //   }
  //   for (int r = 1; r * n <= K; r++) {
  //     int start = dis[2 * n - 1][2 * m - 1];
  //     for (int c = 1; start + r * n + c * m <= K; c++) {
  //       int rest = K - start - r * n - c * m;
  //       if (rest >= n + m - 1) {
  //         ans += count[rest % 2];
  //       } else {
  //         for (int i = 0; i < n; i++) {
  //           for (int j = 0; j < m; j++) {
  //             int l1 = dis[i][j];
  //             int l2 = dis[n - 1][m - 1];
  //             if (l1 == -1) continue;
  //             int d = rest - (l1 - l2);
  //             if (d >= 0 && d % 2 == 0) {
  //               ans++;
  //             }
  //           }
  //         }
  //       }
  //     }
  //   }
  // }
  // {
  //   // Right-top
  //   int count[2] = { 0, 0 };
  //   for (int i = 0; i < n; i++) {
  //     for (int j = 0; j < m; j++) {
  //       int l1 = dis[i][j + 4 * m];
  //       int l2 = dis[n - 1][4 * m];
  //       if (l1 == -1) continue;
  //       count[(l1 - l2) % 2]++;
  //     }
  //   }
  //   for (int r = 1; r * n <= K; r++) {
  //     int start = dis[2 * n - 1][3 * m];
  //     for (int c = 1; start + r * n + c * m <= K; c++) {
  //       int rest = K - start - r * n - c * m;
  //       if (rest >= n + m - 1) {
  //         ans += count[rest % 2];
  //       } else {
  //         for (int i = 0; i < n; i++) {
  //           for (int j = 0; j < m; j++) {
  //             int l1 = dis[i][j + 4 * m];
  //             int l2 = dis[n - 1][4 * m];
  //             if (l1 == -1) continue;
  //             int d = rest - (l1 - l2);
  //             if (d >= 0 && d % 2 == 0) {
  //               ans++;
  //             }
  //           }
  //         }
  //       }
  //     }
  //   }
  // }
  // {
  //   // Left-bottom
  //   int count[2] = { 0, 0 };
  //   for (int i = 0; i < n; i++) {
  //     for (int j = 0; j < m; j++) {
  //       int l1 = dis[i + 4 * n][j];
  //       int l2 = dis[4 * n][m - 1];
  //       if (l1 == -1) continue;
  //       count[(l1 - l2) % 2]++;
  //     }
  //   }
  //   for (int r = 1; r * n <= K; r++) {
  //     int start = dis[3 * n][2 * m - 1];
  //     for (int c = 1; start + r * n + c * m <= K; c++) {
  //       int rest = K - start - r * n - c * m;
  //       if (rest >= n + m - 1) {
  //         ans += count[rest % 2];
  //       } else {
  //         for (int i = 0; i < n; i++) {
  //           for (int j = 0; j < m; j++) {
  //             int l1 = dis[i + 4 * n][j];
  //             int l2 = dis[4 * n][m - 1];
  //             if (l1 == -1) continue;
  //             int d = rest - (l1 - l2);
  //             if (d >= 0 && d % 2 == 0) {
  //               ans++;
  //             }
  //           }
  //         }
  //       }
  //     }
  //   }
  // }
  // {
  //   // Right-bottom
  //   int count[2] = { 0, 0 };
  //   for (int i = 0; i < n; i++) {
  //     for (int j = 0; j < m; j++) {
  //       int l1 = dis[i + 4 * n][j + 4 * m];
  //       int l2 = dis[4 * n][4 * m];
  //       if (l1 == -1) continue;
  //       count[(l1 - l2) % 2]++;
  //     }
  //   }
  //   for (int r = 1; r * n <= K; r++) {
  //     int start = dis[3 * n][3 * m];
  //     for (int c = 1; start + r * n + c * m <= K; c++) {
  //       int rest = K - start - r * n - c * m;
  //       if (rest >= n + m - 1) {
  //         ans += count[rest % 2];
  //       } else {
  //         for (int i = 0; i < n; i++) {
  //           for (int j = 0; j < m; j++) {
  //             int l1 = dis[i + 4 * n][j + 4 * m];
  //             int l2 = dis[4 * n][4 * m];
  //             if (l1 == -1) continue;
  //             int d = rest - (l1 - l2);
  //             if (d >= 0 && d % 2 == 0) {
  //               ans++;
  //             }
  //           }
  //         }
  //       }
  //     }
  //   }
  // }

  printf("%lld\n", ans);
  return 0;
}