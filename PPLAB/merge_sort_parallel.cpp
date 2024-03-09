#include <stdio.h>
#include <omp.h>

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0;
    int j = 0;
    int k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                // Sort the first half
                mergeSort(arr, l, m);
            }

            #pragma omp section
            {
                // Sort the second half
                mergeSort(arr, m + 1, r);
            }
        }

        // Merge the sorted halves
        merge(arr, l, m, r);
    }
}

int main() {
    const int size = 8;
    int arr[size] = {12, 11, 13, 5, 6, 7, 1, 10};

    printf("Original array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    
    double start,end;
    start = omp_get_wtime();

    // Perform parallelized merge sort
    #pragma omp parallel
    {
        #pragma omp single
        {
            mergeSort(arr, 0, size - 1);
        }
    }
    
    end = omp_get_wtime();

    printf("Sorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

		printf("Time : %f ",end-start);
    return 0;
}
