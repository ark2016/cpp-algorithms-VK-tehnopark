#ifndef APPROXIMATE_TSP_H
#define APPROXIMATE_TSP_H

#include "graph.h"
#include "kruskal.h"
#include <vector>

class ApproximateTSP {
public:
    static std::vector<int> findTspPath(const Graph &graph);

    static double computePathLength(const Graph &graph, const std::vector<int> &path);
};

#endif