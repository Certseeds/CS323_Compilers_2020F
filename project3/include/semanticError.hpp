//
// Created by nanos on 2020/11/10.
//

#ifndef CS323_COMPILERS_PROJECT3_INCLUDE_SEMANTICERROR_HPP
#define CS323_COMPILERS_PROJECT3_INCLUDE_SEMANTICERROR_HPP

#include <string>
#include <unordered_map>


// error type 1
void variableNoDefinition(int lineNum, const std::string &name);

// error type 2
void functionNoDefinition(int lineNum, const std::string &name);

// error type 3
void variableRedefined(int lineNum, const std::string &name);

// error type 4
void functionRedefined(int lineNum, const std::string &name);

// error type 5
void nonMatchTypeBothSide(int lineNum);

// error type 6
void rvalueLeftSetError(int lineNum);

// error type 7
void binaryOperatorNonNumber(int lineNum);

// error type 8
void returnTypeDisMatch(int lineNum);

// error type 9
void invalidArgumentNumber(int lineNum, const std::string &name, int expect, int actually);

// error type 9
void invalidArgumentType(int lineNum, const std::string &name, const std::string &expect, const std::string &actually);

// error type 10
void indexOnNonArray(int lineNum);


//error type 11
void invokeNonFunctionVariable(int lineNum, const std::string &name);

// error type 12
void nonIntegerTypeIndexing(int lineNum);

// error type 13
void nonStructFVariable(int lineNum);

// error type 14
void noSuchMember(int lineNum, const std::string &name);

// error type 15
void structRedefined(int lineNum, const std::string &name);

// error type 16
void structNoDefinition(int lineNum, const std::string &name);


#endif //! CS323_COMPILERS_PROJECT3_INCLUDE_SEMANTICERROR_HPP
