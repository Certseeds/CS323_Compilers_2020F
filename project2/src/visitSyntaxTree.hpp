//
// Created by nanos on 2020/11/7.
//

#ifndef CS323_COMPLIERS_VISITSYNTAXTREE_HPP
#define CS323_COMPLIERS_VISITSYNTAXTREE_HPP


#include <string>
#include <unordered_map>
#include "type.hpp"
#include "node.hpp"

using std::string;
using std::unordered_map;
extern unordered_map<string, Type *> symbolTable;

void defVisit(Node *node);

void extDefVisit_SES(Node *node);

void extDefVisit_SS(Node *node);

void extDefVisit_SFC(Node *node);

void expVisit(Node *node);

#endif //CS323_COMPLIERS_VISITSYNTAXTREE_HPP
