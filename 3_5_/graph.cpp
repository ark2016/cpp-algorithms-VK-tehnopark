#include "graph.h"

Graph::Graph(int n) : n(n), adj(n) {}

void Graph::addEdge(int u, int v, double weight) {
    adj[u].emplace_back(v, weight);
    adj[v].emplace_back(u, weight);
    edges.emplace_back(u, v, weight);
}

const std::vector<std::pair<int, double>> &Graph::neighbors(int u) const {
    return adj[u];
}

const std::vector<Edge> &Graph::getEdges() const {
    return edges;
}

int Graph::size() const {
    return n;
}