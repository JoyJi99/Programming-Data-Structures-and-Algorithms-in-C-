#include <stdio.h>
#include <stdlib.h>
size_t maxSeq(int * array, size_t n);
int seq_check(int * check_a, size_t m, size_t expected_max) {
  size_t max = maxSeq(check_a, m);
  if (max == expected_max) {
    printf("right ");
    return 1;
  }
  else {
    printf("wrong ");
    return 0;
  }
}

int main(void) {
  int data1[10] = {1, 2, 1, 3, 5, 8, 2, 4, 6, 9};
  int a = seq_check(data1, 10, 4);

  int data2[10] = {1, 1, 1, 1, 1, 8, 2, 4, 6, 9};
  int b = seq_check(data2, 10, 4);

  int data3[10] = {1, 2, 1, 3, 5, 8, 7, 6, 5, 4};
  int c = seq_check(data3, 10, 4);

  int data4[8] = {0, 10, 20, 3, 5, 8, 2, 4};
  int k = seq_check(data4, 8, 3);

  int data5[1] = {0};
  int m = seq_check(data5, 1, 1);

  int data6[4] = {-4, -3, -2, 0};
  int n = seq_check(data6, 4, 4);

  // int data7[4] = {1, 1, 0, 1};
  int p = seq_check(NULL, 0, 0);

  if (a + b + c + k + m + n + p == 7) {
    return EXIT_SUCCESS;
  }
  else {
    return EXIT_FAILURE;
  }
}
