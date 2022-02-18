#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "function.h"

class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class identityFunction : public Function<int, int> {
 public:
  int invoke(int arg) { return arg; }
};

class minus1Function : public Function<int, int> {
 public:
  int invoke(int arg) { return -1; }
};

class p2Function : public Function<int, int> {
 public:
  int invoke(int arg) { return 1; }
};

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

int binarySearchForZero(Function<int, int> * f, int low, int high);
void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int maxinvoc;
  if (high > low) {
    maxinvoc = log(high - low) / log(2) + 1;
  }
  else {
    maxinvoc = 1;
  }
  CountedIntFn * countf = new CountedIntFn(maxinvoc, f, mesg);

  int answer = binarySearchForZero(countf, low, high);
  //std::cout << answer << std::endl;
  if (answer != expected_ans) {
    std::cerr << "wrong answer" << std::endl;
    exit(EXIT_FAILURE);
  }
  delete countf;
}

int main() {
  SinFunction f;
  minus1Function nf;
  p2Function pf;
  identityFunction lf;
  check(&lf, 2, 100000000, 2, "positive identityFunction");
  //std::cout << 1 << std::endl;
  check(&lf, 0, 0, 0, "from 0 to 0 to 0");
  //std::cout << 2 << std::endl;
  check(&lf, 10, 10, 10, "from 10 to 10 to 10");
  //std::cout << 3 << std::endl;
  check(&lf, -1, 10000000, 0, "identityFunction");
  //std::cout << 4 << std::endl;
  check(&f, 0, 150000, 52359, "sinFunction");
  //std::cout << 5 << std::endl;
  check(&nf, 1, 5, 4, "minus1Function");
  //std::cout << 6 << std::endl;
  check(&pf, 1, 10, 1, "positive2Function");
  //std::cout << 7 << std::endl;
  check(&lf, -99999, 10000000, 0, "identityFunction");
  //std::cout << 8 << std::endl;
  check(&lf, -99999999, -1000, -1001, "negative identityFunction");
}
