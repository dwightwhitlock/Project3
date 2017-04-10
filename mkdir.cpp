#include <sys/stat.h>
#include <sys/types.h>
#include <cstring>
#include <string>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cerrno>
#include <algorithm>
#include <vector>


using std::cout;
using std::endl;
using std::string;
using std::vector;

bool pFlag;
int mode;
int makeDirectories(char * path, int modeD);


int main(int argc, char * argv[]){

  pFlag = false;
  mode = 0755;
  bool goodJob = false;

  for(int i = 1; i < argc; ++i){ // loop through args
    
    if((strcmp(argv[i],"-p")) == 0) //parent - recursive
      {
	pFlag = true;
      }
    else if ((strcmp(argv[i],"-m")) == 0) //specify mode flag
      {
	/* If there is no argument following -m, missing operand error  */
	if(argv[i+1] == nullptr)
	  {
	    cout << "mkdir: option requires an argument -- 'm'"<< endl;
	    exit(EXIT_FAILURE);
	  }
	/* The argument following -m should be the mode specified. */
	else
	  {
	    mode = atoi(argv[i+1]); //set mode equal to mode argument
	    ++i; //advance past mode argument
	  }
      }
    else
      {	
	makeDirectories(argv[i], mode);
	goodJob = true;
      }
	
  }//for

  if(!goodJob)
    {
      cout << "mkdir: missing operand" << endl;
    }

  return EXIT_SUCCESS;
}//main


/**
 * Create directories with the path given. Returns 0 if successful
 * and -1 if not
 **/
int makeDirectories(char * path, int modeD){
  if(pFlag)
    {
      /*
	 We want to call mkdir on all directories in the path specified.
	 The final directory should have mode modeD. Intermediate directories
	 should have 0755.We want to create all directories  in the given path.
	 Create substring of path up to first iteration of '/'. Call mkdir. Add 
	 to that substring the next name in path up to '/'. Continue until 
	 no iterations of '/' in path, and then call mkdir with modeD
      */
      
      int numDirs = 1;

      string strPath(path);
      numDirs += std::count(strPath.begin(),strPath.end(),'/');
      
      int * indexOfSlash = new int[numDirs-1];
      int pathLen = strlen(path);
      int x = 0;
      
      /*Set values in indexOfSlash to the index of '/' in path */
      for(int i = 0; i < pathLen; ++i)
	{
	  
	  if(path[i] == '/')
	    {
	      indexOfSlash[x] = i;
	      x += 1;
	    }
	}

      
      /*Now that we know indices of '/', use string::substr to create paths
       to call mkdir on*/
      char * parentPath;
      string strParentPath;

      for(int j = 0; j < numDirs-1; j++) //loop through dirs
	{
	   strParentPath = strPath.substr(0, indexOfSlash[j]);
	   parentPath = &strParentPath[0];
	   mkdir(parentPath, 0755);
	}
      mkdir(path, modeD);
      
      delete [] indexOfSlash;
    }

  else
    {
      if(mkdir(path,modeD) == -1)
	{
	  if(errno == EEXIST)
	    {
	      cout << "mkdir: cannot create directory '" << path
		   << ": File exists" << endl;
	    }
	  else
	    {
	      cout << "mkdir: cannot create directory '" << path
		   << ": No such file or directory" << endl;
	    }

	  return -1;	  
	}
    }
  
  return 0;
}


