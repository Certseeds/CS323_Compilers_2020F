//
// Created by nanos on 2020/11/7.
//

#ifndef CS323_COMPLIERS_PROJECT2_SRC_VISITSYNTAXTREE_TWO_HPP
#define CS323_COMPLIERS_PROJECT2_SRC_VISITSYNTAXTREE_TWO_HPP


#include "type.hpp"
#include "node.hpp"

/**
 * private functions that do not show outside
 * */
void defStructTypeVisit(Node *node);

void defPureTypeVisit(Node *node);

string getStrValueFromDecList(Node *node);

void defStructDefinition(Node *node);

void defStructObjectDefinition(Node *node);

FieldList *getFiledListFromDefList(Node *node);

void extDefVisit_SES_PureType(Node *node);

void extDefVisit_SES_StructType(Node *node);

Array *getArrayFromVarDec(Node *node, Type *type);

// func is a single print file
void checkTypeMatchType(Type *leftType, Type *rightType, int lineNum, const std::function<void(int)> &func);

void checkReturnValueFromStmtList(Type *type, Node *stmtList);

void checkReturnValueFromStmt(Type *type, Node *stmt);

void checkReturnValueFromCompStmt(Type *type, Node *compStmt);

void getNamesOfDefList(Node *node, vector<Node *> &namesofFileds);

#endif //CS323_COMPLIERS_PROJECT2_SRC_VISITSYNTAXTREE_TWO_HPP
