#include <stdio.h>
#include <cstdlib>
#include "readFreq.h"
#include <fstream>
#include <iostream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256 ) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  uint64_t * arr = new uint64_t[257]();
  std::ifstream is;
  is.open(fname);
  if (is.fail()) {
    std::cerr << "error opening" << fname << std::endl;
    exit(EXIT_FAILURE);
  }

  int c;
  while ((c = is.get()) != EOF) {
    arr[c] += 1;
  }
  arr[256] += 1;
  is.close();
  return arr;
}
