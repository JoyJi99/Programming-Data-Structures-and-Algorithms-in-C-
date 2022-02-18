#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int * countChar(FILE * f, int * count){
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      c -= 'a';
      if ((c >= 0) && (c < 26)) {
        count[c] += 1;
      }
      else {
        printf("invalid character");
      }
    }
  }
  return count;
}

int maxChar(int * count){
  int max = 0;
  for (int i = 0; i < 26; i++) {
    if (count[i] > count[max]) {
      max = i;
    }
  }
  return max;
}

int main(int argc, char ** argv){
  if (argc != 2) {
    fprintf(stderr, "Usage: break inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  int count[26] = {0};
  int * count_res = countChar(f, count);
  int max = maxChar(count_res);

  int key = (max - 4 + 26) % 26;
  fprintf(stdout, "%d\n", key);

  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
