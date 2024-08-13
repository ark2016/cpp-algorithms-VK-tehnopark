#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include "IGraph.h"
#include <vector>
#include <list>

class ListGraph : public IGraph {
public:
    explicit ListGraph(int verticesCount);

    explicit ListGraph(const IGraph &graph);

    virtual ~ListGraph() = default;

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::list<int>> adjacencyLists;
};

#endif
