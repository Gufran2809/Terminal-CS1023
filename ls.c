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
int  myls() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') {
            continue;
        }
        printf("%s\t", entry->d_name);
    }
    printf("\n");

    closedir(dir);
}

int  myls_a(){

  DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
       
        printf("%s\t", entry->d_name);
    }
    printf("\n");

    closedir(dir);

}

int myls_o()
{
    DIR *currentstring;
    struct dirent *current;
    char *path ="./";
    struct stat s;
    currentstring=opendir(path);

    if (currentstring == NULL) 
    {
        perror("opendir");
        return 1;
    }

    while ((current = readdir(currentstring)) != NULL)
    {
	    
	    if(stat(current->d_name,&s)==-1)
	    {
		    perror("stat");
		    exit(EXIT_FAILURE);
	    }
             printf((S_ISDIR(s.st_mode)) ? "d" : "-");
    	     printf((s.st_mode & S_IRUSR) ? "r" : "-");
             printf((s.st_mode & S_IWUSR) ? "w" : "-");
             printf((s.st_mode & S_IXUSR) ? "x" : "-");
             printf((s.st_mode & S_IRGRP) ? "r" : "-");
             printf((s.st_mode & S_IWGRP) ? "w" : "-");
             printf((s.st_mode & S_IXGRP) ? "x" : "-");
             printf((s.st_mode & S_IROTH) ? "r" : "-");
             printf((s.st_mode & S_IWOTH) ? "w" : "-");
             printf((s.st_mode & S_IXOTH) ? "x" : "-");

    printf(" %2ld", s.st_nlink);

    printf(" %s", getpwuid(s.st_uid)->pw_name);

    printf(" %8ld", s.st_size);
    char time[80];
    strftime(time, 80, "%b %d %H:%M", localtime(&s.st_mtime));
    printf(" %s", time);
    printf(" %s\n", current->d_name);

    }
    closedir(currentstring);
}
 int myls_l()
{
    DIR *currentstring;
    struct dirent *current;
    char *path ="./";
    struct stat s;
    currentstring=opendir(path);

    if (currentstring == NULL) 
    {
        perror("opendir");
        return 1;
    }

    while ((current = readdir(currentstring)) != NULL)
    {
	    
	    if(stat(current->d_name,&s)==-1)
	    {
		    perror("stat");
		    exit(EXIT_FAILURE);
	    }
             printf((S_ISDIR(s.st_mode)) ? "d" : "-");
    	     printf((s.st_mode & S_IRUSR) ? "r" : "-");
             printf((s.st_mode & S_IWUSR) ? "w" : "-");
             printf((s.st_mode & S_IXUSR) ? "x" : "-");
             printf((s.st_mode & S_IRGRP) ? "r" : "-");
             printf((s.st_mode & S_IWGRP) ? "w" : "-");
             printf((s.st_mode & S_IXGRP) ? "x" : "-");
             printf((s.st_mode & S_IROTH) ? "r" : "-");
             printf((s.st_mode & S_IWOTH) ? "w" : "-");
             printf((s.st_mode & S_IXOTH) ? "x" : "-");

    printf(" %2ld", s.st_nlink);

    printf(" %s", getpwuid(s.st_uid)->pw_name);

    printf(" %s",getgrgid(s.st_gid)->gr_name);

    printf(" %8ld", s.st_size);
    char time[80];
    strftime(time, 80, "%b %d %H:%M", localtime(&s.st_mtime));
    printf(" %s", time);
    printf(" %s\n", current->d_name);

    }
    closedir(currentstring);
}
int myls_g()
{
    DIR *currentstring;
    struct dirent *current;
    char *path ="./";
    struct stat s;
    currentstring=opendir(path);

    if (currentstring == NULL) 
    {
        perror("opendir");
        return 1;
    }

    while ((current = readdir(currentstring)) != NULL)
    {
	    
	    if(stat(current->d_name,&s)==-1)
	    {
		    perror("stat");
		    exit(EXIT_FAILURE);
	    }
             printf((S_ISDIR(s.st_mode)) ? "d" : "-");
    	     printf((s.st_mode & S_IRUSR) ? "r" : "-");
             printf((s.st_mode & S_IWUSR) ? "w" : "-");
             printf((s.st_mode & S_IXUSR) ? "x" : "-");
             printf((s.st_mode & S_IRGRP) ? "r" : "-");
             printf((s.st_mode & S_IWGRP) ? "w" : "-");
             printf((s.st_mode & S_IXGRP) ? "x" : "-");
             printf((s.st_mode & S_IROTH) ? "r" : "-");
             printf((s.st_mode & S_IWOTH) ? "w" : "-");
             printf((s.st_mode & S_IXOTH) ? "x" : "-");

    printf(" %2ld", s.st_nlink);

    printf(" %s", getpwuid(s.st_uid)->pw_name);

    printf(" %8ld", s.st_size);
    char time[80];
    strftime(time, 80, "%b %d %H:%M", localtime(&s.st_mtime));
    printf(" %s", time);
    printf(" %s\n", current->d_name);

    }
    closedir(currentstring);
}

