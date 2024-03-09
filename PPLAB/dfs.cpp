#include <iostream>
#include <vector>
#include <map>
#include <omp.h>
#include <list>
using namespace std;

// Graph class represents a complete graph
class Graph {
public:
    map<int, bool> visited;
    map<int, list<int>> adj;

    // Function to add edges for a complete graph
    void addEdges(int vertices);

    // DFS traversal of the vertices reachable from v
    void DFS(int v);
    void P_DFS(int v);
};

void Graph::addEdges(int vertices) {
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            if (i != j) {
                adj[i].push_back(j);
            }
        }
    }
}

void Graph::DFS(int v) {
    // Mark the current node as visited and print it
    visited[v] = true;
    //cout << v << " ";

    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFS(*i);
}

void Graph::P_DFS(int v) {
    // Mark the current node as visited and print it
    #pragma omp critical
    visited[v] = true;
    //cout << v << " ";

    for (auto u_it = adj[v].begin(); u_it != adj[v].end(); ++u_it) {
        int u = *u_it;
        if (!visited[u]) {
            #pragma omp task
            P_DFS(u);
        }
    }
}



// Driver code
int main() {
    int vertices;
    cout << "Enter the number of vertices: ";
    cin >> vertices;

    Graph g;
    g.addEdges(vertices);

    cout << "Following is Depth First Traversal\n";

    // Starting DFS from vertex 0
    double start_time = omp_get_wtime();
    g.DFS(0);
    double end_time = omp_get_wtime();
    
    cout << "\nThe time required for serial DFS to execute is: " << end_time - start_time << " seconds\n";
    
    start_time = omp_get_wtime();
    g.visited.clear(); // Reset visited map
    g.P_DFS(0);
    end_time = omp_get_wtime();
    
    cout << "\nThe time required for parallel DFS to execute is: " << end_time - start_time << " seconds\n";
    
    return 0;
}
