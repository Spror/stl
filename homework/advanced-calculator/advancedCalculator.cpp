#include "advancedCalculator.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <iterator>
#include <unordered_set>

bool containsInvalidCharacter(std::string input) {
    static const std::unordered_set<char> valid_signs{'+', '-', '/', '*', '%', '!', '^', '$', '.'};

    auto invalid = std::any_of(begin(input), end(input),
                               [](const auto& ch) {
                                   return !(std::isdigit(ch) || valid_signs.contains(ch));
                               });

    return invalid;
}

bool containsInvalidFormat(std::string input, int* distance) {
    static const std::unordered_set<char> valid_operators{'+', '-', '/', '*', '%', '!', '^', '$'};
    std::string first_str, second_str;

    auto midle = std::find_if(begin(input), end(input),
                              [](const auto& ch) {
                                  return valid_operators.contains(ch);
                              });

    *distance = std::distance(begin(input), midle);

    std::rotate(begin(input), midle, end(input));

    auto invalid = std::any_of(begin(input) + 1, end(input),
                               [count(0)](const auto& ch) mutable {
                                   if (ch == '.')
                                       count++;

                                   return !(std::isdigit(ch) || std::isblank(ch)) || count > 2;
                               });

    return invalid;
}

ErrorCode process(std::string input, double* out) {
    ErrorCode code;
    int distance;

    if (containsInvalidCharacter(input)) {
        code = ErrorCode::BadCharacter;
        return code;
    }

    if (containsInvalidFormat(input, &distance) || distance == 0) {
        code = ErrorCode::BadFormat;
        return code;
    }

    char op = input[distance];
    //auto first = std::stod();

    return ErrorCode::OK;
}