#include "point_generator.h"

std::vector<std::pair<double, double>> PointGenerator::generate_points(int n, double mean, double stddev) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dist(mean, stddev);
    std::vector<std::pair<double, double>> points;
    double u1, u2;

    for (int i = 0; i < n; ++i) {
        u1 = dist(gen);
        u2 = dist(gen);
        points.emplace_back(u1, u2);
    }

    return points;
}