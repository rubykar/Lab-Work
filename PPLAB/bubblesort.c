#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>

void bubblesort(int arr[],int n){
	for(int i = 0 ;i<n;i++){
		for(int j = i;j<n;j++){
			if(arr[i] < arr[j]){
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

int main(){
	int arr[10] = {0};
	int i = 0;
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	fp = fopen("numbers.txt","r");
	
	if(fp == NULL){
		printf("The file could not be read");
		exit(EXIT_FAILURE);
	}
	
	else{
		while((read = getline(&line,&len,fp) ) != -1){
			arr[i] = atoi(line);
			i++;
		}
		bubblesort(arr,10);
		
		for(int i = 0;i<10;i++){
			printf("%d\n",arr[i]);
		}
		fclose(fp);
	
	}

}
