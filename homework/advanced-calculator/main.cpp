#include <iostream>
#include "advancedCalculator.hpp"

std::string handleErrorCode(ErrorCode code) {
    switch (code) {
    case ErrorCode::OK:
        return "OK";
        break;
    case ErrorCode::BadCharacter:
        return "BadCharacter";
        break;
    case ErrorCode::BadFormat:
        return "BadFormat";
        break;
    case ErrorCode::DivideBy0:
        return "DivideBy0";
        break;
    case ErrorCode::ModuleOfNonIntegerValue:
        return "ModuleOfNonIntegerValue";
        break;
    case ErrorCode::SqrtOfNegativeNumber:
        return "SqrtOfNegativeNumber";
        break;
    default:
        return "Unknown Error";
        break;
    }
}

int main() {
    bool end_program = false;
    double result;
    ErrorCode code;
    std::string input;

    while (!end_program) {
        std::getline(std::cin, input);
        if (input == "q") {
            end_program = true;
        } else if ((code = process(input, &result)) == ErrorCode::OK) {
            std::cout << "Result: " << result << std::endl;
        } else {
            std::cout << handleErrorCode(code) << std::endl;
        }
    }
}