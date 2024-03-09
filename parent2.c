#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>


int main(int argc,char *argv[]){
	if(argc != 2){
		fprintf(stderr,"Too few arguments\n");
		exit(EXIT_FAILURE);
	}
	
	int n = atoi(argv[1]);
	
	if(n < 0){
		fprintf(stderr,"Please enter non-negative number\n");
		exit(EXIT_FAILURE);
	}
	
	pid_t pid = fork();
	
	
	
	if(pid < 0){
		fprintf(stderr,"Child process is not created\n");
		exit(EXIT_FAILURE);
	}
	
	if(pid == 0){
	
		char *args[] = {"./child", argv[1], NULL};
		execvp(args[0], args);
		
		
		perror("execvp");
		exit(EXIT_FAILURE);
	}
	
	else{
		wait(NULL);
		printf("Parent Process : Child Process Completed\n");
	}
	
	return 0;
	
}
