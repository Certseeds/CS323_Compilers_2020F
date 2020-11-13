//
// Created by nanos on 2020/11/10.
//

#include "semanticError.hpp"

void variableRedefined(int lineNum, const std::string &name) {
    printf("Error type 3 at Line %d: redefine variable: %s\n", lineNum, name.c_str(), name.c_str());
}

void functionRedefined(int lineNum, const std::string &name) {
    printf("Error type 4 at Line %d: redefine function: %s", lineNum, name.c_str());
}

void semanticErrorOut(semanticError type, int lineNum, const std::string &name) {
    using std::unordered_map;
    using std::string;
    static const unordered_map<semanticError, string> ErrorType = {
            {semanticError::variableRedefined, R"()"},
    };
    printf("Error type %d at Line %d: %s: %s\n", static_cast<int>(type), lineNum, ErrorType.at(type).c_str(),
           name.c_str());
}
