//
// Created by nanos on 2020/12/20.
//

#include "translate.hpp"
#include "translate2.hpp"

#include <utility>


using std::string;
using std::unordered_map;
inline static constexpr int32_t begin_sign = 0;

inline void nodeInterCodeMerge(Node *firstArg, Node *node) {
    for (const auto &item : node->intercodes) {
        firstArg->intercodes.push_back(item);
    }
}

inline void nodeInterCodeMerge(Node *firstArg, std::initializer_list<Node *> nodes) {
    for (const auto &node : nodes) {
        nodeInterCodeMerge(firstArg, node);
    }
}

inline void nodeInterCodeMerge(Node *firstArg, const std::vector<Node *> &nodes) {
    for (const auto &node : nodes) {
        nodeInterCodeMerge(firstArg, node);
    }
}

static const unordered_map<Node *, InterCodeType> BioOpNodes = [] {
    static const unordered_map<Node *, InterCodeType> init{
            {Node::getSingleNameNodePointer("PLUS"),  InterCodeType::ADD},
            {Node::getSingleNameNodePointer("MINUS"), InterCodeType::SUB},
            {Node::getSingleNameNodePointer("MUL"),   InterCodeType::MUL},
            {Node::getSingleNameNodePointer("DIV"),   InterCodeType::DIV}};
    return init;
}();

static string new_temp() {
    static int tempValueTemp = begin_sign;
    return string("t").append(std::to_string(tempValueTemp++));
}

static string new_label() {
    static int tempValueLabel = begin_sign + 1;
    return string("label").append(std::to_string(tempValueLabel++));
}

InterCode *translate_Exp(Node *exp, const string &place) {
    InterCode *will_return = nullptr;
    switch (exp->nodes.size()) {
        case 1: {
            if (exp->get_nodes(0)->name == "INT") {
                will_return = translate_Exp_INT(exp);
            } else {
                will_return = translate_Exp_RightElement(exp, place);
            }
            break;
        }
        case 3: {
            if (exp->get_nodes(0)->name == "Exp" && exp->get_nodes(2)->name == "Exp") {
                auto *const middleSign = exp->get_nodes(1);
                if (middleSign == Node::getSingleNameNodePointer("ASSIGN")) {
                    will_return = translate_Exp_Assign_Exp(exp, place);
                } else if (BioOpNodes.count(middleSign) != 0) {
                    will_return = translate_Exp_Bio_Exp(exp, place);
                }
            }
            break;
        }
    }
    std::cout.flush();
    return will_return;
}

string getNameFromANode(Node *exp) {
    if (exp->interCode != nullptr) {
        return exp->interCode->assign.left->variName;
    } else if (!exp->nodes.empty() && exp->get_nodes(0)->name == "ID") {
        return std::get<string>(exp->get_nodes(0)->value);
    }
}

InterCode *translate_Exp_Bio_Exp(Node *exp, const string &place) {
    auto *const leftNode = exp->get_nodes(0);
    auto *const bioOp = exp->get_nodes(1);
    auto *const rightNode = exp->get_nodes(2);

    auto leftVariName = getNameFromANode(leftNode);
    auto rightExpLeftName = getNameFromANode(rightNode);
    auto *const will_return = new InterCode(BioOpNodes.at(bioOp));
    auto *const will_return_result = new Operand(OperandType::VARIABLE, new_temp());
    auto *const will_return_op2 = new Operand(OperandType::VARIABLE, leftVariName);
    auto *const will_return_op1 = new Operand(OperandType::VARIABLE, rightExpLeftName);
    will_return->bioOp = {will_return_result, will_return_op2, will_return_op1};
    exp->interCode = will_return;
    nodeInterCodeMerge(exp, {leftNode, rightNode});
    exp->intercodes.push_back(will_return);
    return will_return;
}

