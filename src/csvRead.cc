#include <bits/stdc++.h>

using namespace std;

int main() {
  srand((int)time(0));

  string res;

  for (int row = 0; row < 27; row++) {
    for (int i = 0; i < 10; i++) {
      string tmp = to_string(rand() % 100);
      tmp += " ";
      res += tmp;
    }
    res += '\n';
  }


  FILE* filePtr = fopen("./demo.csv", "wr");

  fwrite(res.c_str(), strlen(res.c_str()), 1, filePtr);
}