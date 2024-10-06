#include "arithmeticAverage.hpp"
#include <numeric>

double ArithmeticAverage(const std::vector<int>& first, const std::vector<int>& second) {
    if (first.empty() && second.empty()) {
        return 0.0;
    }

    return (std::reduce(begin(first), end(first)) + std::reduce(begin(second), end(second))) / ((double)(first.size() + second.size()));
}
