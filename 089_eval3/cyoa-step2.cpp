#include "book.h"

int main(int argc, char * argv[]) {
    if(argc != 2) {
        HandError("Usage: ./cyoa-step2 directoryName");
    }
    Book book;
    book.readPages(argv[1]);
    book.checkPages();
    book.beginStory();
    return EXIT_SUCCESS;
}
