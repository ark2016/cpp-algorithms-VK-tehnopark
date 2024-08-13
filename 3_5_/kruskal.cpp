#include "kruskal.h"

UnionFind::UnionFind(int n) : parent(n), rank(n, 0) {
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
    }
}

int UnionFind::find(int u) {
    if (parent[u] != u) {
        parent[u] = find(parent[u]);
    }
    return parent[u];
}

void UnionFind::unite(int u, int v) {
    int root_u, root_v;
    root_u = find(u);

    root_v = find(v);
    if (root_u != root_v) {
        if (rank[root_u] < rank[root_v]) {
            parent[root_u] = root_v;
        } else if (rank[root_u] > rank[root_v]) {
            parent[root_v] = root_u;
        } else {
            parent[root_v] = root_u;
            rank[root_u]++;
        }
    }
}

std::vector<Edge> Kruskal::minimum_spanning_tree(const Graph &graph) {
    std::vector<Edge> mst_edges;
    std::vector<Edge> edges;

    edges = graph.getEdges();
    std::sort(edges.begin(), edges.end(), [](const Edge &e1, const Edge &e2) {
        return e1.weight < e2.weight;
    });
    UnionFind uf(graph.size());

    for (const auto &edge: edges) {
        if (uf.find(edge.u) != uf.find(edge.v)) {
            uf.unite(edge.u, edge.v);
            mst_edges.push_back(edge);
        }
    }

    return mst_edges;
}