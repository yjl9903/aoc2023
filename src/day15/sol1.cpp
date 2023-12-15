#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

char buf[100000];

int main() {
  vector<string> steps;
  scanf("%s", buf);
  for (int i = 0, len = strlen(buf); i < len; i++) {
    int j = i;
    while (j < len && buf[j] != ',') j++;
    buf[j] = 0;
    steps.push_back(buf + i);
    i = j;
  }
  int sum = 0;
  for (string str: steps) {
    int cur = 0;
    for (char c: str) {
      cur += (int) c;
      cur *= 17;
      cur %= 256;
    }
    // printf("cur: %d\n", cur);
    sum += cur;
  }
  printf("%d\n", sum);
  return 0;
}