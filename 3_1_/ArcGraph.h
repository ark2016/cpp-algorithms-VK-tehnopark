#ifndef ARCGRAPH_H
#define ARCGRAPH_H

#include "IGraph.h"
#include <vector>

class ArcGraph : public IGraph {
public:
    explicit ArcGraph(int verticesCount);

    explicit ArcGraph(const IGraph &graph);

    virtual ~ArcGraph() = default;

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::pair<int, int>> arcs;
    int verticesCount;
};

#endif
