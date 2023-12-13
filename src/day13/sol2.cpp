#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <utility>

using namespace std;

char buf[128];
int row[128][128], col[128][128];

pair<int,int> calc(vector<string> mp, pair<int,int> old) {
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

  int rans = -1, cans = -1;
  for (int j = 0; j + 1 < m; j++) {
    if (!row[0][j]) continue;
    bool flag = true;
    for (int i = 1; i < n; i++) {
      if (row[i][j] != row[0][j]) {
        flag = false; break;
      }
    }
    if (flag && j + 1 != old.first) {
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
    if (flag && i + 1 != old.second) {
      cans = i + 1;
      break;
    }
  }

  return { rans, cans };
}

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

    auto res = calc(mp, {-1, -1});
    int orr = res.first;
    int orc = res.second;
    // printf("O: %d %d\n", orr, orc);

    int n = mp.size(), m = mp.front().size();
    int rans = -1, cans = -1;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (mp[i][j] == '.') {
          mp[i][j] = '#';
          auto r = calc(mp, {orr, orc});
          // printf("Find: %d %d -> %d %d\n", i, j, r.first, r.second);
          if ((r.first != -1 || r.second != -1) && r != res) {
            rans = r.first;
            cans = r.second;
          }
          mp[i][j] = '.';
        } else if (mp[i][j] == '#') {
          mp[i][j] = '.';
          auto r = calc(mp, {orr, orc});
          // printf("Find: %d %d -> %d %d\n", i, j, r.first, r.second);
          if ((r.first != -1 || r.second != -1) && r != res) {
            rans = r.first;
            cans = r.second;
          }
          mp[i][j] = '#';
        }
      }
    }

    // printf("ans: %d %d\n", rans, cans);
    // if (rans == -1 && cans == -1) {
    //   for (int i = 0; i < n; i++) puts(mp[i].c_str());
    // }
    if (rans < 0) rans = 0;
    if (cans < 0) cans = 0;
    sum += rans + 100 * cans;
  }
  printf("%d\n", sum);
  return 0;
}