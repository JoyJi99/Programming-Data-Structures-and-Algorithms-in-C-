#include "rand_story.h"

int main(int argc, char ** argv){
    argCheck(argc, 2, 2, "wordFile");
    FILE * f = fopen(argv[1], "r");
    fNull(f, 2, argv[1]);
    catarray_t * cats = parseCategories(f);
    printWords(cats);
    freeCatArr(cats);
    close(f, 2, argv[1]);
    return EXIT_SUCCESS;
}
