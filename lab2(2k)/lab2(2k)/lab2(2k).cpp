#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
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
        adj[dest].push_back({ src, weight });
    }
};
void algorithm(Graph& graph) {
    int V = graph.V;
    vector<bool> inMST(V, false);
    vector<int> key(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<vector<int>> path(V); 
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    int startVertex = 0;
    pq.push({ 0, startVertex });
    key[startVertex] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;

        for (const Edge& edge : graph.adj[u]) {
            int v = edge.dest;
            int weight = edge.weight;

            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push({ key[v], v });
            }
        }
    }
    int minWeight = 0;
    cout << "Ребра" << endl;
    for (int i = 1; i < V; i++) {
        cout << parent[i] << " - " << i << " : " << key[i] << endl;
        minWeight += key[i];
        stack<int> pathStack;
        int currentVertex = i;
        while (currentVertex != startVertex) {
            pathStack.push(currentVertex);
            currentVertex = parent[currentVertex];
        }
        pathStack.push(startVertex);

        cout << "Шлях від " << startVertex << " до " << i << ": ";
        while (!pathStack.empty()) {
            cout << pathStack.top();
            pathStack.pop();
            if (!pathStack.empty()) {
                cout << " -> ";
            }
        }
        cout << endl;

    }
    cout << "Вага " << minWeight << endl;
}

int main() {
    setlocale(LC_ALL, "ukr");
    ifstream input("input.txt");
    if (!input) {
        cerr << "Помилка" << endl;
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
    input.close();
    algorithm(graph);
    return 0;
}
