//
// Created by nanos on 2020/12/20.
//

#ifndef CS323_COMPLIERS_PROJECT3_SRC_TRANSLATE_HPP
#define CS323_COMPLIERS_PROJECT3_SRC_TRANSLATE_HPP

#include <string>
#include <unordered_map>
#include "type.hpp"
#include "node.hpp"
#include "interCode.hpp"
using std::string;
using std::unordered_map;
extern unordered_map<string, Type *> symbolTable;

InterCode *translate_Exp(Node *exp, string place = "");
InterCode *translate_Stmt(Node *stmt);
InterCode* translate_functionInvoke(Node *stmt);
InterCode* translate_functionWithParamInvoke(Node *stmt);
InterCode* translate_enterFunction(Node *stmt);
InterCode * translate_Return(Node* stmt);
#endif //CS323_COMPLIERS_PROJECT3_SRC_TRANSLATE_HPP
