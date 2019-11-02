#pragma once

#include "base.cpp"

enum Verdict {
  Accepted = 0,
  WrongAnswer = 1,
  PresentationError = 2,
  ProtocolViolation = 3,
  ProtocolLimitExceeded = 4,
  JudgeError = 127
};

#include "judge/judge-format.cpp"

// judge should exit(Verdict) if it finds any failures
void judge(fstream& fin, fstream& fsol, FormatJudge& fout);

int main(int argc, const char* argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s test.in test.sol\n", argv[0]);
    exit(JudgeError);
  }
  fstream fin(argv[1], ios::in);
  fstream fsol(argv[2], ios::in);
  FormatJudge fout;
  judge(fin, fsol, fout);
  cerr << "OK" << endl;
  return fout.judge();
}

