#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>
#include "util/rwx.cpp"
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <dirent.h>
#include <cerrno>
#include <getopt.h>
#include <cstring>
#include <pwd.h>
#include <grp.h>
#include <iostream>

using std::string;
using std::cout;
using std::endl;


void listLongFiles(char *, int, int);
void printFormatted(char *, struct stat &, int);

int BLOCKS;
int totalPrinted;

int main(int argc, char *  argv[]){

  int aflag = 0;
  int lflag = 0;
  int index;

  opterr = 0;

  int c;

  while((c = getopt (argc, argv, "alc:")) != -1){
    switch(c){

    case 'a':
      aflag = 1;
      break;
      
    case 'l':
      lflag = 1;
      break;

    case '?':
      fprintf(stderr, "Unknown option. \n");
      return EXIT_FAILURE;

    default:
      return EXIT_FAILURE;

    }
  }

  char thisDir[] = ".";

  if(optind == argc){
    listLongFiles(thisDir,aflag,lflag);
    return EXIT_SUCCESS;
  }

  for(index = optind; index < argc; ++index){
    listLongFiles(argv[index],aflag,lflag);
  }//for
  
  return EXIT_SUCCESS;
}

void listLongFiles(char * file, int aflag, int lflag){

  struct stat fileInfo;

  if(-1 == stat(file, &fileInfo)){
    perror(file);
    exit(EXIT_FAILURE);
  } //stat for mode

  if(S_ISDIR(fileInfo.st_mode) == 0){

    if(lflag == 1){
      printFormatted(file,fileInfo,1);
      return;
    } else {
      printf("%s\n",file);
      return;
    }

  }//if

  

  DIR * dir;
  struct dirent * entry;
  int count = 0;
  char * ptrC;

  dir = opendir(file);


  while((entry = readdir(dir)) != nullptr){
    
    if(-1 == stat(entry->d_name, &fileInfo)){
      perror(entry->d_name);
      exit(EXIT_FAILURE);
    } //stat for mode
    
    if(((ptrC = strchr(entry->d_name,'.'))-entry->d_name) == 0){

      if(aflag != 1){
	continue;
      }//if

    }//if

    BLOCKS += fileInfo.st_blocks;
  }//while

  count = 0;
  dir = opendir(file);

  while((entry = readdir(dir)) != nullptr){
    
    if(-1 == stat(entry->d_name, &fileInfo)){
      perror(entry->d_name);
      exit(EXIT_FAILURE);
    } //stat for mode
    
    if(((ptrC = strchr(entry->d_name,'.'))-entry->d_name) == 0){

      if(aflag != 1){
	continue;
      }//if

    }//if

    if(count == 0 && lflag == 0)
      printf("%s",entry->d_name);

    else if(count > 0 && lflag == 0)
      printf("  %s",entry->d_name);

    else{
      printFormatted(entry->d_name,fileInfo,0);
    }
    ++count;

  }//while

  closedir(dir);

  if(lflag == 0){
    printf("\n");
  }



}

void printFormatted(char * file, struct stat & fileInfo, int isFile){

  std::string rwx = get_rwx(fileInfo.st_mode);
  struct passwd * psw;
  struct group * grp;

  time_t mtime = fileInfo.st_mtime;

  struct tm * timeInfo = localtime(&mtime);

  char months[][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

  psw = getpwuid(fileInfo.st_uid);
  grp = getgrgid(fileInfo.st_gid);

  cout.setf(std::ios_base::unitbuf);
 
  if(totalPrinted == 0 && isFile == 0){
    cout << "total: " << std::dec << BLOCKS/2 << endl;
    ++totalPrinted;
  }
  

  cout << rwx <<  ". ";

  cout << fileInfo.st_nlink;

  cout << " " << psw->pw_name;

  cout << " " <<  grp->gr_name;
  
  cout.width(7);
  cout << std::right << fileInfo.st_size;

  cout << " " << months[timeInfo->tm_mon];
  
  cout.width(3);
  cout << std::right << timeInfo->tm_mday;

  cout.width(3);
  cout << timeInfo->tm_hour << ":" << timeInfo->tm_min;

  char prev = std::cout.fill('0');

  cout <<  " " << file << endl;

  std::cout.fill(prev);
  /* -l option prints 

     blocks taken up
     permissions 
     number of links 
     user 
     group
     size 
     month of last modification 
     day of last modification 
     time of last modification
     filename

  */
}

