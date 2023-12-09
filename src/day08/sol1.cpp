#include <cstdio>
#include <cstring>
#include <map>
#include <set>
#include <utility>
#include <string>
#include <queue>

using namespace std;

char command[1024];

map<string, pair<string,string>> mp;

int main() {
  scanf("%s", command);
  char from[4], left[4], right[4];
  while (scanf("%s = (%[A-Z], %[A-Z])", from, left, right) == 3) {
    mp[from] = { left, right };
  }
  string cur = "AAA";
  int ans = 0;
  while (cur != "ZZZ") {
    for (int i = 0; command[i] != '\0'; i++) {
      ans++;
      if (command[i] == 'L') {
        cur = mp[cur].first;
      } else if (command[i] == 'R') {
        cur = mp[cur].second;
      }
    }
  }
  printf("%d\n", ans);
  // for (int i = 0; command[i] != '\0'; i++) {
  //   if (command[i] == 'L') {
  //     start = mp[start].first;
  //   } else if (command[i] == 'R') {
  //     start = mp[start].second;
  //   }
  // }
  // map<string,int> visited;
  // queue<string> q;
  // q.push(start);
  // visited[start] = 0;
  // while (!q.empty()) {
  //   auto cur = q.front();
  //   q.pop();
  //   if (!visited.count(mp[cur].first)) {
  //     visited[mp[cur].first] = visited[cur] + 1;
  //     q.push(mp[cur].first);
  //   }
  //   if (!visited.count(mp[cur].second)) {
  //     visited[mp[cur].second] = visited[cur] + 1;
  //     q.push(mp[cur].second);
  //   }
  // }
  // printf("%d\n", (int) strlen(command) + visited["ZZZ"]);
  return 0;
}