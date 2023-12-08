#include <cstdio>
#include <cstring>
#include <map>
#include <set>
#include <utility>
#include <string>
#include <queue>
#include <numeric>
#include <vector>

using namespace std;

char command[1024];

map<string, pair<string,string>> mp;

int main() {
  scanf("%s", command);
  char from[4], left[4], right[4];
  vector<string> start;
  while (scanf("%s = (%[A-Z], %[A-Z])", from, left, right) == 3) {
    mp[from] = { left, right };
    if (from[2] == 'A') {
      start.push_back(from);
    }
  }
  long long ans = 1;
  for (auto st: start) {
    string cur = st;
    int cnt = 0;
    set<string> visited;
    while (cur.back() != 'Z') {
      for (int i = 0; command[i] != '\0'; i++) {
        cnt++;
        if (command[i] == 'L') {
          cur = mp[cur].first;
        } else if (command[i] == 'R') {
          cur = mp[cur].second;
        }
      }
    }
    ans = 1ll * ans * cnt / std::gcd(ans, cnt);
  }
  printf("%lld\n", ans);
  return 0;
}