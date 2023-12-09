#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <set>
#include <queue>

using namespace std;

int detect(string& hands) {
  map<char, int> kinds;
  for (char c: hands) {
    kinds[c]++;
  }
  if (kinds.size() == 1) {
    return 7;
  } else if (kinds.size() == 2) {
    int cnt = 0;
    for (char c: hands) if (c == hands[0]) cnt++;
    if (cnt == 1 || cnt == 4) {
      return 6;
    } else {
      return 5;
    }
  } else if (kinds.size() == 5) {
    return 1;
  } else {
    bool flag = false;
    for (auto& e: kinds) if (e.second == 3) flag = true;
    if (flag) return 4;
    int cnt = 0;
    for (auto& e: kinds) if (e.second == 2) cnt++;
    if (cnt == 2) {
      return 3;
    } else if (cnt == 1) {
      return 2;
    } else {
      assert(false);
    }
  }
}

int ord(char c) {
  if (c == 'A') return 14;
  if (c == 'K') return 13;
  if (c == 'Q') return 12;
  if (c == 'J') return 1;
  if (c == 'T') return 10;
  return c - '0';
}

bool compare(string lhs, string rhs) {
  int cl = detect(lhs);
  int cr = detect(rhs);
  if (cl != cr) return cl < cr;
  for (int i = 0; i < lhs.size(); i++) {
    int a = ord(lhs[i]);
    int b = ord(rhs[i]);
    if (a != b) return a < b;
  }
  return false;
}

bool compare_order(string lhs, string rhs) {
  for (int i = 0; i < lhs.size(); i++) {
    int a = ord(lhs[i]);
    int b = ord(rhs[i]);
    if (a != b) return a < b;
  }
  return false;
}

string transform(string t) {
  int cnt = 0;
  for (char c: t) if (c == 'J') cnt++;
  if (cnt == 0) return t;
  string ans = t;
  set<string> visited;
  queue<string> q;
  q.push(t);
  while (!q.empty()) {
    auto cur = q.front();
    q.pop();
    if (compare(ans, cur)) ans = cur;
    for (int i = 0; i < cur.length(); i++) {
      if (cur[i] != 'J') continue;
      for (char c: { '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'K', 'Q', 'J', 'A' }) {
        string x = cur;
        x[i] = c;
        if (!visited.count(x)) {
          visited.insert(x);
          q.push(x);
        }
      }
    }
  }
  return ans;
}

int main() {
  vector<pair<pair<string,string>,int>> players;
  char hands[8]; int bid;
  while (scanf("%s %d", hands, &bid) == 2) {
    players.push_back({ { hands, transform(hands) }, bid });
    // if (hands != transform(hands)) {
    //   printf("%s -> %s\n", hands, transform(hands).c_str());
    // }
  }
  sort(players.begin(), players.end(), [&](auto& lhs, auto& rhs) {
    int cl = detect(lhs.first.second);
    int cr = detect(rhs.first.second);
    if (cl != cr) return cl < cr;
    return compare_order(lhs.first.first, rhs.first.first);
  });
  int ans = 0;
  for (int i = 0; i < players.size(); i++) {
    ans += (i + 1) * players[i].second;
  }
  printf("%d\n", ans);
  return 0;
}