InterCode *translate_Exp_INT(Node *exp) {
    auto *intExp = exp->get_nodes(0);
    int intExpValue = std::get<int>(intExp->value);
    static unordered_map<int, InterCode *> store_map;
    //    if (store_map.count(intExpValue) != 0) {
    //        return store_map[intExpValue];
    //    }
    auto *const leftPlace = new Operand(OperandType::VARIABLE, new_temp());
    auto *const rightValue = new Operand(OperandType::CONSTANT, intExpValue);
    auto *const will_return = new InterCode(InterCodeType::ASSIGN);
    will_return->assign.left = leftPlace;
    will_return->assign.right = rightValue;
    store_map[intExpValue] = will_return;
    exp->interCode = will_return;
    exp->intercodes.push_back(will_return);
    return will_return;
}

InterCode *translate_Exp_RightElement(Node *exp, const string &place) {
    //先只考虑进来的exp就是ID的情况
    auto stringOfVari = std::get<string>(exp->get_nodes(0)->value);
    if (stringOfVari == "read") {
        auto *will_return = new InterCode(InterCodeType::READ);
        auto *readParam = new Operand(OperandType::VARIABLE);
        readParam->variName = place;
        will_return->SingleElement = readParam;
        return will_return;
    }
    //auto variable = symbolTable[stringOfVari];
    auto *const will_return = new InterCode(InterCodeType::ASSIGN);
    auto *const leftPlace = new Operand(OperandType::VARIABLE);
    leftPlace->variName = place;
    auto *const rightValue = new Operand(OperandType::VARIABLE);
    rightValue->variName = stringOfVari;
    will_return->assign.left = leftPlace;
    will_return->assign.right = rightValue;
    return will_return;
}

InterCode *translate_Exp_Assign_Exp(Node *const exp, const std::string &place) {
    Node *const subnodes[3]{exp->get_nodes(0), exp->get_nodes(1), exp->get_nodes(2)};
    auto *const leftNode = subnodes[0];
    auto *const rightNode = subnodes[2];
    auto leftVariName = std::get<string>(leftNode->get_nodes(0)->value);
    auto rightExpLeftName = getNameFromANode(rightNode);
    if (rightNode->interCode != nullptr && rightNode->interCode->interCodeType == InterCodeType::READ) {
        auto *will_return = new InterCode(InterCodeType::READ);
        will_return->SingleElement = new Operand(OperandType::VARIABLE, leftVariName);
        exp->interCode = will_return;
        exp->intercodes.push_back(will_return);
        return will_return;
    } else if (rightNode->interCode != nullptr && rightNode->interCode->interCodeType == InterCodeType::CALL) {
        auto *will_return = new InterCode(InterCodeType::ASSIGN);
        auto *const will_return_leftVari = new Operand(OperandType::VARIABLE);
        will_return_leftVari->variName = leftVariName;
        auto *const will_return_rightVari = new Operand(OperandType::VARIABLE);
        will_return_rightVari->variName = rightExpLeftName;
        will_return->assign = {will_return_leftVari, will_return_rightVari};
        nodeInterCodeMerge(exp, {leftNode, rightNode});
        exp->intercodes.push_back(will_return);
        return will_return;
    }
    auto *will_return = new InterCode(InterCodeType::ASSIGN);
    auto *const will_return_leftVari = new Operand(OperandType::VARIABLE);
    will_return_leftVari->variName = leftVariName;
    auto *const will_return_rightVari = new Operand(OperandType::VARIABLE);
    will_return_rightVari->variName = rightExpLeftName;
    will_return->assign = {will_return_leftVari, will_return_rightVari};
    exp->interCode = will_return;
    nodeInterCodeMerge(exp, {leftNode, rightNode});
    exp->intercodes.push_back(will_return);
    return will_return;
}

InterCode *translate_varDecAssign(Node *const dec) {
    return translate_Exp_Assign_Exp(dec);
}

void translate_DecListMerge(Node *const decList) {
    nodeInterCodeMerge(decList, {decList->get_nodes(0), decList->get_nodes(2)});
}

