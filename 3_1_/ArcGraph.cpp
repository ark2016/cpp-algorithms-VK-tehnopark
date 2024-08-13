#include "ArcGraph.h"

ArcGraph::ArcGraph(int verticesCount) : verticesCount(verticesCount) {}

ArcGraph::ArcGraph(const IGraph &graph) : verticesCount(graph.VerticesCount()) {
    for (int i = 0; i < verticesCount; ++i) {
        const auto nextVertices = graph.GetNextVertices(i);
        for (int v: nextVertices) {
            AddEdge(i, v);
        }
    }
}

void ArcGraph::AddEdge(int from, int to) {
    arcs.emplace_back(from, to);
}

int ArcGraph::VerticesCount() const {
    return verticesCount;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;
    for (const auto &arc: arcs) {
        if (arc.first == vertex) {
            result.push_back(arc.second);
        }
    }
    return result;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;
    for (const auto &arc: arcs) {
        if (arc.second == vertex) {
            result.push_back(arc.first);
        }
    }
    return result;
}
