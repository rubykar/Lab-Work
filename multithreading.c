#include<stdio.h>
#include<pthread.h>


void* printEven(void *arg){
	int n = *((int *)arg);
	for(int i = 2;i <=n ;i +=2){
		printf("Even Thread : %d\n",i);
	}
	pthread_exit(NULL);
}


void* printOdd(void *arg){
	int n = *((int*)arg);
	for(int i = 1;i<=n;i+=2){
		printf("Odd Thread : %d\n",i);
	}
	pthread_exit(NULL);
}


int main(){
	int n;
	printf("Enter the range : ");
	scanf("%d",&n);

	pthread_t evenThread , oddThread;

	pthread_create(&evenThread,NULL,printEven,&n);
	pthread_create(&oddThread,NULL,printOdd,&n);

	pthread_join(evenThread,NULL);
	pthread_join(oddThread,NULL);


	return 0;

}
