#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <limits>

/**
 * DSA Tip #5: Graphs
 *
 * Key concepts:
 * - Graph representations (adjacency list, matrix)
 * - Graph traversal algorithms (BFS, DFS)
 * - Shortest path algorithms (Dijkstra, Bellman-Ford)
 * - Cycle detection
 * - Topological sorting
 * - Connected components
 *
 * Trick: Use adjacency list for sparse graphs (most real-world graphs)
 * and adjacency matrix for dense graphs or when you need O(1) edge checks.
 */

class Graph {
private:
    int vertices_;
    std::vector<std::vector<int>> adjList_; // Adjacency list
    bool directed_;

public:
    Graph(int vertices, bool directed = false)
        : vertices_(vertices), adjList_(vertices), directed_(directed) {}

    void addEdge(int u, int v) {
        adjList_[u].push_back(v);
        if (!directed_) {
            adjList_[v].push_back(u); // Undirected graph
        }
    }

    // Breadth-First Search
    void BFS(int start) const {
        std::vector<bool> visited(vertices_, false);
        std::queue<int> q;

        visited[start] = true;
        q.push(start);

        std::cout << "BFS traversal starting from " << start << ": ";

        while (!q.empty()) {
            int vertex = q.front();
            q.pop();
            std::cout << vertex << " ";

            for (int neighbor : adjList_[vertex]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        std::cout << "\n";
    }

    // Depth-First Search (recursive)
    void DFS(int start) const {
        std::vector<bool> visited(vertices_, false);
        std::cout << "DFS traversal starting from " << start << ": ";
        DFSUtil(start, visited);
        std::cout << "\n";
    }

private:
    void DFSUtil(int vertex, std::vector<bool>& visited) const {
        visited[vertex] = true;
        std::cout << vertex << " ";

        for (int neighbor : adjList_[vertex]) {
            if (!visited[neighbor]) {
                DFSUtil(neighbor, visited);
            }
        }
    }

public:
    // Iterative DFS
    void DFSIterative(int start) const {
        std::vector<bool> visited(vertices_, false);
        std::stack<int> s;

        s.push(start);
        std::cout << "Iterative DFS starting from " << start << ": ";

        while (!s.empty()) {
            int vertex = s.top();
            s.pop();

            if (!visited[vertex]) {
                visited[vertex] = true;
                std::cout << vertex << " ";

                // Push neighbors in reverse order to maintain DFS order
                for (auto it = adjList_[vertex].rbegin(); it != adjList_[vertex].rend(); ++it) {
                    if (!visited[*it]) {
                        s.push(*it);
                    }
                }
            }
        }
        std::cout << "\n";
    }

    // Cycle detection in undirected graph
    bool hasCycleUndirected() const {
        std::vector<bool> visited(vertices_, false);

        for (int i = 0; i < vertices_; ++i) {
            if (!visited[i]) {
                if (hasCycleUtil(i, visited, -1)) {
                    return true;
                }
            }
        }
        return false;
    }

private:
    bool hasCycleUtil(int vertex, std::vector<bool>& visited, int parent) const {
        visited[vertex] = true;

        for (int neighbor : adjList_[vertex]) {
            if (!visited[neighbor]) {
                if (hasCycleUtil(neighbor, visited, vertex)) {
                    return true;
                }
            } else if (neighbor != parent) {
                return true;
            }
        }
        return false;
    }

public:
    // Topological sort (for DAGs)
    std::vector<int> topologicalSort() const {
        std::vector<int> indegree(vertices_, 0);
        std::queue<int> q;
        std::vector<int> result;

        // Calculate indegrees
        for (int i = 0; i < vertices_; ++i) {
            for (int neighbor : adjList_[i]) {
                indegree[neighbor]++;
            }
        }

        // Enqueue vertices with indegree 0
        for (int i = 0; i < vertices_; ++i) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int vertex = q.front();
            q.pop();
            result.push_back(vertex);

            for (int neighbor : adjList_[vertex]) {
                if (--indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        return result;
    }

    // Print adjacency list
    void printGraph() const {
        std::cout << "Adjacency List:\n";
        for (int i = 0; i < vertices_; ++i) {
            std::cout << i << ": ";
            for (int neighbor : adjList_[i]) {
                std::cout << neighbor << " ";
            }
            std::cout << "\n";
        }
    }
};

// Dijkstra's algorithm for shortest path
class DijkstraGraph {
private:
    int vertices_;
    std::vector<std::vector<std::pair<int, int>>> adjList_; // {neighbor, weight}

public:
    DijkstraGraph(int vertices) : vertices_(vertices), adjList_(vertices) {}

    void addEdge(int u, int v, int weight) {
        adjList_[u].push_back({v, weight});
        adjList_[v].push_back({u, weight}); // Undirected
    }

    std::vector<int> shortestPath(int start) {
        std::vector<int> distance(vertices_, std::numeric_limits<int>::max());
        std::vector<bool> visited(vertices_, false);
        distance[start] = 0;

        for (int i = 0; i < vertices_ - 1; ++i) {
            // Find vertex with minimum distance
            int minDist = std::numeric_limits<int>::max();
            int minVertex = -1;

            for (int v = 0; v < vertices_; ++v) {
                if (!visited[v] && distance[v] < minDist) {
                    minDist = distance[v];
                    minVertex = v;
                }
            }

            if (minVertex == -1) break;
            visited[minVertex] = true;

            // Update distances
            for (auto& neighbor : adjList_[minVertex]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (!visited[v] && distance[minVertex] != std::numeric_limits<int>::max() &&
                    distance[minVertex] + weight < distance[v]) {
                    distance[v] = distance[minVertex] + weight;
                }
            }
        }

        return distance;
    }
};

int main() {
    std::cout << "=== Graph Algorithms Demo ===\n\n";

    // Create undirected graph
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);

    g.printGraph();
    std::cout << "\n";

    // Traversals
    g.BFS(0);
    g.DFS(0);
    g.DFSIterative(0);
    std::cout << "\n";

    // Cycle detection
    std::cout << "Has cycle: " << (g.hasCycleUndirected() ? "yes" : "no") << "\n\n";

    // Topological sort (create DAG)
    Graph dag(6, true); // Directed graph
    dag.addEdge(0, 1);
    dag.addEdge(0, 2);
    dag.addEdge(1, 3);
    dag.addEdge(2, 3);
    dag.addEdge(3, 4);
    dag.addEdge(4, 5);

    std::cout << "Topological sort: ";
    auto topoOrder = dag.topologicalSort();
    for (int vertex : topoOrder) {
        std::cout << vertex << " ";
    }
    std::cout << "\n\n";

    // Dijkstra's algorithm
    DijkstraGraph dg(5);
    dg.addEdge(0, 1, 4);
    dg.addEdge(0, 2, 1);
    dg.addEdge(2, 1, 2);
    dg.addEdge(1, 3, 1);
    dg.addEdge(2, 3, 5);
    dg.addEdge(3, 4, 3);

    auto distances = dg.shortestPath(0);
    std::cout << "Shortest distances from vertex 0:\n";
    for (int i = 0; i < distances.size(); ++i) {
        std::cout << "To " << i << ": " << distances[i] << "\n";
    }

    std::cout << "\n=== Tips ===\n";
    std::cout << "1. Use adjacency list for sparse graphs (most real graphs)\n";
    std::cout << "2. Use adjacency matrix for dense graphs or O(1) edge checks\n";
    std::cout << "3. BFS: shortest path in unweighted graphs, level-order\n";
    std::cout << "4. DFS: topological sort, cycle detection, path finding\n";
    std::cout << "5. Dijkstra: shortest path in weighted graphs (non-negative weights)\n";
    std::cout << "6. Bellman-Ford: handles negative weights, detects negative cycles\n";
    std::cout << "7. Topological sort only works on DAGs (Directed Acyclic Graphs)\n";

    return 0;
}