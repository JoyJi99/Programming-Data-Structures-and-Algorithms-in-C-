#include <iostream>
#include "bstset.h"

using namespace std;
int main(){
 BstSet<int> set;
    set.add(1);
    set.add(2);
    set.add(3);
    set.in();
    if(set.contains(1)){
      cout << "contains1"<<endl;
    }
    set.remove(3);
     set.in();


}
