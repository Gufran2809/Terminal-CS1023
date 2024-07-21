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

//ls commands
int myls();
int myls_a();
int myls_l();
int myls_o();
int myls_g();

//ps commands
int myps();
int myps_A();
int myps_af();
int myps_p();
int myps_f();
//cp functions

int cpfile(char*,char*);
int rep(char*,char*);
int mycp_u(char*,char*);
int con(char*,char*);

//mv functions;
int mvfile(char*,char*);
int conMv(char*,char*);
int repMv(char*,char*);
int mymv_u(char*,char*);

//grep functions
int mygrep(char*,char*,char*);
int mygrep_n(char*,char*,char*);
int mygrep_v(char*,char*,char*);
int mygrep_c(char*,char*,char*);
int mygrep_l(char*,char*,char*);

int main()
{
		char hostname[500];
    		char username[500];
    		char current[500];
    		char prompt[500];
    		gethostname(hostname, sizeof(hostname));
    		getlogin_r(username, sizeof(username));
    while (1)
    {
        getcwd(current, sizeof(current));
        snprintf(prompt,500, "%s@%s:%s $ ", username, hostname, current);
	char* input = readline(prompt);

	if(strlen(input)!=0)
        add_history(input);

	char *token[6];
	token[0]=strtok(input," ");token[1]=strtok(NULL," ");
	token[2]=strtok(NULL," ");token[3]=strtok(NULL," ");
	token[4]=strtok(NULL," ");

	if(strcmp(token[0],"man")==0)	
	{
		if(strcmp(token[1],"ls")==0)
			{
				char store[1000];
				FILE *show;
				show=fopen("ls_man.txt","r");
				while(fgets(store,1000,show)!=NULL)
					printf("%s",store);
				fclose(show);
				printf("\n");

			}

		else if(strcmp(token[1],"ps")==0)
			{
				char store[1000];
                                FILE *show;
                                show=fopen("ps_man.txt","r");
                                while(fgets(store,1000,show)!=NULL)
                                        printf("%s",store);
                                fclose(show);
                                printf("\n");

			}

		 else if(strcmp(token[1],"cp")==0)
                        {
                                char store[1000];
                                FILE *show;
                                show=fopen("cp_man.txt","r");
                                while(fgets(store,1000,show)!=NULL)
                                        printf("%s",store);
                                fclose(show);
                                printf("\n");

                        }

		 else if(strcmp(token[1],"mv")==0)
                        {
                                char store[1000];
                                FILE *show;
                                show=fopen("mv_man.txt","r");
                                while(fgets(store,1000,show)!=NULL)
                                        printf("%s",store);
                                fclose(show);
                                printf("\n");

                        }

		  else if(strcmp(token[1],"grep")==0)
                        {
                                char store[1000];
                                FILE *show;
                                show=fopen("grep_man.txt","r");
                                while(fgets(store,1000,show)!=NULL)
                                        printf("%s",store);
                                fclose(show);
                                printf("\n");

                        }

	}//man command end
	 
	 
	 //calling ls commands
	if(strcmp(token[0],"ls")==0 && token[1]==NULL)
	{
		myls();
		continue;
	}
	if(strcmp(token[0],"ls")==0 && strcmp(token[1],"-a")==0)
	{	myls_a();}
	if(strcmp(token[0],"ls")==0 && strcmp(token[1],"-l")==0)
	{ 	myls_l();}
	if(strcmp(token[0],"ls")==0 && strcmp(token[1],"-o")==0)
	{	myls_o();}
	if(strcmp(token[0],"ls")==0 && strcmp(token[1],"-g")==0)
	{	myls_g();}

	//calling ps commands
	int show_all = 0;
    
    
	  if(strcmp(token[0],"ps")==0 && token[1]==NULL)
	  {  
		  show_all=1;
		  myps();
		  continue;
	  }
        if(strcmp(token[0],"ps")==0 && strcmp(token[1],"-A")==0)
	{
		myps_A();
		continue;
	}
	
        if(strcmp(token[0],"ps")==0 && strcmp(token[1],"-af")==0)
	{
		myps_af();
		continue;
	}
	
        if(strcmp(token[0],"ps")==0 && strcmp(token[1],"-f")==0)
	{
	       	myps_f();
		continue;
	}
	
        if(strcmp(token[0],"ps")==0 && strcmp(token[1],"-p")==0)
	{        myps_p();
		continue;	
	}
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int change=0;
            
     if(strcmp(token[0],"cp")==0 && token[3]==NULL)
    {
	    char *sourcefile=token[1];
	    char *destinationfile=token[2];
	    cpfile(sourcefile,destinationfile);
    }
    
    if(strcmp(token[0],"cp")==0 && strcmp(token[1],"-n")==0)
    {
	    char *sourcefile=token[2];
	    char *destinationfile=token[3];
	    rep(sourcefile,destinationfile);
    }

   if(strcmp(token[0],"cp")==0 && strcmp(token[1],"-u")==0)
    {
	    char *sourcefile=token[2];
	    char *destinationfile=token[3];
	    mycp_u(sourcefile,destinationfile);
    }

   if(strcmp(token[0],"cp")==0 && strcmp(token[1],"-v")==0)
    {
	    char *sourcefile=token[2];
	    char *destinationfile=token[3];
	    cpfile(sourcefile,destinationfile);
	    printf("%s -> %s",sourcefile,destinationfile);
    }
   if(strcmp(token[0],"cp")==0 && strcmp(token[1],"-l")==0)
    {
	    char *sourcefile=token[2];
	    char *destinationfile=token[3];
	    con(sourcefile,destinationfile);
    }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  int changeMv=0;
    if(strcmp(token[0],"mv")==0 && token[3]==NULL)
    {
	    char *sourcefile=token[1];
	    char *destinationfile=token[2];
	    mvfile(sourcefile,destinationfile);
    }
    
    if(strcmp(token[0],"mv")==0 && strcmp(token[1],"-n")==0)
    {
	    char *sourcefile=token[2];
	    char *destinationfile=token[3];
	    repMv(sourcefile,destinationfile);
    }

   if(strcmp(token[0],"mv")==0 && strcmp(token[1],"-u")==0)
    {
	    char *sourcefile=token[2];
	    char *destinationfile=token[3];
	    mymv_u(sourcefile,destinationfile);
    }

   if(strcmp(token[0],"mv")==0 && strcmp(token[1],"-v")==0)
    {
	    char *sourcefile=token[2];
	    char *destinationfile=token[3];
	    mvfile(sourcefile,destinationfile);
	    printf("\n%s -> %s\n",sourcefile,destinationfile);
    }

   if(strcmp(token[0],"mv")==0 && strcmp(token[1],"-l")==0)
    {
	    char *sourcefile=token[2];
	    char *destinationfile=token[3];
	    conMv(sourcefile,destinationfile);
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(strcmp(token[0],"grep")==0 && token[3]==NULL)
    {
	char *flag=token[1];
    	char *sourcefile=token[2];
	char *destinationfile=token[3];
	mygrep(sourcefile,destinationfile,flag);
    }


    if(strcmp(token[0],"grep")==0 && strcmp(token[1],"-c")==0)
    {	
	char *flag=token[1];
        char *sourcefile=token[2];
        char *destinationfile=token[3];
        mygrep_c(sourcefile,destinationfile,flag);
    }
	
    
    if(strcmp(token[0],"grep")==0 && strcmp(token[1],"-n")==0)
    {
        char *flag=token[1];
        char *sourcefile=token[2];
        char *destinationfile=token[3];
        mygrep_n(sourcefile,destinationfile,flag);
    }
     if(strcmp(token[0],"grep")==0 && strcmp(token[1],"-v")==0)
    {
        char *flag=token[1];
        char *sourcefile=token[2];
        char *destinationfile=token[3];
        mygrep_v(sourcefile,destinationfile,flag);
    }

      if(strcmp(token[0],"grep")==0 && strcmp(token[1],"-l")==0)
    {
        char *flag=token[1];
        char *sourcefile=token[2];
        char *destinationfile=token[3];
        mygrep_l(sourcefile,destinationfile,flag);
    }


    
    
    }

    }























