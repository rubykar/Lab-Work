#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX_VERTICES 500

// Structure to represent a queue node
struct QueueNode {
    int data;
    struct QueueNode* next;
};

// Structure to represent a queue
struct Queue {
    struct QueueNode *front, *rear;
};

// Function to create a new queue node
struct QueueNode* newQueueNode(int data) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a new queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to check if the queue is empty
int isEmpty(struct Queue* queue) {
    return queue->front == NULL;
}

// Function to add an element to the queue
void enqueue(struct Queue* queue, int data) {
    struct QueueNode* newNode = newQueueNode(data);
    if (isEmpty(queue)) {
        queue->front = queue->rear = newNode;
        return;
    }
    queue->rear->next = newNode;
    queue->rear = newNode;
}

// Function to remove an element from the queue
int dequeue(struct Queue* queue) {
    if (isEmpty(queue))
        return -1;
    int data = queue->front->data;
    struct QueueNode* temp = queue->front;
    queue->front = queue->front->next;
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

// Function to perform Breadth-First Search traversal sequentially
void sequentialBFS(int** graph, int startVertex, int vertices) {
    struct Queue* queue = createQueue();
    int visited[MAX_VERTICES] = {0};

    visited[startVertex] = 1;
    enqueue(queue, startVertex);

    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);

        for (int i = 0; i < vertices; ++i) {
            if (graph[currentVertex][i] && !visited[i]) {
                visited[i] = 1;
                enqueue(queue, i);
            }
        }
    }
}

// Function to perform Breadth-First Search traversal in parallel
void parallelBFS(int** graph, int startVertex, int vertices) {
    struct Queue* queue = createQueue();
    int visited[MAX_VERTICES] = {0};

    visited[startVertex] = 1;
    enqueue(queue, startVertex);

    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);

        #pragma omp parallel for
        for (int i = 0; i < vertices; ++i) {
            if (graph[currentVertex][i] && !visited[i]) {
                visited[i] = 1;
                enqueue(queue, i);
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

    printf("Sequential BFS Traversal: ");
    double start_time_seq = omp_get_wtime();
    sequentialBFS(graph, 0, MAX_VERTICES);
    double end_time_seq = omp_get_wtime();
    printf("\nSequential BFS Execution Time: %f seconds\n", end_time_seq - start_time_seq);

    printf("\nParallel BFS Traversal: ");
    double start_time_par = omp_get_wtime();
    parallelBFS(graph, 0, MAX_VERTICES);
    double end_time_par = omp_get_wtime();
    printf("\nParallel BFS Execution Time: %f seconds\n", end_time_par - start_time_par);

    // Free dynamically allocated memory for the graph
    freeGraph(graph, MAX_VERTICES);

    return 0;
}
