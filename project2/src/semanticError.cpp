//
// Created by nanos on 2020/11/10.
//

#include "semanticError.hpp"


void variableNoDefinition(int lineNum, const std::string &name) {
    printf("Error type 1 at Line %d: undefined variable: %s\n", lineNum, name.c_str());
}

void functionNoDefinition(int lineNum, const std::string &name) {
    printf("Error type 2 at Line %d: undefined function: %s\n", lineNum, name.c_str());
}

void variableRedefined(int lineNum, const std::string &name) {
    printf("Error type 3 at Line %d: redefine variable: %s\n", lineNum, name.c_str());
}

void functionRedefined(int lineNum, const std::string &name) {
    printf("Error type 4 at Line %d: redefine function: %s\n", lineNum, name.c_str());
}

void rvalueLeftSetError(int lineNum) {
    printf("Error type 6 at Line %d: left side in assignment is rvalue\n", lineNum);
}

void binaryOperatorNonNumber(int lineNum) {
    printf("Error type 7 at Line %d: binary operation on non-number variables\n", lineNum);
}

void invalidArgumentNumber(int lineNum, const std::string &name, int expect, int actually) {
    printf("Error type 9 at Line %d: invalid argument number for %s, expect %d, got %d\n", lineNum, name.c_str(),
           expect, actually);
}

void invalidArgumentType(int lineNum, const std::string &name, const std::string &expect, const std::string &actually) {
    printf("Error type 9 at Line %d: invalid argument type for %s, expect %s, got %s\n", lineNum, name.c_str(),
           expect.c_str(), actually.c_str());
}

void indexOnNonArray(int lineNum) {
    printf("Error type 10 at Line %d: indexing on non-array variable\n", lineNum);
}

void invokeNonFunctionVariable(int lineNum, const std::string &name) {
    printf("Error type 11 at Line %d: invoking non-function variable: %s\n", lineNum, name.c_str());
}

void nonStructFVariable(int lineNum) {
    printf("Error type 13 at Line %d: accessing with non-struct variable\n", lineNum);
}

void noSuchMember(int lineNum, const std::string &name) {
    printf("Error type 14 at Line %d: no such member: %s\n", lineNum, name.c_str());
}


void structRedefined(int lineNum, const std::string &name) {
    printf("Error type 15 at Line %d: redefine struct: %s\n", lineNum, name.c_str());
}

void nonIntegerTypeIndexing(int lineNum) {
    printf("Error type 12 at Line %d: indexing by non-integer\n", lineNum);
}