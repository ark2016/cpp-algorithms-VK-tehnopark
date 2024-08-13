#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "graph.h"
#include <vector>
#include <algorithm>

class UnionFind {
private:
    std::vector<int> parent, rank;

public:
    UnionFind(int n);

    int find(int u);

    void unite(int u, int v);
};

class Kruskal {
public:
    static std::vector<Edge> minimum_spanning_tree(const Graph &graph);
};

#endif