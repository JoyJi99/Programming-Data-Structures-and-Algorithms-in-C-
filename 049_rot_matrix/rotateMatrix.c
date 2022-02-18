#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void rotate(FILE *f){
    int row = 0;
    int col = 0;
    int count = 0;
    char a[10][10];
    char c;
    while ( (c = fgetc(f)) != EOF ){
        if(row < 10) {
            if (c == '\n') {
                if (col != 10) {
                    perror("incorrect length of column");
                    exit(EXIT_FAILURE);
                }
                row++;
                col = 0;
            }
            else {
                a[col][9-row] = c;
                col++;
            }
        }
        count++;
        if(count > 110){
            perror("incorrect length of row");
            exit(EXIT_FAILURE);
        }
    }
    if(row <= 9){
        perror("incorrect length of row");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < 10; i++){
	for (int j = 0; j < 10; j++){
            printf("%c", a[i][j]);
	}
        printf("\n");
    }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Useage: ./rotateMatrix filename\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file!");
    return EXIT_FAILURE;
  }
  rotate(f);
}
