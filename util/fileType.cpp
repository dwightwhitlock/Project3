#include <unistd.h>
#include <sys/stat.h>
#include <string>

using std::string;

string fileType(int mode){

  int modeMasked = mode & S_IFMT;
  
  switch(modeMasked){

  case S_IFSOCK:
    return "socket";
    break;

  case S_IFLNK:
    return "symbolic link";
    break;
    
  case S_IFREG:
    return "regular file";
    break;

  case S_IFBLK:
    return "block device";
    break;

  case S_IFDIR:
    return "directory";
    break;

  case S_IFCHR:
    return "character device";
    break;

  case S_IFIFO:
    return "FIFO";
    break;

  default:
    return "ERROR";
    break;

  }
}
