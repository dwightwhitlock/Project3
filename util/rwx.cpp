#include "./fileType.cpp"
#include <sys/stat.h>
#include <unistd.h>
#include <string>

using std::string;

string get_rwx(int mode){

  string rwx = "";
  
  int modeUser = mode & S_IRWXU;
  int modeGroup = mode & S_IRWXG;
  int modeOther = mode & S_IRWXO;

  string fileT = fileType(mode);

  //File Type Checking
  if(fileT == "socket")
    rwx.push_back('s');
  if(fileT == "regular file")
    rwx.push_back('-');
  if(fileT == "symbolic link")
    rwx.push_back('l');
  if(fileT == "block device")
    rwx.push_back('b');
  if(fileT == "directory")
    rwx.push_back('d');
  if(fileT == "character device")
    rwx.push_back('c');
  if(fileT == "FIFO")
    rwx.push_back('f');

  //User permission
  if(modeUser == S_IRWXU)
    rwx.append("rwx");
   else if(modeUser == S_IRUSR)
    rwx.append("r--");    
   else if(modeUser == (S_IRUSR | S_IWUSR))
    rwx.append("rw-");
   else if (modeUser == (S_IWUSR))
    rwx.append("-w-");
   else if (modeUser == (S_IWUSR | S_IXUSR))
    rwx.append("-wx");
   else if (modeUser == (S_IXUSR))
    rwx.append("--x");
   else if (modeUser == (S_IXUSR | S_IRUSR))
    rwx.append("r-x");
   else
     rwx.append("---");
  
  //Group permissions
  if(modeGroup == S_IRWXG)
    rwx.append("rwx");
  else if(modeGroup == S_IRGRP)
    rwx.append("r--");    
  else if(modeGroup == (S_IRGRP | S_IWGRP))
    rwx.append("rw-");
  else if (modeGroup == (S_IWGRP))
    rwx.append("-w-");
  else if (modeGroup == (S_IWGRP | S_IXGRP))
    rwx.append("-wx");
  else if (modeGroup == (S_IXGRP))
    rwx.append("--x");
  else if (modeGroup == (S_IXGRP | S_IRGRP))
    rwx.append("r-x");
  else
    rwx.append("---");

  //Other permission
  if(modeOther == S_IRWXO)
    rwx.append("rwx");
  else if(modeOther == S_IROTH)
    rwx.append("r--");    
  else if(modeOther == (S_IROTH | S_IWOTH))
    rwx.append("rw-");
  else if (modeOther == (S_IWOTH))
    rwx.append("-w-");
  else if (modeOther == (S_IWOTH | S_IXOTH))
    rwx.append("-wx");
  else if (modeOther == (S_IXOTH))
    rwx.append("--x");
  else if (modeOther == (S_IXOTH | S_IROTH))
    rwx.append("r-x");
  else
    rwx.append("---");
    
 return rwx;

}
