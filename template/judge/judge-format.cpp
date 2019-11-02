#pragma once

#include "log.cpp"

// FormatJudge is a wrapper of cin for strictly formatted input,
// setting PresentationError if whitespace is not correct,
// and exiting with WrongAnswer if non-whitespace is incorrect
class FormatJudge {
 public:
  // operator>> reads arg from cin
  // Should be used for parsing an unknown value
  template<class T>
  FormatJudge& operator>>(T& arg);
  // operator<< reads from cin expecting to see arg
  // Should be used for parsing expected values and formatting
  template<class T>
  FormatJudge& operator<<(T arg);
  // getline reads s from cin
  // Should be used for parsing unknown whitespace
  FormatJudge& getline(string& s);
  // judge reads from cin expecting to see EOF,
  // and returns PresentationError or Accepted.
  // Should be called when finalizing judging
  int judge();
  // printFilePos outputs "at line:col" to os
  // Should be called when reporting a failure
  void printFilePos(ostream& os);
 private:
  void advance();
  void ws();
  void printChar(ostream& os, int c);
  void printExpected(ostream& os, int c);
  void printGot(ostream& os);
  bool isSpace(int c);

  bool hasPE; stringstream pe;
  int line = 1, nextLine = 1;
  int col = 1, nextCol = 1;
};


template<class T>
FormatJudge& FormatJudge::operator>>(T& arg) {
  ws();
  string s;
  cin >> s;
  stringstream ss(s);
  ss >> arg;
  if (!ss) {
    cerr << "Bad output" << endl;
    cerr << "expected one " << cp_log::demangledType(arg) << endl;
    cerr << "got '" << s << "' ";
    printFilePos(cerr);
    exit(WrongAnswer);
  }
  col += (int)s.size();
  return *this;
}

template<class T>
FormatJudge& FormatJudge::operator<<(T arg) {
  stringstream ss;
  ss << arg;
  string fmt = ss.str();
  for (int i=0; i<(int)fmt.size(); ++i) {
    if (isSpace(fmt[i])) {
      if (cin.peek() == fmt[i]) {
        advance();
        continue;
      }
      if (!hasPE) {
        pe << "Did not match whitespace" << endl;
        printExpected(pe, fmt[i]);
        pe << "from '" << fmt << "' at " << i << "," << endl;
        printGot(pe);
        hasPE = true;
      }
    } else {
      ws();
      if (cin.peek() == fmt[i]) {
        advance();
        continue;
      }
      cerr << "Bad output" << endl;
      printExpected(cerr, fmt[i]);
      cerr << "from '" << fmt << "' at " << i << "," << endl;
      printGot(cerr);
      exit(WrongAnswer);
    }
  }
  return *this;
}

FormatJudge& FormatJudge::getline(string& s) {
  std::getline(cin, s);
  line = nextLine; col = nextCol;
  nextLine++;
  nextCol = 1;
  return *this;
}

int FormatJudge::judge() {
  ws();
  if (cin.peek() != EOF) {
    cerr << "Too much output" << endl;
    printExpected(cerr, EOF);
    printGot(cerr);
    exit(WrongAnswer);
  }
  if (hasPE) {
    cerr << pe.str() << endl;
    return PresentationError;
  }
  return Accepted;
}

void FormatJudge::printFilePos(ostream& os) {
  os << "at ";
  os << line << ":" << col;
}

void FormatJudge::advance() {
  if (cin.get() == '\n') {
    line++;
    col = 1;
  } else {
    col++;
  }
}

void FormatJudge::ws() {
  while (isSpace(cin.peek())) {
    if (!hasPE) {
      pe << "Unexpected whitespace" << endl;
      printGot(pe);
      hasPE = true;
    }
    advance();
  }
}

void FormatJudge::printChar(ostream& os, int c) {
  if (c == EOF)
    os << "EOF";
  else
    os << "'" << (char)c << "' ((char)" << c << ")";
}

void FormatJudge::printExpected(ostream& os, int c) {
  os << "expected ";
  printChar(os, c);
  os << endl;
}

void FormatJudge::printGot(ostream& os) {
  os << "got ";
  printChar(os, cin.peek());
  os << " ";
  printFilePos(os);
  os << endl;
}

bool FormatJudge::isSpace(int c) {
  return c >= 0 && isspace((char)c, cin.getloc());
}

