#include "palindrome.hpp"
#include <algorithm>
#include <iostream>

bool is_palindrome(std::string str) {
    str.erase(std::remove_if(begin(str), end(str), [](const auto& x) {
                  return !std::isalnum(x);
              }),
              end(str));

    std::transform(begin(str), end(str), begin(str), [](auto& ch) {
        return std::tolower(ch);
    });

    return std::equal(begin(str), end(str), str.rbegin(), str.rend());
}