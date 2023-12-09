#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <string>
#include <vector>
#include <utility>
#include <map>

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
  if (c == 'J') return 11;
  if (c == 'T') return 10;
  return c - '0';
}

bool compare(string lhs, string rhs) {
  for (int i = 0; i < lhs.size(); i++) {
    int a = ord(lhs[i]);
    int b = ord(rhs[i]);
    if (a != b) return a < b;
  }
  return false;
}

int main() {
  vector<pair<string,int>> players;
  char hands[8]; int bid;
  while (scanf("%s %d", hands, &bid) == 2) {
    players.push_back({ hands, bid });
  }
  sort(players.begin(), players.end(), [&](auto& lhs, auto& rhs) {
    int cl = detect(lhs.first);
    int cr = detect(rhs.first);
    if (cl != cr) {
      return cl < cr;
    } else {
      return compare(lhs.first, rhs.first);
    }
  });
  int ans = 0;
  for (int i = 0; i < players.size(); i++) {
    ans += (i + 1) * players[i].second;
  }
  printf("%d\n", ans);
  return 0;
}