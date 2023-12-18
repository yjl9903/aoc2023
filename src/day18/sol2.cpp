#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

const int maxn = 21000000;

int a[maxn * 4], tag[maxn * 4];
void update(int L, int R, int l, int r, int rt) {
  if (L <= l && r <= R) {
    a[rt] = r - l + 1 - a[rt];
    tag[rt] ^= 1;
    return;
  }
  int m = (l + r) / 2;
  if (tag[rt]) {
    tag[rt * 2] ^= 1;
    tag[rt * 2 + 1] ^= 1;
    a[rt * 2] = m - l + 1 - a[rt * 2];
    a[rt * 2 + 1] = r - (m + 1) + 1 - a[rt * 2 + 1];
    tag[rt] = 0;
  }
  if (L <= m) update(L, R, l, m, rt * 2);
  if (R > m) update(L, R, m + 1, r, rt * 2 + 1);
  a[rt] = a[rt * 2] + a[rt * 2 + 1];
}

int main() {
  vector<pair<char,int>> cmds;
  char dir[2], rgb[32];
  int len;
  while (scanf("%s %d %s", dir, &len, rgb) == 3) {
    // cmds.push_back({ dir[0], len });
    len = 0;
    for (int i = 2; i <= 6; i++) {
      len *= 16;
      if (rgb[i] >= '0' && rgb[i] <= '9') len += rgb[i] - '0';
      else len += rgb[i] - 'a' + 10;
    }
    char d = 'R';
    if (rgb[7] == '0') d = 'R';
    else if (rgb[7] == '1') d = 'D';
    else if (rgb[7] == '2') d = 'L';
    else if (rgb[7] == '3') d = 'U';
    cmds.push_back({ d, len });
  }

  int cx = 0, cy = 0;
  int nl = 0, nr = 0, mu = 0, md = 0;

  long long ans = 0, border = 0;
  vector<pair<int,pair<int,int>>> lines;
  for (auto& cmd: cmds) {
    int dx = 0, dy = 0;
    if (cmd.first == 'U') dx = -1;
    else if (cmd.first == 'L') dy = -1;
    else if (cmd.first == 'D') dx = 1;
    else if (cmd.first == 'R') dy = 1;
    
    if (cmd.first == 'U' || cmd.first == 'D') {
      int L = cx, R = cx + dx * cmd.second;
      if (L > R) swap(L, R);
      lines.push_back({ cy, { L, R } });
    }
    
    cx += dx * cmd.second;
    cy += dy * cmd.second;
    border += cmd.second;
    nl = min(nl, cx);
    nr = max(nr, cx);
    mu = min(mu, cy);
    md = max(md, cy);
  }
  sort(lines.begin(), lines.end());
  // printf("%d %d\n", nl, nr);
  for (int y = mu, i = 0; y <= md; y++) {
    while (i < lines.size() && lines[i].first == y) {
      update(lines[i].second.first - nl + 1, lines[i].second.second - 1 - nl + 1, 1, nr - nl + 1, 1);
      i++;
    }
    ans += a[1];
    // printf("%d: %d\n", y, a[1]);
  }
  printf("%lld\n", ans + (border / 2 + 1));
  return 0;
}