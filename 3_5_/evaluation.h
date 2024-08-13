#ifndef EVALUATION_H
#define EVALUATION_H

#include "graph.h"
#include "approximate_tsp.h"
#include "point_generator.h"
#include <vector>
#include <tuple>

class Evaluation {
public:
    static std::tuple<double, double> evaluateApproximation(int n, int trials);

private:
    static Graph buildCompleteGraph(const std::vector<std::pair<double, double>> &points);

    static double computeOptimalTspLength(const Graph &graph);
};

#endif