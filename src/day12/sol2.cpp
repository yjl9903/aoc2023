#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <string>

using namespace std;

const int maxn = 1024;

char buf1[maxn], buf2[maxn];
long long f[maxn][24][64];

int main() {
  long long sum = 0;
  while (scanf("%s %s", buf1, buf2) == 2) {
    vector<int> parts;
    for (int i = 0, len = strlen(buf2); i < len; i++) {
      int j = i;
      while (i < len && '0' <= buf2[i] && buf2[i] <= '9') i++;
      buf2[i] = 0;
      parts.push_back(atoi(buf2 + j));
    }
    string raw;
    raw += buf1; raw += '?';
    raw += buf1; raw += '?';
    raw += buf1; raw += '?';
    raw += buf1; raw += '?';
    raw += buf1;
    vector<int> parts2 = parts;
    for (int i = 0; i < 4; i++) {
      for (int x: parts2) parts.push_back(x);
    }
    // ---
    // puts(raw.c_str());
    // for (int x: parts) printf("%d ", x); puts("");

    memset(f, 0, sizeof f);
    f[0][0][0] = 1;
    int part = *max_element(parts.begin(), parts.end());
    for (int i = 0; i <= raw.size(); i++) {
      for (int j = 0; j <= part; j++) {
        for (int k = 0; k <= parts.size(); k++) {
          if (!f[i][j][k]) continue;
          // printf("f[%d][%d][%d] = %d\n", i, j, k, f[i][j][k]);
          if (i == raw.size() || raw[i] == '.' || raw[i] == '?') {
            if (j == 0) {
              f[i + 1][0][k] += f[i][j][k];
            } else if (k < parts.size()) {
              if (j == parts[k]) {
                f[i + 1][0][k + 1] += f[i][j][k];
              } else if (j != parts[k]) {
                // invalid
              }
            }
          }
          if (i < raw.size()) {
            if (raw[i] == '#' || raw[i] == '?') {
              if (j + 1 <= part) {
                f[i + 1][j + 1][k] += f[i][j][k];
              }
            }
          }
        }
      }
    }
    long long ans = f[raw.size() + 1][0][parts.size()];
    assert(ans >= 0);
    // printf("ans: %d\n", ans);
    sum += ans;
  }
  printf("%lld\n", sum);
  return 0;
}