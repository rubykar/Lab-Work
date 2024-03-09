#include<stdio.h>
#include<stdlib.h>

int factorial(int n){
	if(n == 0 || n == 1 ){
			return 1;
	}
	
	else
		return n*factorial(n-1);

}

int main(int argc,char *argv[]){

	int result = factorial(atoi(argv[1]));
	printf("Factorial of the number is %d",result);
	return 0;
}
