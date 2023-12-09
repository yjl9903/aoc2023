#include <cstdio>
#include <cassert>
#include <cstring>

using namespace std;

char buf[1024];

int main() {
  int sum = 0;
  while (scanf("%s", buf + 1) == 1) {
    int n = strlen(buf + 1);
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
      if (buf[i] >= '0' && buf[i] <= '9') {
        sum += 10 * (buf[i] - '0');
        cnt++;
        break;
      }
    }
    for (int i = n; i >= 1; i--) {
      if (buf[i] >= '0' && buf[i] <= '9') {
        sum += (buf[i] - '0');
        cnt++;
        break;
      }
    }
    assert(cnt == 2);
  }
  printf("%d\n", sum);
  return 0;
}