#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <utility>

using namespace std;

char buf[100000];

int hsh(string s) {
  int cur = 0;
  for (char c: s) {
    cur += (int) c;
    cur *= 17;
    cur %= 256;
  }
  return cur;
}

struct Box {
  vector<pair<string,int>> data;

  void pop(string label) {
    for (int i = 0; i < data.size(); i++) {
      if (data[i].first == label) {
        data.erase(data.begin() + i);
      }
    }
  }

  void push(string label, int len) {
    for (auto& entry: data) {
      if (entry.first == label) {
        entry.second = len;
        return;
      }
    }
    data.push_back({ label, len });
  }
} box[256];

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
  for (string step: steps) {
    if (step.back() == '-') {
      string label = step.substr(0, (int) step.size() - 1);
      // printf("Pop %s (%d)\n", label.c_str(), hsh(label));
      box[hsh(label)].pop(label);
    } else {
      int len = step.back() - '0';
      string label = step.substr(0, (int) step.size() - 2);
      // printf("Push %s (%d) %d\n", label.c_str(), hsh(label), len);
      box[hsh(label)].push(label, len);
    }
  }
  int ans = 0;
  for (int i = 0; i < 256; i++) {
    for (int j = 0; j < box[i].data.size(); j++) {
      ans += (i + 1) * (j + 1) * box[i].data[j].second;
    }
  }
  printf("%d\n", ans);
  return 0;
}
// rn=1,cm-,qp=3,cm=2,qp-,pc=4,ot=9,ab=5,pc-,pc=6,ot=7