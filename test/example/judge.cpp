#include "judge/base.cpp"
#include "judge/format.cpp"

void judge(fstream& fin, fstream& fsol) {
  FormatJudge fout;

  cout << fin.rdbuf();

  int sol;
  fsol >> sol;
  int ans;
  fout >> ans << '\n';
  cerr << "Expected " << sol << ", got " << ans << endl;
  if (ans != sol) {
    cerr << "Incorrect answer" << endl;
    exit(WrongAnswer);
  }
  cerr << "OK" << endl;
  exit(fout.judge());
}

