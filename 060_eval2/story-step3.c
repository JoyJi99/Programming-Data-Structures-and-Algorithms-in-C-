#include "rand_story.h"

//program takes two command line arguments:
// 1. the word file
// 2. the story file
int main(int argc, char ** argv) {
    argCheck(argc, 3, 3, "wordFile storyFile");
    FILE * f1 = fopen(argv[1], "r");
    FILE * f2 = fopen(argv[2], "r");
    fNull(f1, 3, argv[1]);
    fNull(f2, 3, argv[2]);
    catarray_t * cats = parseCategories(f1);
    parseTemplate(f2, cats, 1);
    freeCatArr(cats);
    close(f1, 3, argv[1]);
    close(f2, 3, argv[2]);
    return EXIT_SUCCESS;
}
