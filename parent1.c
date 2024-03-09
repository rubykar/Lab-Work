#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Few arguments provided\n");
        exit(EXIT_FAILURE);
    }

    int n = argc - 1;

    int *arr = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork Failed\n");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        bubbleSort(arr, n);
        char *arr_str[n + 1];
        for (int i = 0; i < n; i++) {
            char elem_str[10];
            snprintf(elem_str, sizeof(elem_str), "%d", arr[i]);
            arr_str[i] = strdup(elem_str);
        }

        arr_str[n] = NULL;

        execve("./child", arr_str, NULL);

        perror("execve");

        exit(EXIT_FAILURE);
    } else {
        wait(NULL);

        printf("Parent process: Child Process completed\n");
    }

    free(arr);
    return 0;
}
