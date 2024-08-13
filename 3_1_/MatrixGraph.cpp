#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int verticesCount)
        : verticesCount(verticesCount), adjacencyMatrix(verticesCount, std::vector<bool>(verticesCount, false)) {}

MatrixGraph::MatrixGraph(const IGraph &other)
        : MatrixGraph(other.VerticesCount()) {
    for (int from = 0; from < verticesCount; ++from) {
        for (int to: other.GetNextVertices(from)) {
            AddEdge(from, to);
        }
    }
}

void MatrixGraph::AddEdge(int from, int to) {
    if (0 <= from && from < verticesCount && 0 <= to && to < verticesCount) {
        adjacencyMatrix[from][to] = true;
    }
}

int MatrixGraph::VerticesCount() const {
    return verticesCount;
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    std::vector<int> nextVertices;
    if (0 <= vertex && vertex < verticesCount) {
        for (int to = 0; to < verticesCount; ++to) {
            if (adjacencyMatrix[vertex][to]) {
                nextVertices.push_back(to);
            }
        }
    }
    return nextVertices;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    std::vector<int> prevVertices;
    if (0 <= vertex && vertex < verticesCount) {
        for (int from = 0; from < verticesCount; ++from) {
            if (adjacencyMatrix[from][vertex]) {
                prevVertices.push_back(from);
            }
        }
    }
    return prevVertices;
}
