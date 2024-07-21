#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <dirent.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/stat.h>
#include <time.h>
#include <grp.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/sysinfo.h>
#include <ctype.h>
#include<sched.h>
#include<pwd.h>
#include <fcntl.h>
#include <errno.h>

int mvfile(char* sourcefile,char* destinationfile) {
    
    if (rename(sourcefile, destinationfile) != 0) {
        printf("Error: could not move file\n");
    }

    printf("File moved successfully\n");
    return 0;
}
///////////////////////////////////////////////////////////////////////////
int conMv(char* sourcefile,char* destinationfile)
  {
	    if (rename(sourcefile, destinationfile) != 0) {
        printf("Error: could not move file\n");
    }
	
    printf("File moved successfully\n");
    return 0;
  }
/////////////////////////////////////////////////////////////////////////////
int  repMv(char *sourcefile, char *destinationfile) {

    struct stat s;
    if (stat(sourcefile, &s) == -1) {
        printf("Error: Cannot stat file '%s' : No such file or directory", sourcefile);
 
    }

        if (access(destinationfile, F_OK) == 0) {
        printf("Destination file already exists, file not moved.\n");
        return 1;
    }

    if (rename(sourcefile, destinationfile) == -1) {
        printf("Error: Cannot move file '%s' to '%s'\n", sourcefile, destinationfile);
     
    }}
/////////////////////////////////////////////////////////////////////

int mymv_u(char *sourcefile,char *destinationfile) {
  struct stat src_stat, dest_stat;

  if (stat(sourcefile, &src_stat) == -1) {
    perror("mvu: stat source file");
  }

  if (stat(destinationfile, &dest_stat) != -1) {
    // Destination file exists, check modification times
    if (src_stat.st_mtime <= dest_stat.st_mtime) {
      // Source file is not newer, do not overwrite
      printf("mvu: '%s' not moved: destination file is newer or equal\n", sourcefile);
      return 1;
    }
  }

  // Source file is newer, or destination file does not exist
  if (rename(sourcefile, destinationfile) == -1) {
    perror("mvu: rename file");
  
  }
  
}

///////////////////////////////////////////////////////////////////////////
