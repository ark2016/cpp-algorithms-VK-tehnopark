#ifndef POINT_GENERATOR_H
#define POINT_GENERATOR_H

#include <vector>
#include <random>
#include <cmath>

class PointGenerator {
public:
    static std::vector<std::pair<double, double>> generate_points(int n, double mean = 0.0, double stddev = 1.0);
};

#endif