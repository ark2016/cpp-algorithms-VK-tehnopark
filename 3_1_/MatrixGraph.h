#ifndef MATRIX_GRAPH_H
#define MATRIX_GRAPH_H

#include "IGraph.h"
#include <vector>

class MatrixGraph : public IGraph {
public:
    explicit MatrixGraph(int verticesCount);

    explicit MatrixGraph(const IGraph &other);

    ~MatrixGraph() override = default;

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<bool>> adjacencyMatrix;
    int verticesCount;
};

#endif