// maybe include read
InterCode *translate_functionInvoke(Node *stmt) {
    Node *const subnodes[3]{stmt->get_nodes(0), stmt->get_nodes(1), stmt->get_nodes(2)};
    auto functionName = std::get<string>(subnodes[0]->value);
    auto *will_return = new InterCode();
    if (functionName == "read") {
        will_return->interCodeType = InterCodeType::READ;
        stmt->interCode = will_return;
        stmt->interCode->SingleElement = new Operand(OperandType::VARIABLE);
    } else {
        will_return->interCodeType = InterCodeType::CALL;
        stmt->interCode = will_return;
        stmt->interCode->assign = {
                new Operand(OperandType::VARIABLE, new_temp()),
                new Operand(OperandType::VARIABLE, functionName)};
        //        stmt->interCode->SingleElement = new Operand(OperandType::VARIABLE);
    };
    return will_return;
}

// maybe include write
InterCode *translate_functionWithParamInvoke(Node *stmt) {
    // 传进来的应该是 'exp'
    auto getNameFromArgNode = [](Node *node) {
        if (node->get_nodes(0)->interCode != nullptr) {
            return node->get_nodes(0)->interCode->assign.left->variName;
        } else {
            return std::get<string>(node->get_nodes(0, 0)->value);
        }
    };
    auto functionName = std::get<string>(stmt->get_nodes(0)->value);
    auto const paramName = getNameFromArgNode(stmt->get_nodes(2));
    auto *const will_return = new InterCode();
    if (functionName == "write") {
        will_return->interCodeType = InterCodeType::WRITE;
        will_return->SingleElement = new Operand(OperandType::VARIABLE, paramName);
        stmt->interCode = will_return;
        nodeInterCodeMerge(stmt, stmt->get_nodes(2));
        stmt->intercodes.push_back(will_return);
        return will_return;
    };
    auto *argExp = stmt->get_nodes(2);
    vector<InterCode *> tempIntercodes;
    do {
        auto argName = getNameFromArgNode(argExp);
        auto *const arg_InterCode = new InterCode(InterCodeType::ARG);
        arg_InterCode->SingleElement = new Operand(OperandType::VARIABLE);
        arg_InterCode->SingleElement->variName = argName;
        argExp->interCode = arg_InterCode;
        //arg_InterCode->print();
        nodeInterCodeMerge(stmt, argExp->get_nodes(0));
        tempIntercodes.push_back(arg_InterCode);
        if (argExp->nodes.size() == 1) {
            break;
        }
        argExp = argExp->get_nodes(2);
    } while (argExp != nullptr);
    std::for_each(tempIntercodes.crbegin(), tempIntercodes.crend(), [&stmt](InterCode *ic) {
        stmt->intercodes.push_back(ic);
    });
    will_return->interCodeType = InterCodeType::CALL;
    stmt->interCode = will_return;
    stmt->interCode->assign = {
            new Operand(OperandType::VARIABLE, new_temp()),
            new Operand(OperandType::VARIABLE, functionName)};
    stmt->intercodes.push_back(will_return);
    return will_return;
}

void translate_functionBodyDefine(Node *stmt, Node *Specifier_FunDec_Recv, Node *CompSt) {
    nodeInterCodeMerge(stmt, {Specifier_FunDec_Recv, CompSt});
}

void translate_CompstMerge(Node *CompSt, Node *DefList, Node *StmtList) {
    nodeInterCodeMerge(CompSt, {DefList, StmtList});
}

InterCode *translate_enterFunction(Node *const stmt) {
    auto functionName = std::get<string>(stmt->get_nodes(1, 0)->value);
    auto *const functionInterCode = new InterCode(InterCodeType::FUNCTION);
    functionInterCode->labelElement = new Operand(OperandType::JUMP_LABEL, functionName);
    stmt->interCode = functionInterCode;
    stmt->intercodes.push_back(functionInterCode);
    auto *const functionType = symbolTable[functionName];
    auto *list = std::get<FieldList *>(functionType->type);
    while (list != nullptr) {
        auto *const will_return = new InterCode(InterCodeType::PARAM);
        will_return->SingleElement = new Operand(OperandType::VARIABLE);
        will_return->SingleElement->variName = list->name;
        stmt->intercodes.push_back(will_return);
        list = list->next;
    }
    // TODO ,add Params
    return functionInterCode;
}

