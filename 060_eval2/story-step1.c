#include "rand_story.h"

int main(int argc, char ** argv){
    argCheck(argc, 2, 1, "storyFile");
    FILE * f = fopen(argv[1], "r");
    fNull(f, 1, argv[1]);
    parseTemplate(f, NULL, 1);
    close(f, 1, argv[1]);
    return EXIT_SUCCESS;
}
