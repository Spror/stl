#include "sort.hpp"
#include <algorithm>

std::deque<std::string> lengthSort(std::forward_list<std::string> str_fl) {
    std::deque<std::string> str_deq(str_fl.begin(), str_fl.end());

    std::sort(begin(str_deq), end(str_deq), [](const auto& str_1, const auto& str_2) {
        if (str_1.size() == str_2.size()) {
            return str_1 < str_2;
        }
        return str_1.size() < str_2.size();
    });

    return str_deq;
}