InterCode *translate_Return(Node *stmt) {
    auto returnName = getNameFromANode(stmt->get_nodes(1));
    auto *const will_return = new InterCode(InterCodeType::RETURN);
    will_return->SingleElement = new Operand(OperandType::VARIABLE, returnName);
    stmt->interCode = will_return;
    for (const auto &item : stmt->get_nodes(1)->intercodes) {
        stmt->intercodes.push_back(item);
    }
    stmt->intercodes.push_back(will_return);
    return nullptr;
}

void translate_StmtlistMerge(Node *StmtList) {
    nodeInterCodeMerge(StmtList, StmtList->nodes);
}

void translate_DeflistMerge(Node *StmtList) {
    nodeInterCodeMerge(StmtList, StmtList->nodes);
}

void translate_StmtMergeExp(Node *Stmt) {
    nodeInterCodeMerge(Stmt, {Stmt->nodes[0]});
}

void insertAJumpLabelToExpNode(Node *const exp, string labelName) {
    auto *const label1Intercode = new InterCode(InterCodeType::LABEL);
    label1Intercode->labelElement = new Operand(OperandType::JUMP_LABEL);
    label1Intercode->labelElement->jumpLabel = std::move(labelName);
    exp->intercodes.push_back(label1Intercode);
}

void insertAGotoLabelToExpNode(Node *const exp, string labelName) {
    auto *const gotoLabel3Intercode = new InterCode(InterCodeType::GOTO);
    gotoLabel3Intercode->labelElement = new Operand(OperandType::JUMP_LABEL);
    gotoLabel3Intercode->labelElement->jumpLabel = std::move(labelName);
    exp->intercodes.push_back(gotoLabel3Intercode);
}

void translate_if(Node *const stmt) {
    const auto newLabel1 = new_label();
    const auto newLabel2 = new_label();
    translate_Cond(stmt->get_nodes(2), newLabel1, newLabel2);
    nodeInterCodeMerge(stmt, stmt->get_nodes(2));
    insertAJumpLabelToExpNode(stmt, newLabel1);
    nodeInterCodeMerge(stmt, stmt->get_nodes(4));  // code2
    insertAJumpLabelToExpNode(stmt, newLabel2);
}

static const unordered_map<Node *, string> relopNameMap = [] {
    unordered_map<Node *, string> init{
            {Node::getSingleNameNodePointer("LT"), "<"},
            {Node::getSingleNameNodePointer("LE"), "<="},
            {Node::getSingleNameNodePointer("GT"), ">"},
            {Node::getSingleNameNodePointer("GE"), ">="},
            {Node::getSingleNameNodePointer("NE"), "!="},
            {Node::getSingleNameNodePointer("EQ"), "=="}};
    return init;
}();

void translate_Cond(Node *const stmt, string label_true, const string &label_false) {
    if (relopNameMap.count(stmt->get_nodes(1)) != 0) {
        translate_relop(stmt, std::move(label_true), label_false);
    } else if (stmt->get_nodes(1) == Node::getSingleNameNodePointer("OR")) {
        translate_exp_or_exp(stmt, label_true, label_false);
    }
}

