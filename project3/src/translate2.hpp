//
// Created by nanos on 2020/12/20.
//

#ifndef CS323_COMPLIERS_PROJECT3_SRC_TRANSLATE2_HPP
#define CS323_COMPLIERS_PROJECT3_SRC_TRANSLATE2_HPP

// private functions
InterCode *translate_Exp_RightElement(Node *exp, string place = "");

InterCode *translate_Exp_INT(Node *intExp);
InterCode *translate_Exp_Bio_Exp(Node *exp, string place = "");

InterCode *translate_Exp_Assign_Exp(Node *exp, const std::string &place = "");

#endif //CS323_COMPLIERS_PROJECT3_SRC_TRANSLATE2_HPP
