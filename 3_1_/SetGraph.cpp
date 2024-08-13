#include "SetGraph.h"

SetGraph::SetGraph(int verticesCount)
        : verticesCount(verticesCount), adjacencyList(verticesCount) {}

SetGraph::SetGraph(const IGraph &graph)
        : SetGraph(graph.VerticesCount()) {
    for (int from = 0; from < verticesCount; ++from) {
        for (int to: graph.GetNextVertices(from)) {
            AddEdge(from, to);
        }
    }
}

void SetGraph::AddEdge(int from, int to) {
    adjacencyList[from].insert(to);
}

int SetGraph::VerticesCount() const {
    return verticesCount;
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    std::vector<int> result(adjacencyList[vertex].begin(), adjacencyList[vertex].end());
    return result;
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;
    for (int from = 0; from < verticesCount; ++from) {
        if (adjacencyList[from].count(vertex) > 0) {
            result.push_back(from);
        }
    }
    return result;
}
