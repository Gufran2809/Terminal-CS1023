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
#include <pwd.h>
#include <grp.h>
#include <errno.h>
#include <fcntl.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////
int cpfile(char *sourcefile,char *destinationfile)
	{
	FILE *source = fopen(sourcefile, "r");
    if (source == NULL) {
        printf("Error opening source file %s\n", sourcefile);
        return 1;
    }

    // open the destination file for writing
    FILE *destination = fopen(destinationfile, "w");
    if (destination == NULL) {
        printf("Error opening destination file %s\n", destinationfile);
        return 1;
    }

    // copy the contents of the source file to the destination file
    char buffer[4096];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytes_read, destination);
    }

    // close the files
    fclose(source);
    fclose(destination);

    printf("File copied successfully.\n");

    return 0;
	}
//////////////////////////////////////////////////////////////////////////////////////////

int rep(char *sourcefile, char *destinationfile) {
    int  no_overwrite = 1;


    // open the source file for reading
    FILE *source = fopen(no_overwrite ? sourcefile : "-n", "r");
    if (source == NULL) {
        printf("Error opening source file %s\n", no_overwrite ? sourcefile : "-n");
        return 1;
    }

    // open the destination file for writing
    FILE *destination = fopen(no_overwrite ? destinationfile : sourcefile, no_overwrite ? "wx" : "w");
    if (destination == NULL) {
        printf("Error opening destination file %s\n", no_overwrite ? destinationfile : sourcefile);
        return 1;
    }

    // copy the contents of the source file to the destination file
    char buffer[4096];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), source)) > 0) {
        fwrite(buffer, 1, bytes_read, destination);
    }

    // close the files
    fclose(source);
    fclose(destination);

    printf("File copied successfully.\n");

    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////

int con( char *sourcefile,  char *destinationfile) {
    if (link(sourcefile, destinationfile) != 0) {
        perror("Error creating hard link");
        exit(errno);
    }
    printf("Linked %s to %s\n", sourcefile, destinationfile);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int mycp_u(char *sourcefile, char *destinationfile) {
  int src_fd, dest_fd;
  ssize_t n;
  char buf[BUFSIZ];
  struct stat src_stat, dest_stat;

  if (stat(sourcefile, &src_stat) == -1) {
    perror("cpu: stat source file");
   
  }

  if (stat(destinationfile, &dest_stat) != -1) {
    // Destination file exists, check modification times
    if (src_stat.st_mtime <= dest_stat.st_mtime) {
      // Source file is not newer, do not copy
      printf("cpu: '%s' not copied: destination file is newer or equal\n", sourcefile);
      return 1;
    }
  }

  // Source file is newer, or destination file does not exist
  if ((src_fd = open(sourcefile, O_RDONLY)) == -1) {
    perror("cpu: open source file");
  }

  if ((dest_fd = open(destinationfile, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
    perror("cpu: open destination file");
  }

  while ((n = read(src_fd, buf, BUFSIZ)) > 0) {
    if (write(dest_fd, buf, n) != n) {
      perror("cpu: write destination file");
    }
  }

  if (n == -1) {
    perror("cpu: read source file");
   
  }

  if (close(src_fd) == -1) {
    perror("cpu: close source file");
   
  }

  if (close(dest_fd) == -1) {
    perror("cpu: close destination file");
    
  }
  
}

