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
////////////////////////////////////////////////////////////////////////////////////////
int mygrep(char* sourcefile, char* destinationfile,char *flag) {
    char line[1000];
    FILE *file;
    int line_number = 0;
    
    
    
    
    file = fopen(sourcefile, "r");  
    if (file == NULL) {
        printf("Error: could not open file %s\n", sourcefile);
        return 1;
    }
    
    while (fgets(line, 1000, file) != NULL) {
        line_number++;
        if (strstr(line, flag) != NULL) {
            printf("%s:%d:%s", sourcefile, line_number, line);
        }
    }
    
    fclose(file);
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////
int mygrep_c(char* sourcefile,char* destinationfile,char* flag) {
    char line[1000];
    FILE *file;
    int line_number = 0;
    int count = 0;
    
    file = fopen(sourcefile, "r");
    if (file == NULL) {
        printf("Error: could not open file %s\n", sourcefile);
        return 1;
    }
    
    while (fgets(line, 1000, file) != NULL) {
        line_number++;
        if (strstr(line, flag) != NULL) {
            count++;
        }
    }
    
    fclose(file);
    printf("%d\n", count);
    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
int mygrep_n(char* sourcefile,char* destinationfile,char* flag) 
	{
    char line[1000];
    FILE *file;
    int line_number = 0;
    
    
    
    file = fopen(sourcefile, "r");
    if (file == NULL) {
        printf("Error: could not open file %s\n", sourcefile);
        return 1;
    }
    
    while (fgets(line, 1000, file) != NULL) {
        line_number++;
        if (strstr(line, flag) != NULL) {
            printf("%s:%d:%s", sourcefile, line_number, line);
        }
    }
    
    fclose(file);
    return 0;
}
/////////////////////////////////////////////////////////////////////////////
int mygrep_v(char* sourcefile,char* destinationfile,char* flag) {
    char line[1000];
    FILE *file;
   
    file = fopen(sourcefile, "r");
    if (file == NULL) {
        printf("Error: could not open file %s\n", sourcefile);
        return 1;
    }
    
    while (fgets(line, 1000, file) != NULL) {
        if (strstr(line, flag) == NULL) {
            printf("%s", line);
        }
    }
    
    fclose(file);
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////
int mygrep_l(char* sourcefile,char* destinationfile,char* flag) {
    char line[1000];
    FILE *file;
    int found = 0;
   
    
    file = fopen(sourcefile, "r");
    if (file == NULL) {
        printf("Error: could not open file %s\n", sourcefile);
        return 1;
    }
    
    while (fgets(line, 1000, file) != NULL) {
        if (strstr(line, flag) != NULL) {
            found = 1;
            break;
        }
    }
    
    if (found) {
        printf("%s\n", sourcefile);
    }
    
    fclose(file);
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////
