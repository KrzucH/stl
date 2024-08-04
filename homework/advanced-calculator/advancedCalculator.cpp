#include "advancedCalculator.hpp"

ErrorCode process(std::string input, double* output) {
    std::map<char, std::function<double(double, double)>> advCalc;
    advCalc['+'] = [](auto a, auto b) -> double { return a + b; };
    advCalc['-'] = [](auto a, auto b) -> double { return a - b; };
    advCalc['/'] = [](auto a, auto b) -> double { return a / b; };
    advCalc['*'] = [](auto a, auto b) -> double { return a * b; };
    advCalc['%'] = [](auto a, auto b) -> double { return static_cast<int>(a) % static_cast<int>(b); };
    advCalc['!'] = [](auto a, auto b) -> double { if(a < 0) {
                                                    a = std::tgamma(a + 1); 
                                                    return -a;
                                                } else {                                                     
                                                    return std::tgamma(a + 1);};
                                                };
    advCalc['^'] = [](auto a, auto b) -> double { if(a < 0 && b > 0) {
                                                    a = std::pow(a, b);
                                                    return -a;
                                                  } else {
                                                    return std::pow(a, b);};                                                  
                                                  };
    advCalc['$'] = [](auto a, auto b) -> double {};
    return ErrorCode::OK;
};