#include <bits/stdc++.h>
using namespace std;

enum Verdict {
  Accepted = 0,
  WrongAnswer = 1,
  PresentationError = 2,
  ProtocolViolation = 3,
  ProtocolLimitExceeded = 4,
  JudgeError = 127
};

void judge(fstream& fin, fstream& fsol);

int main(int argc, const char* argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s test.in test.sol\n", argv[0]);
    exit(JudgeError);
  }
  fstream fin(argv[1], ios::in);
  fstream fsol(argv[2], ios::in);
  judge(fin, fsol);
}

