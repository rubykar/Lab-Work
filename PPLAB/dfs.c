#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX_VERTICES 5000

// Structure to represent a stack node
struct StackNode {
    int data;
    struct StackNode* next;
};

// Structure to represent a stack
struct Stack {
    struct StackNode *top;
};

// Function to create a new stack node
struct StackNode* newStackNode(int data) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a new stack
struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = NULL;
    return stack;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == NULL;
}

// Function to push an element onto the stack
void push(struct Stack* stack, int data) {
    struct StackNode* newNode = newStackNode(data);
    newNode->next = stack->top;
    stack->top = newNode;
}

// Function to pop an element from the stack
int pop(struct Stack* stack) {
    if (isEmpty(stack))
        return -1;
    int data = stack->top->data;
    struct StackNode* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    return data;
}

// Function to create a complete graph with n vertices
int** createGraph(int vertices) {
    int** graph = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; ++i)
        graph[i] = (int*)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            if (i == j)
                graph[i][j] = 0;
            else
                graph[i][j] = 1;
        }
    }
    return graph;
}

// Function to perform Depth-First Search traversal sequentially
void sequentialDFS(int** graph, int startVertex, int vertices) {
    struct Stack* stack = createStack();
    int visited[MAX_VERTICES] = {0};

    push(stack, startVertex);
    visited[startVertex] = 1;

    while (!isEmpty(stack)) {
        int currentVertex = pop(stack);
        //printf("%d ", currentVertex);

        for (int i = 0; i < vertices; ++i) {
            if (graph[currentVertex][i] && !visited[i]) {
                push(stack, i);
                visited[i] = 1;
            }
        }
    }
}

// Function to perform Depth-First Search traversal in parallel
void parallelDFS(int** graph, int startVertex, int vertices) {
		#pragma omp critical
    struct Stack* stack = createStack();
    int visited[MAX_VERTICES] = {0};

    push(stack, startVertex);
    visited[startVertex] = 1;

    while (!isEmpty(stack)) {
        int currentVertex = pop(stack);
        //printf("%d ", currentVertex);

        #pragma omp critical
        for (int i = 0; i < vertices; ++i) {
            if (graph[currentVertex][i] && !visited[i]) {
                push(stack, i);
                visited[i] = 1;
            }
        }
    }
}

// Function to free dynamically allocated memory for the graph
void freeGraph(int** graph, int vertices) {
    for (int i = 0; i < vertices; ++i)
        free(graph[i]);
    free(graph);
}

int main() {
    int** graph = createGraph(MAX_VERTICES);

    printf("Sequential DFS Traversal: ");
    double start_time_seq = omp_get_wtime();
    sequentialDFS(graph, 0, MAX_VERTICES);
    double end_time_seq = omp_get_wtime();
    printf("\nSequential DFS Execution Time: %f seconds\n", end_time_seq - start_time_seq);

    printf("\nParallel DFS Traversal: ");
    double start_time_par = omp_get_wtime();
    #pragma omp parallel
    parallelDFS(graph, 0, MAX_VERTICES);
    double end_time_par = omp_get_wtime();
    printf("\nParallel DFS Execution Time: %f seconds\n", end_time_par - start_time_par);

    // Free dynamically allocated memory for the graph
    freeGraph(graph, MAX_VERTICES);

    return 0;
}

