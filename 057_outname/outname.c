#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  const char * suffix = ".counts";
  unsigned len = strlen(inputName) + strlen(suffix) + 1; 
  char * ans = malloc(len * sizeof(*ans)); 
  snprintf(ans, len, "%s%s", inputName, suffix);//目标字符串，拷贝size
  return ans;
}
