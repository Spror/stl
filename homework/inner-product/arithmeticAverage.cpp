#include "arithmeticAverage.hpp"
#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>

double ArithmeticAverage(const std::vector<int>& first, const std::vector<int>& second) {
    if (first.empty() && second.empty()) {
        return 0.0;
    }

    return (std::reduce(begin(first), end(first)) + std::reduce(begin(second), end(second))) / ((double)(first.size() + second.size()));
}

double Distance(const std::vector<int>& first, const std::vector<int>& second) {
    if (first.size() != second.size()) {
        throw std::invalid_argument("Vectors must have the same size");
    }

    double sum_of_squares = std::transform_reduce(begin(first), end(first),
                                                  begin(second),
                                                  0,
                                                  std::plus<>(),
                                                  [](const auto& x, const auto& y) {
                                                      return pow((x - y), 2);
                                                  });

    return std::sqrt(sum_of_squares);
}