#include "evaluation.h"
#include <algorithm>
#include <numeric>
#include <cmath>

Graph Evaluation::buildCompleteGraph(const std::vector<std::pair<double, double>> &points) {
    int n;

    n = points.size();
    Graph graph(n);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double weight = std::sqrt(std::pow(points[i].first - points[j].first, 2) +
                                      std::pow(points[i].second - points[j].second, 2));
            graph.addEdge(i, j, weight);
        }
    }
    return graph;
}

double Evaluation::computeOptimalTspLength(const Graph &graph) {
    std::vector<int> permutation(graph.size());
    std::iota(permutation.begin(), permutation.end(), 0);
    double optimal_length, path_length;
    int u, v;

    optimal_length = std::numeric_limits<double>::max();
    do {
        path_length = 0.0;
        for (size_t i = 0; i < permutation.size() - 1; ++i) {
            u = permutation[i];
            v = permutation[i + 1];
            for (const auto &[neighbor, weight]: graph.neighbors(u)) {
                if (neighbor == v) {
                    path_length += weight;
                    break;
                }
            }
        }
        u = permutation.back();
        v = permutation.front();
        for (const auto &[neighbor, weight]: graph.neighbors(u)) {
            if (neighbor == v) {
                path_length += weight;
                break;
            }
        }
        optimal_length = std::min(optimal_length, path_length);
    } while (std::next_permutation(permutation.begin(), permutation.end()));

    return optimal_length;
}

std::tuple<double, double> Evaluation::evaluateApproximation(int n, int trials) {
    std::vector<double> ratios;
    std::vector<std::pair<double, double>> points;
    std::vector<int> tsp_path;
    double optimal_length, approx_length, ratio, sum, mean, variance, stddev;

    for (int i = 0; i < trials; ++i) {
        points = PointGenerator::generate_points(n);
        Graph graph = buildCompleteGraph(points);
        tsp_path = ApproximateTSP::findTspPath(graph);
        approx_length = ApproximateTSP::computePathLength(graph, tsp_path);
        optimal_length = computeOptimalTspLength(graph);
        ratio = approx_length / optimal_length;
        ratios.push_back(ratio);
    }
    sum = std::accumulate(ratios.begin(), ratios.end(), 0.0);
    mean = sum / ratios.size();
    variance = std::accumulate(ratios.begin(), ratios.end(), 0.0, [mean](double acc, double x) {
        return acc + (x - mean) * (x - mean);
    }) / ratios.size();
    stddev = std::sqrt(variance);

    return {mean, stddev};
}