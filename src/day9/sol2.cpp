#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

char buf[8196];

int main() {
  int sum = 0;
  while (scanf("%[^\n]", buf) == 1) {
    getchar();
    stringstream line;
    line << buf;
    vector<int> a; int x;
    while (line >> x) {
      a.push_back(x);
    }
    vector<int> first;
    while (true) {
      first.push_back(a.front());
      vector<int> nxt;
      bool flag = true;
      for (int i = 1; i < a.size(); i++) {
        nxt.push_back(a[i] - a[i - 1]);
        if (a[i] != a[i - 1]) flag = false;
      }
      a = nxt;
      if (flag) break;
    }
    int ans = 0;
    first.push_back(0);
    reverse(first.begin(), first.end());
    for (int x: first) {
      ans = x - ans;
    }
    sum += ans;
  }
  printf("%d\n", sum);
  return 0;
}