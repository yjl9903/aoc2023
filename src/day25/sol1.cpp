#include <cstdio>
#include <cstring>
#include <cassert>
#include <sstream>
#include <map>
#include <string>
#include <vector>

using namespace std;

const int maxn = 10000;

int cnt, ecnt;
map<string,int> ids;
int id(string s) {
  if (ids.count(s)) {
    return ids[s];
  } else {
    return ids[s] = ++cnt;
  }
}

bool skip[maxn];
vector<pair<int,int>> edges[maxn];

namespace Graph {
  int ans, br, tot, siz, dfn[maxn], low[maxn], dep[maxn], fa[maxn];
  void dfs(int p, int old) {
    siz++;
    dfn[p] = low[p] = ++tot;
    dep[p] = dep[old] + 1;
    for (auto& e: edges[p]) {
      if (skip[e.second]) continue;
      int v = e.first;
      if (v == old) continue;
      if (!dfn[v]) {
        fa[v] = p;
        dfs(v, p);
        low[p] = min(low[p], low[v]);
        if (low[v] > dfn[p]) {
          ans = e.second;
          br++;
        }
      } else low[p] = min(low[p], dfn[v]);
    }
  }
  int run() {
    br = tot = siz = 0;
    memset(dfn, 0, sizeof dfn);
    memset(low, 0, sizeof low);
    memset(dep, 0, sizeof dep);
    memset(fa, 0, sizeof fa);
    for (int i = 1; i <= cnt; i++) {
      if (!dfn[i]) dfs(i, 0);
    }
    if (br > 0) {
      if (br != 1) {
        return false;
      }
      int cut = ans;
      skip[ans] = true;
      br = tot = siz = 0;
      memset(dfn, 0, sizeof dfn);
      memset(low, 0, sizeof low);
      memset(dep, 0, sizeof dep);
      memset(fa, 0, sizeof fa);
      dfs(1, 0);
      skip[ans] = false;
      return siz * (cnt - siz);
    }
    return br > 0;
  }
}

int main() {
  char buf[64];
  while (scanf("%[^\n]", buf) == 1) {
    getchar();
    int split = 0;
    while (buf[split] && buf[split] != ':') split++;
    buf[split] = '\0';
    stringstream ss(buf + split + 1);
    // printf("%s: ", buf);
    char nxt[16];
    while (ss >> nxt) {
      // printf("%s ", nxt);
      edges[id(buf)].push_back({ id(nxt), ++ecnt });
      edges[id(nxt)].push_back({ id(buf), ecnt });
    }
    // puts("");
  }

  for (int i = 1; i <= ecnt; i++) {
    for (int j = i + 1; j <= ecnt; j++) {
      skip[i] = true;
      skip[j] = true;
      int ans = Graph::run();
      if (ans) {
        // Find: 2017 3015 -> 562912
        printf("Find: %d %d -> %d\n", i, j, ans);
        return 0;
      }
      skip[i] = false;
      skip[j] = false;
    }
  }

  return 0;
}
