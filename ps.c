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



int myps() {
    DIR *dir;
    struct dirent *dir_entry;
    FILE *fp;
    char path[100], buffer[1024];
    
    dir = opendir("/proc/");
    
    if (dir == NULL) {
        printf("Error: Could not open /proc directory\n");
        return 1;
    }
    
    printf("PID\t\tTTY\t\tSTAT\t\tCOMMAND\n");
    
    while ((dir_entry = readdir(dir)) != NULL) {
        if (dir_entry->d_type == DT_DIR && isdigit(*dir_entry->d_name)) {
            sprintf(path, "/proc/%s/stat", dir_entry->d_name);
            fp = fopen(path, "r");
            
            if (fp == NULL) {
                printf("Error: Could not open file for process %s\n", dir_entry->d_name);
                continue;
            }
            
            fscanf(fp, "%*d %*s %s", buffer);
            
            fclose(fp);
            
            if (buffer[0] == 'R') {
                sprintf(path, "/proc/%s/cmdline", dir_entry->d_name);
                fp = fopen(path, "r");
                
                if (fp == NULL) {
                    printf("Error: Could not open file for process %s\n", dir_entry->d_name);
                    continue;
                }
                
                fscanf(fp, "%s", buffer);
                
                fclose(fp);
                
                printf("%s\t\t?\t\t%c\t\t%s\n", dir_entry->d_name, buffer[2], buffer);
            }
        }
    }
    
    closedir(dir);
}

               int myps_A(){
        DIR *currstr;
    struct dirent *current;
    if ((currstr = opendir("/proc")) == NULL) {
        perror("opendir");
    }
    printf("%-8s %-10s %-10s %-10s\n", "PID","TTY", "TIME", "CMD");
    while ((current = readdir(currstr)) != NULL) {
        if (current->d_type == DT_DIR) {
            char path[1000000];
            snprintf(path, sizeof(path), "/proc/%s/status", current->d_name);
            FILE *file;
            if ((file = fopen(path, "r")) != NULL) {
             char line[1000000];
                char name[1000];
		char name1[1000];
                char pwd[1000];
                char status1[1000];
		int status;
                int utime, stime;
		int uid;
		int core;
                int tty_nr;
                int tty_fd;
		 int processor;
		 struct user_info;
		 int  ppid;
		 int  pid;
if (tty_fd == -1) {
    perror("open");
}
char *tty_name = (tty_nr == 0) ? NULL: ttyname(tty_fd);;


                while (fgets(line, sizeof(line), file) != NULL) {
                    if (sscanf(line, "Name: %s", name) == 1) {
                        sscanf(current->d_name, "%d", &pid); }

                    if (sscanf(line, "State: %d", &status) == 1) {
                        break; }
                      sscanf(line, "%*d %*s %*c %d",&tty_nr);
                    if (sscanf(line, "utime: %d", &utime) == 1) {
                        utime /= sysconf(_SC_CLK_TCK); }
                    if (sscanf(line, "stime: %d", &stime) == 1) {
                        stime /= sysconf(_SC_CLK_TCK);  }
		
                if (status != -1) {
                    time_t now = time(NULL);
                    struct tm *timenow = localtime(&now);
                    char time[10];
                    strftime(time, sizeof(time), "%H:%M", timenow);
     printf("%-8d %c%-10s %2d:%-5ld -%-10s\n", pid,(tty_nr==0)?'?':' ',(tty_name == NULL) ? " ": tty_name , utime, now % 60, name );
		}fclose(file);}}}}}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int myps_af() {
    DIR *dir;
    struct dirent *ent;
    FILE *fp;
    char path[256];
    char line[256];
    int pid, ppid, uid, status;
    char user[32], comm[32], state[32], *tty;
    unsigned long utime, stime;

    printf("%-8s %-8s %-8s %-8s %-12s %-12s %-8s %s\n", "USER", "PID", "PPID", "STATUS", "START", "TIME", "TTY", "COMMAND");

    if ((dir = opendir("/proc")) == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    while ((ent = readdir(dir)) != NULL) {
        if (ent->d_type != DT_DIR) continue;
        if (sscanf(ent->d_name, "%d", &pid) != 1) continue;

        snprintf(path, sizeof(path), "/proc/%d/status", pid);

        if ((fp = fopen(path, "r")) == NULL) {
            continue;
        }

        uid = -1;
        status = -1;
        while (fgets(line, sizeof(line), fp)) {
            if (sscanf(line, "Uid: %d", &uid) == 1) {
                continue;
            }
            if (sscanf(line, "PPid: %d", &ppid) == 1) {
                continue;
            }
            if (sscanf(line, "State: %s", state) == 1) {
                status = state[0];
                continue;
            }
            if (sscanf(line, "Name: %s", comm) == 1) {
                continue;
            }
            if (sscanf(line, "Tgid: %d", &pid) == 1) {
                continue;
            }
        }
        fclose(fp);

        if (uid == -1) continue;

        struct passwd *pw = getpwuid(uid);
        if (pw == NULL) {
            fprintf(stderr, "Failed to get username for UID %d\n", uid);
            continue;
        }
        snprintf(user, sizeof(user), "%s", pw->pw_name);

        snprintf(path, sizeof(path), "/proc/%d/stat", pid);
        if ((fp = fopen(path, "r")) == NULL) {
            continue;
        }

        if (fgets(line, sizeof(line), fp) == NULL) {
            fclose(fp);
            continue;
        }
        fclose(fp);

        sscanf(line, "%*d %*s %s %*d %*d %*d %*d %*u %*u %*u %*u %*u %*u %lu %lu", state, &utime, &stime);

        time_t now = time(NULL);
        struct tm *tm_now = localtime(&now);
        char start_time[16];
        strftime(start_time, sizeof(start_time), "%b %d %H:%M", tm_now);

        printf("%-8s %-8d %-8d %-8c %-12s %02lu:%02lu %-8s %s\n", user, pid, ppid, status, start_time, utime/60, stime/60, "?", comm);
    }

    closedir(dir);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int myps_f() {
    FILE *fp;
    char pid_str[10];
    char cmd[100];
    char line[100];

    int pid = getpid(); // get the process ID of the current process
    sprintf(pid_str, "%d", pid); // convert the PID to a string

    // construct the ps command
    strcpy(cmd, "ps -f | grep ");
    strcat(cmd, pid_str);

    // execute the command and read its output
    fp = popen(cmd, "r");
    if (fp == NULL) {
        printf("Error executing command.\n");
        return 1;
    }
    printf("USER\tPID\tPPID\tC\tSTIME\tTTY\tTIME\tCMD\n");
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }
    pclose(fp);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int myps_p() {
    pid_t pid = getpid();
    FILE *fp;
    char cmd[100];
    char line[100];

    // construct the ps command
    sprintf(cmd, "ps -p %d", pid);

    // execute the command and read its output
    fp = popen(cmd, "r");
    if (fp == NULL) {
        printf("Error executing command.\n");
        return 1;
    }

    // print the output to the console
    printf("USER\tPID\tPPID\tC\tSTIME\tTTY\tTIME\tCMD\n");
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }
    pclose(fp);
}
/////////////////////////////////////////////////////////////////////////////////////////
