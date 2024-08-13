#include "ListGraph.h"

ListGraph::ListGraph(int verticesCount) {
    adjacencyLists.resize(verticesCount);
}

ListGraph::ListGraph(const IGraph &graph) {
    int verticesCount = graph.VerticesCount();
    adjacencyLists.resize(verticesCount);

    for (int i = 0; i < verticesCount; ++i) {
        const auto nextVertices = graph.GetNextVertices(i);
        for (int v: nextVertices) {
            AddEdge(i, v);
        }
    }
}

void ListGraph::AddEdge(int from, int to) {
    adjacencyLists[from].push_back(to);
}

int ListGraph::VerticesCount() const {
    return adjacencyLists.size();
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    std::vector<int> result(adjacencyLists[vertex].begin(), adjacencyLists[vertex].end());
    return result;
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;
    for (int i = 0; i < adjacencyLists.size(); ++i) {
        for (int v: adjacencyLists[i]) {
            if (v == vertex) {
                result.push_back(i);
                break;
            }
        }
    }
    return result;
}
