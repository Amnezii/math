#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <limits>
#include <stack>

using namespace std;

struct Edge {
    int dest, weight;
};


struct Graph {
    int V;
    vector<vector<Edge>> adj;

    Graph(int v) {
        V = v;
        adj.resize(v);
    }

    void addEdge(int src, int dest, int weight) {
        adj[src].push_back({ dest, weight });
    }
};

void algorithm(Graph& graph, int startVertex, int endVertex) {
    int V = graph.V;
    vector<int> distance(V, numeric_limits<int>::max());
    vector<int> parent(V, -1);
    distance[startVertex] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, startVertex });

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const Edge& edge : graph.adj[u]) {
            int v = edge.dest;
            int weight = edge.weight;

            if (distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                parent[v] = u;
                pq.push({ distance[v], v });
            }
        }
    }

    cout << "Шлях від " << startVertex << " до " << endVertex << ":" << endl;
    int currentVertex = endVertex;
    stack<int> pathStack;
    while (currentVertex != -1) {
        pathStack.push(currentVertex);
        currentVertex = parent[currentVertex];
    }
    while (!pathStack.empty()) {
        cout << pathStack.top();
        pathStack.pop();
        if (!pathStack.empty()) {
            cout << " -> ";
        }
    }
    cout << endl;
    cout << "Вага: " << distance[endVertex] << endl;
}

int main() {
    setlocale(LC_ALL, "rus");
    ifstream input("input.txt");
    if (!input) {
        cout << "Помилка" << endl;
        return 1;
    }

    int V, E;
    input >> V >> E;

    Graph graph(V);

    for (int i = 0; i < E; i++) {
        int src, dest, weight;
        input >> src >> dest >> weight;
        graph.addEdge(src, dest, weight);
    }

    int startVertex, endVertex;
    input >> startVertex >> endVertex;

    input.close();

    algorithm(graph, startVertex, endVertex);

    return 0;
}
