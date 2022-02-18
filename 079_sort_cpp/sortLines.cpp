#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::istream & read_into(std::string & s, T & stream) {
  return getline(stream, s);
}

template<typename T>
void sort_file(T & stream) {
  std::string s;
  std::vector<std::string> lines;
  while (read_into<std::istream>(s, stream)) {
    lines.push_back(s);
  }
  if (!stream.eof() && !stream) {
    std::cerr << "Error reading file";
  }
  std::sort(lines.begin(), lines.end());
  for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); ++it) {
    std::cout << *it << std::endl;
  }
  return;
}

int main(int argc, char ** argv) {
  std::string s;
  if (argc == 1) {
    sort_file<std::istream>(std::cin);
    exit(EXIT_SUCCESS);
  }
  else {
    for (int i = 1; i < argc; i++) {
      std::ifstream ifs(argv[i]);
      if (!ifs) {
        std::cerr << "File opening failed" << std::endl;
        exit(EXIT_FAILURE);
      }
      sort_file<std::ifstream>(ifs);
    }
  }
  exit(EXIT_SUCCESS);
}
