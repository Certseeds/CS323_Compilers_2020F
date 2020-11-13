//
// Created by nanos on 2020/11/10.
//

#ifndef CS323_COMPLIERS_PROJECT2_SRC_SEMANTICERROR_HPP
#define CS323_COMPLIERS_PROJECT2_SRC_SEMANTICERROR_HPP

#include <string>
#include <unordered_map>

enum class semanticError {
    variableRedefined = 3,
};

void variableRedefined(int lineNum, const std::string &name);

void functionRedefined(int lineNum, const std::string &name);

void semanticErrorOut(semanticError type, int lineNum, const std::string &name = "");


#endif //! CS323_COMPLIERS_PROJECT2_SRC_SEMANTICERROR_HPP
