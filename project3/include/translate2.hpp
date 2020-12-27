//
// Created by nanos on 2020/12/20.
//

#ifndef CS323_COMPLIERS_PROJECT3_INCLUDE_TRANSLATE2_HPP
#define CS323_COMPLIERS_PROJECT3_INCLUDE_TRANSLATE2_HPP

// private functions
InterCode *translate_Exp_RightElement(Node *exp, const string& place = "");

InterCode *translate_Exp_INT(Node *intExp);

InterCode *translate_Exp_Bio_Exp(Node *exp, const string& place = "");

InterCode *translate_Exp_Assign_Exp(Node *exp, const std::string &place = "");

void translate_Cond(Node *stmt, string label_true, const string& label_false);

static void insertAJumpLabelToExpNode(Node *exp, string labelName);

static void insertAGotoLabelToExpNode(Node *exp, string labelName);

#endif //CS323_COMPLIERS_PROJECT3_INCLUDE_TRANSLATE2_HPP
