#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>


int Isprime(int n){
 if(n<=1){
  return -1;
 }
 int i;
 for(i = 2;i * i <= n;i++){
	if(n%i == 0){
	 return -1;
	}
  }
  return n;
}




int main(int argc, char *argv[]){
	if (argc != 2){
		fprintf(stderr,"Parameter is not provided\n");
		exit(EXIT_FAILURE);
	}

	int n = atoi(argv[1]);

	if(n < 0 ){
		fprintf(stderr, "Please provide a non negative number\n");
		exit(EXIT_FAILURE);
	}

	pid_t pid = fork();

	if(pid < 0){
		fprintf(stderr,"The child process is not created\n");
		exit(EXIT_FAILURE);
	}

	if(pid == 0){
		printf("Child Process %ld : Prime Series - ",(long)getpid());
		for(int i = 0 ; i <= n;i++){
			if(Isprime(i) != -1){
			printf("%d",Isprime(i));
			}
			if(i < n) { 
        	                printf(",");
	                }

		}

		printf("\n");
	}

	else{
		wait(NULL);
		printf("parent Process %ld : Child process completed\n", (long)getpid());
	}
	return 0;
}




