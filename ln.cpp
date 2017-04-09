#include <cstdlib>
#include <unistd.h>
#include <stdio.h>

int main(const int argc, const char * argv []){
  
  if(argc == 3){
    if(link(argv[1],argv[2]) == -1){
      perror("ln:");
      return EXIT_FAILURE;
    }
  }//create hard link
  else if(argc == 4){
    if(symlink(argv[2],argv[3]) == -1){
      perror("ln:");
      return EXIT_FAILURE;
    }
  }//create symlink
  else{
    char buf[BUFSIZ];
    setbuf(stdin, buf);
    printf("ln: invalid number of arguments");
  }//invalid args

  return EXIT_SUCCESS;
}
