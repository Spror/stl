#include "advancedCalculator.hpp"
#include <algorithm>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <unordered_set>

using MathOp = ErrorCode (*)(double, double, double*);

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
        *result = a / b;
        return ErrorCode::OK;
    }

    return ErrorCode::DivideBy0;
}

ErrorCode modOp(double a, double b, double* result) {
    if (a == static_cast<int>(a) && b == static_cast<int>(b)) {
        *result = std::fmod(a, b);
        return ErrorCode::OK;
    }

    return ErrorCode::ModuleOfNonIntegerValue;
}

ErrorCode rootOp(double a, double b, double* result) {
    if (a >= 0) {
        *result = std::pow(a, 1.0 / b);
        return ErrorCode::OK;
    }

    return ErrorCode::SqrtOfNegativeNumber;
}

ErrorCode powOp(double a, double b, double* result) {
    *result = std::pow(a, b);
    return ErrorCode::OK;
}

ErrorCode facOp(double a, double b, double* result) {
    if (a >= 0)
        *result = std::tgamma(a + 1);
    else
        *result = -1 * std::tgamma(std::abs(a) + 1);

    return ErrorCode::OK;
}

bool containsInvalidCharacter(std::string input) {
    static const std::unordered_set<char> valid_signs{'+', '-', '/', '*', '%', '!', '^', '$', '.', ','};

    auto valid = std::all_of(begin(input), end(input),
                             [](const auto& ch) {
                                 return std::isdigit(ch) || valid_signs.contains(ch) || std::isblank(ch);
                             });

    return !valid;
}

bool containsInvalidFormat(std::string input, int* distance) {
    static const std::unordered_set<char> valid_operators{'+', '-', '/', '*', '%', '!', '^', '$'};

    auto op_iter = std::find_if(std::next(begin(input), 1), end(input),
                                [](const auto& ch) {
                                    return valid_operators.contains(ch);
                                });

    // If no operator is found, the format is invalid
    if (op_iter == end(input)) {
        return true;
    }

    if (op_iter == std::prev(end(input))) {
        if (*op_iter == '!') {
            return false;
        } else {
            return true;
        }
    }

    *distance = std::distance(begin(input), op_iter);

    // Count occurrences of '.' to check if the format is correct
    if (std::count(begin(input), op_iter, '.') > 1 || std::count(op_iter, end(input), '.') > 1) {
        return true;
    }

    input.erase(op_iter);

    // Count occurrences of '-' to check if the format is correct
    if (std::count(begin(input), end(input), '-') > 2) {
        return true;
    }

    auto valid = std::all_of(begin(input), end(input),
                             [](const auto& ch) mutable {
                                 return std::isdigit(ch) || std::isblank(ch) || ch == '-' || ch == '.';
                             });

    return !valid;
}

ErrorCode process(std::string input, double* out) {
    std::unordered_map<char, MathOp> math_operations{
        {'+', addOp},
        {'-', subOp},
        {'*', mulOp},
        {'/', divOp},
        {'%', modOp},
        {'!', facOp},
        {'^', powOp},
        {'$', rootOp}};

    int distance;

    if (containsInvalidCharacter(input)) {
        return ErrorCode::BadCharacter;
    }

    if (containsInvalidFormat(input, &distance)) {
        return ErrorCode::BadFormat;
    }

    char op = input[distance];
    double a, b{0.0};

    try {
        a = std::stod(input.substr(0, distance));
        if (op != input.back())
            b = std::stod(input.substr(distance + 1));
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return math_operations[op](a, b, out);
}