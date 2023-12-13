#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

char buf[128];
int row[128][128], col[128][128];

int main() {
  int sum = 0;
  while (true) {
    vector<string> mp;
    while (scanf("%[^\n]", buf) == 1) {
      getchar();
      mp.push_back(buf);
    }
    if (mp.empty()) break;
    getchar();

    int n = mp.size(), m = mp.front().size();
    memset(row, 0, sizeof row);
    memset(col, 0, sizeof col);
    for (int i = 0; i < n; i++) {
      // puts(mp[i].c_str());
      for (int j = 0; j + 1 < m; j++) {
        int p = j, q = j + 1;
        while (p >= 0 && q < m && mp[i][p] == mp[i][q]) p--, q++;
        row[i][j] = j - p;
      }
    }
    for (int j = 0; j < m; j++) {
      for (int i = 0; i + 1 < n; i++) {
        int p = i, q = i + 1;
        while (p >= 0 && q < n && mp[p][j] == mp[q][j]) p--, q++;
        col[i][j] = i - p;
      }
    }

    int rans = 0, cans = 0;
    for (int j = 0; j + 1 < m; j++) {
      if (!row[0][j]) continue;
      bool flag = true;
      for (int i = 1; i < n; i++) {
        if (row[i][j] != row[0][j]) {
          flag = false; break;
        }
      }
      if (flag) {
        rans = j + 1;
        break;
      }
    }
    for (int i = 0; i + 1 < n; i++) {
      if (!col[i][0]) continue;
      bool flag = true;
      for (int j = 1; j < m; j++) {
        if (col[i][j] != col[i][0]) {
          flag = false; break;
        }
      }
      if (flag) {
        cans = i + 1;
        break;
      }
    }
    // for (int i = 0; i + 1 < n; i++) {
    //   for (int j = 0; j < m; j++) {
    //     printf("%d ", col[i][j]);
    //   }
    //   puts("");
    // }
    // printf("Ans: %d %d\n", rans, cans);
    sum += rans + 100 * cans;
  }
  printf("%d\n", sum);
  return 0;
}