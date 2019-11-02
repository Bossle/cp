#include "judge/judge-base.cpp"

void judge(fstream& fin, fstream& fsol, FormatJudge& fout) {
  cout << fin.rdbuf() << flush;
  fout << fsol.rdbuf();
}

