#include "advancedCalculator.hpp"
#include <algorithm>
#include <cctype>
#include <unordered_set>

bool isValid(std::string input) {
    static const std::unordered_set<char> valid_signs{'+', '-', '/', '*', '%', '!', '^', '$', '.'};

    auto invalid = std::any_of(begin(input), end(input),
                               [](const auto& ch) {
                                   return !std::isdigit(ch) && !valid_signs.contains(ch);
                               });

    return !invalid;
}

ErrorCode process(std::string input, double* out) {
    ErrorCode code;

    if (isValid(input)) {
        code = ErrorCode::BadCharacter;
        return code;
    }

    return code;
}