void translate_ifelse(Node *const stmt) {
    const auto newLabel1 = new_label();
    const auto newLabel2 = new_label();
    const auto newLabel3 = new_label();
    translate_Cond(stmt->get_nodes(2), newLabel1, newLabel2);
    nodeInterCodeMerge(stmt, stmt->get_nodes(2));
    insertAJumpLabelToExpNode(stmt, newLabel1);
    nodeInterCodeMerge(stmt, stmt->get_nodes(4));  // code2
    insertAGotoLabelToExpNode(stmt, newLabel3);
    insertAJumpLabelToExpNode(stmt, newLabel2);
    nodeInterCodeMerge(stmt, stmt->get_nodes(6));
    insertAJumpLabelToExpNode(stmt, newLabel3);
}

void translate_while(Node *const stmt) {
    const auto newLabel1 = new_label();
    const auto newLabel2 = new_label();
    const auto newLabel3 = new_label();
    translate_Cond(stmt->get_nodes(2), newLabel2, newLabel3);
    insertAJumpLabelToExpNode(stmt, newLabel1);
    nodeInterCodeMerge(stmt, stmt->get_nodes(2));
    insertAJumpLabelToExpNode(stmt, newLabel2);
    nodeInterCodeMerge(stmt, stmt->get_nodes(4));  // code2
    insertAGotoLabelToExpNode(stmt, newLabel1);
    insertAJumpLabelToExpNode(stmt, newLabel3);
}

InterCode *translate_minus_exp(Node *const exp) {
    auto *const minud_exp = exp->get_nodes(1);
    const auto minud_exp_name = getNameFromANode(minud_exp);
    const auto newTempName = new_temp();
    auto *const will_return = new InterCode(InterCodeType::SUB);
    will_return->bioOp = {
            new Operand(OperandType::VARIABLE, newTempName),
            new Operand(OperandType::CONSTANT, 0),
            new Operand(OperandType::VARIABLE, minud_exp_name)};
    exp->interCode = will_return;
    nodeInterCodeMerge(exp, exp->get_nodes(1));
    exp->intercodes.push_back(will_return);
    return will_return;
}

InterCode *translate_exp_or_exp(Node *const exp, const string &label_true, const string &label_false) {
    Node *const expSubs[3]{exp->get_nodes(0), exp->get_nodes(1), exp->get_nodes(2)};
    const auto newLabel1 = new_label();
    translate_Cond(expSubs[0], label_true, newLabel1);
    nodeInterCodeMerge(exp, expSubs[0]);
    {
        auto *const label1InterCode = new InterCode(InterCodeType::LABEL);
        label1InterCode->labelElement = new Operand(OperandType::JUMP_LABEL);
        label1InterCode->labelElement->jumpLabel = newLabel1;
        exp->intercodes.push_back(label1InterCode);
    }
    translate_Cond(expSubs[2], label_true, label_false);
    nodeInterCodeMerge(exp, expSubs[2]);
    return nullptr;
}

InterCode *translate_relop(Node *const exp, string label_true, string label_false) {
    Node *const expSubs[3]{exp->get_nodes(0), exp->get_nodes(1), exp->get_nodes(2)};
    const auto tempName1 = getNameFromANode(expSubs[0]);
    const auto opName = relopNameMap.at(expSubs[1]);
    //const auto op = BioOpNodes.at(expSubs[1]);
    const auto tempName2 = getNameFromANode(expSubs[2]);
    auto *const will_return = new InterCode(InterCodeType::IF_ELSE);
    //nodeInterCodeMerge(exp,expSubs[2]);
    will_return->ifElse = {
            new Operand(OperandType::VARIABLE, tempName1),
            new Operand(OperandType::VARIABLE, opName),
            new Operand(OperandType::VARIABLE, tempName2),
            new Operand(OperandType::JUMP_LABEL, std::move(label_true))};
    exp->interCode = will_return;
    nodeInterCodeMerge(exp, {expSubs[0], expSubs[2]});
    exp->intercodes.push_back(will_return);
    auto *const elsePart = new InterCode(InterCodeType::GOTO);
    elsePart->labelElement = new Operand(OperandType::JUMP_LABEL);
    elsePart->labelElement->jumpLabel = std::move(label_false);
    exp->intercodes.push_back(elsePart);
    return will_return;
}