#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <tuple>
#include <cmath>
#include <algorithm>

struct Edge {
    int u, v;
    double weight;

    Edge(int u, int v, double weight) : u(u), v(v), weight(weight) {}
};

class Graph {
private:
    std::vector<std::vector<std::pair<int, double>>> adj;
    std::vector<Edge> edges;
    int n;

public:
    Graph(int n);

    void addEdge(int u, int v, double weight);

    const std::vector<std::pair<int, double>> &neighbors(int u) const;

    const std::vector<Edge> &getEdges() const;

    int size() const;
};

#endif