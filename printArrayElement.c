#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>


void printArrayElement(int n,char *arg[]){
	for(int i = 1;i <= n ; i++){
		int m = atoi(arg[i]);
		printf("%d\t",m);
	}
	printf("\n");

}


int main(int argc , char *argv[]){
	if (argc < 2){
		fprintf(stderr,"Expected more agruments , got very few\n");
		exit(EXIT_FAILURE);
	}
	
	pid_t pid = fork();
	
	if(pid < 0){
		fprintf(stderr,"The child process is not created\n");
		exit(EXIT_FAILURE);
	}
	
	if(pid == 0){
		printArrayElement(argc - 1,argv);
	}
	
	else{
		wait(NULL);
		
		printf("Parent Process : Child process Completed\n");
	}
	
	return 0;

}
