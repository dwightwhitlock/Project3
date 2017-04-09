#include <cstdlib>
#include <unistd.h>
#include <iostream>

int main(){

  for(int i = 0; environ[i] != nullptr; ++i){
    printf("%s\n",environ[i]);
  }

}
