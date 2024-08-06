#include "advancedCalculator.hpp"

bool iskey(const char& key) {
    if (key == '+' || key == '^' || key == '%' || key == '$' || key == '!' || key == '/' || key == '*') {
        return true;
    } else {
        return false;
    }
}

ErrorCode process(std::string input, double* output) {
    std::map<char, std::function<double(double, double)>> advCalc;
    std::string numberStr1;
    std::string numberStr2;       
    char key;
    int counter{};
    int dotCounter{};

    advCalc['+'] = [](auto a, auto b) -> double { return a + b; };
    advCalc['-'] = [](auto a, auto b) -> double { return a - b; };
    advCalc['/'] = [](auto a, auto b) -> double { return a / b; };
    advCalc['*'] = [](auto a, auto b) -> double { return a * b; };
    advCalc['%'] = [](auto a, auto b) -> double { return static_cast<int>(a) % static_cast<int>(b); };
    advCalc['!'] = [](auto a, auto b) -> double { if (a < 0) {
                                                     a = -a;
                                                     a = std::tgamma(a + 1);
                                                     return -a;
                                                  } else {
                                                     return std::tgamma(a + 1);
                                                  };
                                                };
    advCalc['^'] = [](auto a, auto b) -> double { return std::pow(a, b); };
    advCalc['$'] = [](auto a, auto b) -> double { return std::pow(a, 1 / b); };

    if (input[0] == '-') {        
        numberStr1 += input[0];
    } else if (std::ispunct(input[0])) {
        return ErrorCode::BadFormat;
    } else {
        numberStr1 += input[0];
    }

    for (auto num : input) {
        if (std::isalpha(num)) {
            return ErrorCode::BadCharacter;
        } else if (iskey(num) || num == ',' || num == '.' || num == '-') {
        } else if (std::ispunct(num)) {
            return ErrorCode::BadCharacter;
        }
    }

    for (auto i = 1; i <= input.size(); i++) {
        if (input[i] == ',') {
            return ErrorCode::BadFormat;
        } else if (input[i] == '!' && i + 1 < input.size()) {
            return ErrorCode::BadFormat;
        } else if (iskey(input[i])) {
            ++counter;
            if (counter == 1) {
                key = input[i];
            }
            if (counter > 1) {
                return ErrorCode::BadFormat;
            }
        }

        if (input[i] == '.') {
            if (dotCounter >= 1) {
                if (counter == 0) {
                    return ErrorCode::BadFormat;
                } else if (dotCounter >= 2 && counter == 1) {
                    return ErrorCode::BadFormat;
                }
            }
            ++dotCounter;
        }

        if (key != input[i] && counter == 1) {
            numberStr2 += input[i];
        } else if (input[i] == '-' && counter == 0) {
            key = input[i];
            ++counter;
        } else if (key != input[i]) {
            numberStr1 += input[i];
        } else if (input[i] == '-') {
            numberStr2 += input[i];
        }

        if (input.size() - 1 == i) {
            if (numberStr2.empty()) {
                numberStr2 = "0";
            }
            if (std::stod(numberStr2) == -0 && key == '/') {
                return ErrorCode::DivideBy0;
            } else if (std::stod(numberStr1) < 0 && key == '$') {
                return ErrorCode::SqrtOfNegativeNumber;
            } else if (dotCounter > 0 && key == '%') {
                return ErrorCode::ModuleOfNonIntegerValue;
            } else if (advCalc[key]) {
                *output = advCalc[key](std::stod(numberStr1), std::stod(numberStr2));
                return ErrorCode::OK;
            }
        }
    }
    return ErrorCode::OK;
};
