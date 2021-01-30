/*
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-12-27 20:19:22
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-12-29 13:22:49
 */
//
// Created by nanos on 2020/12/20.
//

#ifndef CS323_COMPILERS_PROJECT3_INCLUDE_TRANSLATE2_HPP
#define CS323_COMPILERS_PROJECT3_INCLUDE_TRANSLATE2_HPP

// private functions
InterCode *translate_Exp_RightElement(Node *exp, const string& place = "");

InterCode *translate_Exp_INT(Node *intExp);

InterCode *translate_Exp_Bio_Exp(Node *exp, const string& place = "");

InterCode *translate_Exp_Assign_Exp(Node *exp, const std::string &place = "");

static void translate_Cond(Node *stmt, string label_true, const string& label_false);

inline static void insertAJumpLabelToExpNode(Node *exp, string labelName);

inline static void insertAGotoLabelToExpNode(Node *exp, string labelName);

#endif //CS323_COMPILERS_PROJECT3_INCLUDE_TRANSLATE2_HPP
