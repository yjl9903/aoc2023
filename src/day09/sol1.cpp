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
    int ans = 0;
    // puts("----");
    while (true) {
      ans += a.back();
      // for (int x: a) printf("%d ", x);
      // puts("");
      vector<int> nxt;
      bool flag = true;
      for (int i = 1; i < a.size(); i++) {
        nxt.push_back(a[i] - a[i - 1]);
        if (a[i] != a[i - 1]) flag = false;
      }
      a = nxt;
      if (flag) break;
    }
    sum += ans;
    // printf("ans: %d\n", ans);
  }
  printf("%d\n", sum);
  return 0;
}