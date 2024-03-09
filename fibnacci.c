#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Function to calculate factorial
long long factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int main(int argc, char *argv[]) {
    	// Check if the number of command-line arguments is correct
    	if (argc != 2) {
        	fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        	exit(EXIT_FAILURE);
    	}

   	int n = atoi(argv[1]) ;

	if ( n < 0){
		fprintf(stderr,"Error : Please provide a non-negative integer.\n");
		exit(EXIT_FAILURE);
	}

	pid_t pid = fork();

	if(pid < 0){
		fprintf(stderr,"Fork failed");
		exit(EXIT_FAILURE);
	}
	

	if(pid == 0){
		printf("Child Process : Factorial Sequenec - ");


		for(int i = 0;i <= n; i++){
			printf("%lld",factorial(i));
			if(i<n){
				printf(", ");
			}
		}
		printf("\n");
	}
	else{
		wait(NULL);

		printf("Parent Process: Child completed");
	}
	return 0; 
}
