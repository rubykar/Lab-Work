#include<stdio.h>
#include<stdlib.h>


int binarySearch(int arr[],int low,int high, int key){
	while(low <= high){
		int mid = low + (high - low) / 2;
		if(arr[mid] == key)
			return mid;
			
		if(arr[mid] < key){
			low = mid + 1;
		}
		
		else
			high = mid - 1;
	
	}
	
	return -1;
}



int main(int argc, char *argv[]) {
    printf("Child Process : Sorted Array - ");

    for (int i = 0; argv[i] != NULL; i++) {
        printf("%d", atoi(argv[i]));
        if (argv[i + 1] != NULL) {
            printf(" ,");
        }
    }
    printf("\n");

    int n = argc;

    int *arr = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i]);
        printf("\n%d",arr[i]);
    }

    int key;

    printf("\nEnter the key you want to search for :");
    scanf("%d", &key);
    int result = binarySearch(arr, 0, n - 1, key);

    if (result != -1) {
        printf("Element %d found at index %d.\n", key, result);
    } else {
        printf("Element %d not found in the array\n", key);
    }

    free(arr);

    return 0;
}

