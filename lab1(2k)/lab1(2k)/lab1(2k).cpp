#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

struct Edge {
    int src, dest, weight;
};

struct Graph {
    int V, E;
    vector<Edge> edges;

    Graph(int v, int e) {
        V = v;
        E = e;
        edges.resize(e);
    }
};

bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

int find(vector<int>& parent, int i) {
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

void unionSets(vector<int>& parent, int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);
    parent[xroot] = yroot;
}

void algorithm(Graph& graph) {
    int V = graph.V;
    vector<Edge> result;
    vector<int> parent(V, -1);
    sort(graph.edges.begin(), graph.edges.end(), compareEdges);
    int e = 0;
    while (result.size() < V - 1 && e < graph.E) {
        Edge nextEdge = graph.edges[e++];

        int x = find(parent, nextEdge.src);
        int y = find(parent, nextEdge.dest);

        if (x != y) {
            result.push_back(nextEdge);
            unionSets(parent, x, y);
        }
    }

    int minWeight = 0;
    cout << "Ребра: " << endl;
    for (Edge edge : result) {
        cout << edge.src << " - " << edge.dest << " : " << edge.weight << endl;
        minWeight += edge.weight;
    }
    cout << "Вага: " << minWeight << endl;
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

    Graph graph(V, E);

    for (int i = 0; i < E; i++) {
        int src, dest, weight;
        input >> src >> dest >> weight;
        graph.edges[i] = { src, dest, weight };
    }

    input.close();

    algorithm(graph);

    return 0;
}
