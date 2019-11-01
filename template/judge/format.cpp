class FormatJudge {
 public:
  template<class T>
  FormatJudge& operator>>(T& arg) {
    cin >> arg;
    return *this;
  }
  template<class T>
  FormatJudge& operator<<(T arg) {
    stringstream ss;
    ss << arg;
    string fmt = ss.str();
    for (int i=0; i<(int)fmt.size(); ++i) {
      if (isSpace(fmt[i])) {
        int next = cin.peek();
        if (next == fmt[i]) {
          getCh();
          continue;
        }
        if (!hasPE) {
          pe << "Did not match whitespace" << endl;
          printExpected(pe, fmt[i]);
          pe << "from '" << fmt << "' at " << i << "," << endl;
          printGot(pe, next, /*peek*/ true);
          hasPE = true;
        }
      } else {
        int next = getNonSpaceCh();
        if (next == fmt[i])
          continue;
        cerr << "Bad output" << endl;
        printExpected(cerr, fmt[i]);
        cerr << "from '" << fmt << "' at " << i << "," << endl;
        printGot(cerr, next);
        exit(WrongAnswer);
      }
    }
    return *this;
  }
  FormatJudge& getline(string& s) {
    std::getline(cin, s);
    line = nextLine; col = nextCol;
    nextLine++;
    nextCol = 1;
    return *this;
  }
  int judge() {
    int c = getNonSpaceCh();
    if (c != EOF) {
      cerr << "Too much output" << endl;
      printExpected(cerr, EOF);
      printGot(cerr, c);
      exit(WrongAnswer);
    }
    if (hasPE) {
      cerr << pe.str() << endl;
      return PresentationError;
    }
    return Accepted;
  }
 private:
  void printChar(ostream& os, int c) {
    if (c == EOF)
      os << "EOF";
    else
      os << "'" << (char)c << "' ((char)" << c << ")";
  }
  void printExpected(ostream& os, int c) {
    os << "expected ";
    printChar(os, c);
    os << endl;
  }
  void printGot(ostream& os, int c, bool peek=false) {
    os << "got ";
    printChar(os, c);
    os << " at ";
    os << (peek ? nextLine : line) << ":" << (peek ? nextCol : col);
    os << endl;
  }
  int getCh() {
    line = nextLine; col = nextCol;
    int ans = cin.get();
    if (ans == '\n') {
      nextLine++;
      nextCol = 1;
    } else {
      nextCol++;
    }
    return ans;
  }
  int getNonSpaceCh() {
    int c = getCh();
    if (!isSpace(c))
      return c;
    if (!hasPE) {
      pe << "Unexpected whitespace" << endl;
      pe << "got "; printChar(pe, c); pe << endl; pe << " ";
      pe << "at " << line << ":" << col << ": ";
      hasPE = true;
    }
    do {
      c = getCh();
    } while (isSpace(c));
    return c;
  }
  bool isSpace(int c) {
    return c >= 0 && isspace((char)c, cin.getloc());
  }
  bool hasPE; stringstream pe;
  int line = 1, nextLine = 1;
  int col = 1, nextCol = 1;
};
