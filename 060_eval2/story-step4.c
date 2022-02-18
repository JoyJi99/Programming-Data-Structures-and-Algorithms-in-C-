#include "rand_story.h"

//program takes two command line arguments:
// 1. the word file
// 2. the story file
//program takes an option "-n" indicating no reuse of words
int main(int argc, char ** argv) {
    if (argc == 3 && strcmp(argv[1], "-n") != 0) {
        FILE * f1 = fopen(argv[1], "r");
        FILE * f2 = fopen(argv[2], "r");
        fNull(f1, 4, argv[1]);
        fNull(f2, 4, argv[2]);
        catarray_t * cats = parseCategories(f1);
        parseTemplate(f2, cats, 1); //pass 1 to reuse words
        freeCatArr(cats);
        close(f1, 4, argv[1]);
        close(f2, 4, argv[2]);
    }
    else if (argc == 4 && strcmp(argv[1], "-n") == 0) {
        FILE * f1 = fopen(argv[2], "r");
        FILE * f2 = fopen(argv[3], "r");
        fNull(f1, 4, argv[2]);
        fNull(f2, 4, argv[3]);
        catarray_t * cats = parseCategories(f1);
        parseTemplate(f2, cats, 0); //pass 0 to refuse reuse words
        freeCatArr(cats);
        close(f1, 4, argv[2]);
        close(f2, 4, argv[3]);
    }
    else {
        fprintf(stderr, "Usage: ./story_step4 (-n) wordFile storyFile\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
