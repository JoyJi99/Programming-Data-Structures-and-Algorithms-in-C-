#include "book.h"

int main(int argc, char * argv[]) {
    if (argc != 2) {
        HandError("Usage: ./cyoa-step4 directoryName");
    }
    Book book;
    book.readPages(argv[1]);
    book.checkPages();
    std::vector<unsigned> valiWinPages = book.findValidWin();
    book.printWin(valiWinPages);
    return EXIT_SUCCESS;
}
