#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <string>
#include <utility>

using namespace std;

int n, m;
int vis[1024];
char buf[1024];

int main(int argc, char* argv[]) {
  int xs = atoi(argv[1]);
  for (int i = 1; i < 1024; i++) vis[i] = xs - 1;

  int row = 0;
  vector<pair<int,int>> galaxy;
  while (scanf("%[^\n]", buf) == 1) {
    getchar();
    n++;
    m = strlen(buf);
    bool empty = true;
    for (int i = 0; i < m; i++) {
      if (buf[i] == '#') {
        empty = false;
        vis[i + 1] = 0;
        galaxy.push_back({ n + row, i + 1 });
      }
    }
    if (empty) row += xs - 1;
  }
  for (int i = 1; i <= m; i++) vis[i] += vis[i - 1];
  for (auto& p: galaxy) p.second += vis[p.second];
  long long ans = 0;
  for (int i = 0; i < galaxy.size(); i++) {
    for (int j = 0; j < i; j++) {
      ans += abs(galaxy[i].first - galaxy[j].first) + abs(galaxy[i].second - galaxy[j].second);
    }
  }
  printf("%lld\n", ans);
  return 0;
}