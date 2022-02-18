#include "page.h"

int main(int argc, char * argv[]) {
    if(argc != 2) {
        HandError("Usage: ./cyoa-step1 pageFile");
    }
    Page page;
    if(page.readPage(argv[1])) {
        page.printPage();
    }
    else {
        HandError("Can't open file");
    }
    return EXIT_SUCCESS;
}
