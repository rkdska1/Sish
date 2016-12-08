#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <errno.h>  
#include <sys/types.h>  
#include <sys/wait.h>  
#include <signal.h>  
#include <string.h>  
#define DELIM ":"  
   
extern char **environ;	//FOr env command  
  
int main(int argc, char **argv){  
	pid_t pid;  
	char *str_path[1000]={NULL};  
	char test_str[1000];  
	char buffer[1000]=" ";  
	char *command[]={NULL};  
	char *user=NULL;  
	char *pwd; 	  
	char *newpwd=NULL;  
	char *pwdptr=NULL;  
	char *pwdtemp=NULL;  
	char *path=NULL;  
	char *mypath;  
	char *path_ptr;  
	char *path_comm[1000]={NULL};  
	char *path_tmp=NULL;  
	char *ptr=NULL;  
	char *temp=NULL;  
	char *user_id;  
	char *user_pwd;  
	char **env_var1;  
	int i=0; int j=0; int spc_com;   
	int number=0; int check_number=0; int error_msg=0;int safe_mode=0;int permission=0;//0 = no permission, 1= normal, 2= super,.. save this for later  
	user = getenv("USER");  
	mypath = getenv("PATH");  
	pwd = getenv("PWD");  
	spc_com=1;  
/*		  
	printf("GOOD SO FAR 1111");	  
	pwdtemp= (char *)malloc(strlen(pwd)+1);  
	printf("GOOD SO FAR 2222");  
	strcpy(pwdtemp, pwd);  
	printf("GOOD SO FQAR 3333");  
	newpwd= strtok_r(pwdtemp, "/", &pwdptr);  
	printf("EEEOEOENEONEONEOENEONE");  
	while(!(temp3=strtok_r(NULL, "/", &pwdptr))){  
		temp2 = temp3;  
	}  
	printf("%s", temp2);  
*/  
//	memset(path_comm, 0, size);  
	  
  
	while(1){  
		spc_com=1;  
		if(error_msg ==1){			//in case the command is not right  
		if(!strlen(command[0]))  
				break;;  
			printf("%s: command not found\n", command[0]);  
			error_msg=0;  
		}  
		for(i=0;command[i];i++)  
			command[i]=NULL;		//clear the command string  
		printf("%sassam:~%s$ ", user, pwd);  
		fgets(buffer, 256, stdin);  
//		while(buffer.IsEmpty()){  
//			printf("%s@assam:~%s$", user, pwd);  
//			fgets(buffer, 256, stdin);	  
//		}  
  
		  
		buffer[strlen(buffer)-1]='\0';	  
		if(!strcmp(buffer, "quit") || (!strcmp(buffer, "QUIT")))  
			exit(0);  
		if(!strcmp(buffer, "showpath")){  
			printf("%s\n", mypath);  
			spc_com=0;  
		}  
		if(!strcmp(buffer, "env") || !strcmp(buffer, "ENV")){  
			for(env_var1=environ; *env_var1!=NULL; ++env_var1)  
				printf("%s\n", *env_var1);  
			spc_com=0;  
		}				//additional commands added  
		  
		if(spc_com){  
		pid=fork();  
	//	printf("FIRST\n");	  
//		memset(command, 0, size);  
	//	printf("SECOND\n");  
		  
		temp = strtok(buffer, " ");   // needs to be modified  
	//	printf("THIRD\n");  
		i=0;  
		while(temp){  
			command[i]= temp;  
			temp = strtok(NULL, " ");  
			i++;  
		}  
	//	printf("moving buffer is error");  
		//printf("BEFORE ERROR!!!\n");	  
		if(pid < 0){	//If the fork is not operated right  
			perror("fork failed: process id : %d\n");  
			exit(1);   //127 or 126 seems right?  
		}	  
		else if(pid==0){	//child process  
			path = getenv("PATH");  
			path_tmp = strtok(path, ":");  
			j=0;  
			while(path_tmp){  
				path_comm[j]=path_tmp;  
				path_tmp = strtok(NULL, ":");  
				j++;  
			}  
  
  
			for(i=0;path_comm[i]!=NULL;i++){  
				check_number = snprintf(test_str,256,  "%s/%s", path_comm[i], command[0]);  
			  
			  
				if(!check_number){		//Error check  
					printf("Error has occured!! ABORTING");  
					exit(0);  
				}  
				number = execve(test_str, command, NULL);      
				if(number== -1){	//if execve is not done right  
					error_msg = 1;  
				}  
			}		  
		}  
		else{ 	//parent process  
			wait(0);  
		}   
	}}  
	return 0;	  
  
}  

