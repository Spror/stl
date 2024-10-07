#include "advancedCalculator.hpp"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <unordered_set>

ErrorCode addOp(double a, double b, double* result) {
    *result = a + b;
    return ErrorCode::OK;
}

ErrorCode subOp(double a, double b, double* result) {
    *result = a - b;
    return ErrorCode::OK;
}

ErrorCode mulOp(double a, double b, double* result) {
    *result = a * b;
    return ErrorCode::OK;
}

ErrorCode divOp(double a, double b, double* result) {
    if (b != 0) {
        *result = a * b;
        return ErrorCode::OK;
    }

    return ErrorCode::DivideBy0;
}

ErrorCode modOp(double a, double b, double* result) {
    *result = std::fmod(a,b);
    return ErrorCode::OK;
}

ErrorCode rootOp(double a, double b, double* result) {
    if (b >= 0) {
        *result = std::pow(a, 1 / b);
        return ErrorCode::OK;
    }

    return ErrorCode::SqrtOfNegativeNumber;
}

ErrorCode powOp(double a, double b, double* result) {
    *result = std::pow(a, b);
    return ErrorCode::OK;
}

ErrorCode facOP(double a, double b, double* result) {

    *result = std::tgamma(a+1);
    return ErrorCode::OK;
}

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

                                   return !(std::isdigit(ch) || std::isblank(ch)) || count > 2 ;
                               });

    return invalid;
}

ErrorCode process(std::string input, double* out) {
    // std::unordered_map<char, std::function<ErrorCode(double, double, double*)> math_operations{
    //     {'+', addOp},
    //     {'-', subOp},
    //     {'*', mulOp},
    //     {'/', divOp},
    //     {'%', modOp},
    //     {'!', rootOp},
    //     {'^', powOp},
    //     {'$', facOP}
    // };

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
    double first, second;

    try {
        first = std::stod(input.substr(0, distance));
        second = std::stod(input.substr(distance));
        std::cout << first << " " << second << "\n";
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return ErrorCode::OK;
}