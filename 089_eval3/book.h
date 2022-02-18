#include <set>
#include <queue>
#include <stack>
#include <sstream>
#include "page.h"

//a book which includes all the pages read in
class Book {
private:
    std::vector<Page> pages;
    std::vector<unsigned> winPages;
public:
    void readPages(char * path);
    void checkPages();
    void findWin();
    std::vector<unsigned> findLose();
    void beginStory();
    int depth(unsigned pageNum);
    void printDepth();
    std::vector<unsigned> findValidWin();
    std::vector<std::vector<unsigned> > winPath(unsigned pageNum);
    void printWin(std::vector<unsigned> winPages);
};
