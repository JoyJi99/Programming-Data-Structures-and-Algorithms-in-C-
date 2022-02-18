#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

class Page {
public:
    std::string text;
    std::vector<std::pair<unsigned, std::string> > choices;
    bool result;
public:
    bool readPage(char * fileName);
    void readChoice(std::string str);
    void readResult(std::string str);
    void printPage();

};

void HandError(std::string errorInfo);
