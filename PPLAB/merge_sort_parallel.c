#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

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

    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {

                mergeSort(arr, l, m);
            }

            #pragma omp section
            {

                mergeSort(arr, m + 1, r);
            }
        }

        merge(arr, l, m, r);
    }
}

void mergeSortSeq(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSortSeq(arr, l, m);
           

        mergeSortSeq(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int main() {
    const int size = 10000000; 
    int* arr = (int*)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        arr[i] = rand();
    }

    double start_seq = omp_get_wtime();
    mergeSortSeq(arr, 0, size - 1);
    double end_seq = omp_get_wtime();
    printf("Sequential merge sort took %.6f seconds\n", end_seq - start_seq);


    for (int i = 0; i < size; i++) {
        arr[i] = rand();
    }


    double start_par = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        {
            mergeSort(arr, 0, size - 1);
        }
    }
    double end_par = omp_get_wtime();
    printf("Parallel merge sort took %.6f seconds\n", end_par - start_par);

    free(arr);
    return 0;
}
