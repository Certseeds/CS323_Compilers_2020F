//
// Created by nanos on 2020/12/20.
//

#include <iostream>
#include <unordered_map>
#include "interCode.hpp"

using std::cout;
using std::string;
using std::unordered_map;


Operand::Operand(OperandType operandEnum) : operandEnum(operandEnum), variName("") {}

void Operand::print() const {
    switch (this->operandEnum) {
        case OperandType::VARIABLE: {
            std::cout << this->variName;
            break;
        }
        case OperandType::CONSTANT: {
            std::cout << '#' << this->value;
            break;
        }
        case OperandType::JUMP_LABEL: {
            std::cout << this->variName;
        }
        default: {
            break;
        }
    }
}

Operand::Operand(OperandType operandEnum, std::string variName) : operandEnum(operandEnum),
                                                                  variName(std::move(variName)) {}

Operand::Operand(OperandType operandEnum, int32_t value) : operandEnum(operandEnum), value(value) {}


InterCode::InterCode(InterCodeType interCodeType) : interCodeType(interCodeType) {}

static const unordered_map<InterCodeType, string> BioOpNodes = [] {
    static const unordered_map<InterCodeType, string> init{
            {InterCodeType::ADD, " + "},
            {InterCodeType::SUB, " - "},
            {InterCodeType::MUL, " * "},
            {InterCodeType::DIV, " / "},
    };
    return init;
}();
static const unordered_map<InterCodeType, string> singleElementWords = [] {
    static const unordered_map<InterCodeType, string> init{
            {InterCodeType::RETURN,   "RETURN"},
            {InterCodeType::WRITE,    "WRITE"},
            {InterCodeType::PARAM,    "PARAM"},
            {InterCodeType::FUNCTION, "FUNCTION"},
            {InterCodeType::ARG,      "ARG"},
            {InterCodeType::READ,     "READ"},
            {InterCodeType::LABEL,    "LABEL"},
            {InterCodeType::GOTO,     "GOTO"},
    };
    return init;
}();

void InterCode::print() const {
    switch (this->interCodeType) {
        case InterCodeType::ASSIGN: {
            this->assign.left->print();
            std::cout << " := ";
            this->assign.right->print();
            break;
        }
        case InterCodeType::CALL: {
            this->assign.left->print();
            std::cout << " := CALL ";
            this->assign.right->print();
            break;
        }
        case InterCodeType::ADD:
        case InterCodeType::SUB:
        case InterCodeType::MUL:
        case InterCodeType::DIV: {
            this->bioOp.result->print();
            std::cout << " := ";
            this->bioOp.op1->print();
            std::cout << BioOpNodes.at(this->interCodeType);
            this->bioOp.op2->print();
            break;
        }
        case InterCodeType::LABEL:
        case InterCodeType::FUNCTION: {
            std::cout << singleElementWords.at(this->interCodeType) << ' ';
            this->SingleElement->print();
            std::cout << " :";
            break;
        }
        case InterCodeType::GOTO:
        case InterCodeType::READ:
        case InterCodeType::PARAM:
        case InterCodeType::RETURN:
        case InterCodeType::ARG:
        case InterCodeType::WRITE: {
            std::cout << singleElementWords.at(this->interCodeType) << ' ';
            this->SingleElement->print();
            break;
        }
        case InterCodeType::IF_ELSE: {
            std::cout << "IF ";
            this->ifElse.left->print();
            std::cout << ' ';
            this->ifElse.operation->print();
            std::cout << ' ';
            this->ifElse.right->print();
            std::cout << " GOTO ";
            this->ifElse.if_label->print();
        }
        default: {
            break;
        }
    }
    std::cout << '\n';
}
