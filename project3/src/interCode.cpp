//
// Created by nanos on 2020/12/20.
//

#include "interCode.hpp"
#include <iostream>
#include <unordered_map>

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
    static unordered_map<InterCodeType, string> init;
    init.insert(std::make_pair(InterCodeType::ADD, " + "));
    init.insert(std::make_pair(InterCodeType::SUB, " - "));
    init.insert(std::make_pair(InterCodeType::MUL, " * "));
    init.insert(std::make_pair(InterCodeType::DIV, " / "));
    return init;
}();
static const unordered_map<InterCodeType, string> singleElementWords = [] {
    static unordered_map<InterCodeType, string> init;
    init.insert(std::make_pair(InterCodeType::RETURN, "RETURN"));
    init.insert(std::make_pair(InterCodeType::WRITE, "WRITE"));
    init.insert(std::make_pair(InterCodeType::PARAM, "PARAM"));
    init.insert(std::make_pair(InterCodeType::FUNCTION, "FUNCTION"));
    init.insert(std::make_pair(InterCodeType::ARG, "ARG"));
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
        case InterCodeType::READ: {
            std::cout << "READ ";
            this->SingleElement->print();
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
        case InterCodeType::FUNCTION: {
            std::cout << singleElementWords.at(this->interCodeType) << ' ';
            this->SingleElement->print();
            std::cout << " :";
            break;
        }
        case InterCodeType::PARAM:
        case InterCodeType::RETURN:
        case InterCodeType::ARG:
        case InterCodeType::WRITE: {
            std::cout << singleElementWords.at(this->interCodeType) << ' ';
            this->SingleElement->print();
            break;
        }
        default: {
            break;
        }
    }
    std::cout << '\n';
}
