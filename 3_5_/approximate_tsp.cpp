#include "approximate_tsp.h"
#include <unordered_set>
#include <stack>

std::vector<int> ApproximateTSP::findTspPath(const Graph &graph) {
    std::vector<Edge> mst_edges;

    mst_edges = Kruskal::minimum_spanning_tree(graph);
    std::vector<std::vector<int>> mst_adj(graph.size());

    for (const auto &edge: mst_edges) {
        mst_adj[edge.u].push_back(edge.v);
        mst_adj[edge.v].push_back(edge.u);
    }

    std::vector<int> euler_tour;
    std::unordered_set<int> visited;
    std::stack<int> stack;
    stack.push(0);

    int u;

    while (!stack.empty()) {
        u = stack.top();
        stack.pop();
        if (visited.insert(u).second) {
            euler_tour.push_back(u);
            for (int v: mst_adj[u]) {
                stack.push(v);
            }
        }
    }

    std::vector<int> tsp_path;
    std::unordered_set<int> tsp_visited;

    for (int node: euler_tour) {
        if (tsp_visited.insert(node).second) {
            tsp_path.push_back(node);
        }
    }
    tsp_path.push_back(tsp_path.front());

    return tsp_path;
}

double ApproximateTSP::computePathLength(const Graph &graph, const std::vector<int> &path) {
    double length;
    int u, v;

    length = 0.0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        u = path[i];
        v = path[i + 1];
        for (const auto &[neighbor, weight]: graph.neighbors(u)) {
            if (neighbor == v) {
                length += weight;
                break;
            }
        }
    }
    return length;
}