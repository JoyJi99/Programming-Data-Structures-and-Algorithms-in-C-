#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high){
  if((low + 1) >= high){
    return low;
  }
  int mid = (low + high) / 2;
  int target = f->invoke(mid);
  if (target == 0){
    return mid;
  }
  else if(target > 0){
    return binarySearchForZero(f, low, mid);
  }
  else{
    return binarySearchForZero(f, mid, high);
  }
}
