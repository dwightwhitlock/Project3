#include <unistd.h>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <limits.h>

int main(){
  char * dir;
  char buff[PATH_MAX+1];

  dir = getcwd(buff,PATH_MAX+1);
  std::cout << dir << std::endl;
  
}
