/*
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2021-01-20 15:35:30
 * @LastEditors: nanoseeds
 * @LastEditTime: 2021-01-29 14:19:43
 */

#include "mipsAsm.hpp"
#include "type.hpp"
#include "translate2.hpp"
#include <unordered_map>
#include <iostream>
#include "mipsAsmStrs.hpp"

using std::unordered_map;

using std::cout;
using std::cin;
extern unordered_map<string, Type *> symbolTable;
inline static const string pre_build_data =

#include "prebuildData.asm"

inline static const string pre_build_func =

#include "prebuildFunc.asm"

void mipsAsm::outputDataAndText() {
    std::cout << pre_build_data << std::endl;
    for (const auto &vari_name : this->vari_names) {
        printf("_%s: .word 0\n", vari_name.c_str());
    }
    std::cout << pre_build_func << std::endl;
}

void mipsAsm::insert_vari(const std::string &str) {
    this->vari_names.insert(str);
}

void mipsAsm::scan_symbolTable() {
    for (const auto&[key, value]: symbolTable) {
        if (value->category == CATEGORY::PRIMITIVE &&
            value->type.index() == 0 &&
            std::get<Node_TYPE>(value->type) == Node_TYPE::INT) {
            this->insert_vari(key);
        }
    }
    const auto[temp_num, _] = new_temp_with_order();
    for (auto i = 0; i < temp_num - 1; ++i) {
        this->insert_vari(string("t").append(std::to_string(i)));
    }
}

static vector<vector<InterCode *>> ircodes_vec;

void mipsAsm::add_intercodes(const vector<InterCode *> &ircodes) {
    ircodes_vec.push_back(ircodes);
}

static const unordered_map<InterCodeType, string> BioOpNodes = [] {
    static const unordered_map<InterCodeType, string> init{
            {InterCodeType::ADD, "add"},
            {InterCodeType::SUB, "sub"},
            {InterCodeType::MUL, "mul"},
    };
    return init;
}();

void mipsAsm::output_intercodes() {
    for (const auto &ircodes: ircodes_vec) {
        unordered_map<string, int32_t> param_to_reg{};
        const auto load_vari_to_register = [&param_to_reg](int32_t order, Operand *operand) {
            switch (operand->operandEnum) {
                case OperandType::VARIABLE: {
                    if (param_to_reg.count(operand->variName) == 0) {
                        return string("lw   $t").append(std::to_string(order)).append(",_").append(operand->variName);
                    } else {
                        return string("move $t").append(std::to_string(order)).append(",$a")
                                .append(std::to_string(param_to_reg.at(operand->variName)));
                    }
                }
                case OperandType::CONSTANT: {
                    if (operand->value == 0) {
                        return string("move $t").append(std::to_string(order)).append(",$zero");
                    }
                }
                default: {
                    return string("Error");
                }
            }
        };
        int order_of_a_regs = 0;
        vector<string> args;
        for (const auto &ircode: ircodes) {
            switch (ircode->interCodeType) {
                case InterCodeType::PARAM: {
                    this->insert_vari(ircode->SingleElement->variName);
                    if (param_to_reg.count(ircode->SingleElement->variName) == 0) {
                        param_to_reg[ircode->SingleElement->variName] = order_of_a_regs++;
                    }
                    break;
                }
                case InterCodeType::LABEL: {
                    printf("%s:\n", ircode->labelElement->jumpLabel.c_str());
                    break;
                }
                case InterCodeType::FUNCTION: {
                    printf("%s:\n", ircode->labelElement->jumpLabel.c_str());
                    printf("%s\n\n", function_begin);
                    break;
                }
                case InterCodeType::ASSIGN: {
                    switch (ircode->assign.right->operandEnum) {
                        case OperandType::CONSTANT : {
                            printf("    li   $t0,%s\n", ircode->assign.right->get_asm_str().c_str());
                            break;
                        }
                        case OperandType::VARIABLE: {
                            printf("    lw   $t0,%s\n", ircode->assign.right->get_asm_str().c_str());
                            break;
                        }
                        default: {
                            break;
                        }
                    }
                    printf("    sw   $t0,%s\n\n", ircode->assign.left->get_asm_str().c_str());
                    break;
                }
                case InterCodeType::ADD:
                case InterCodeType::MUL:
                case InterCodeType::SUB: {
                    const string &bioOp_name = BioOpNodes.at(ircode->interCodeType);
                    printf("    %s\n", load_vari_to_register(0, ircode->bioOp.op1).c_str());
                    printf("    %s\n", load_vari_to_register(1, ircode->bioOp.op2).c_str());
                    printf("    %s  $t2,$t0,$t1\n", bioOp_name.c_str());
                    printf("    sw   $t2,%s\n\n", ircode->bioOp.result->get_asm_str().c_str());
                    break;
                }
                case InterCodeType::RETURN: {
                    printf("%s\n", function_end);
                    printf("    %s\n", load_vari_to_register(0, ircode->SingleElement).c_str());
                    static const string return_sentenct = R"(move $v0,$t0
    jr $ra)";
                    printf("    %s\n\n", return_sentenct.c_str());
                    break;
                }
                case InterCodeType::WRITE: {
                    printf("%s\n", write_begin);
                    printf("    lw   $t0,%s\n", ircode->SingleElement->get_asm_str().c_str());
                    printf("%s\n\n", write_end);
                    break;
                }
                case InterCodeType::READ: {
                    printf("%s\n", read_begin);
                    printf("    sw   $t0,%s\n\n", ircode->SingleElement->get_asm_str().c_str());
                    break;
                }
                case InterCodeType::GOTO: {
                    printf("    j %s\n\n", ircode->labelElement->jumpLabel.c_str());
                    break;
                }
                case InterCodeType::IF_ELSE: {
                    printf("    %s\n", load_vari_to_register(0, ircode->ifElse.left).c_str());
                    printf("    %s\n", load_vari_to_register(1, ircode->ifElse.right).c_str());
                    static const unordered_map<string, string> operandtoStr{
                            {"<",  "blt"},
                            {"<=", "ble"},
                            {">",  "bgt"},
                            {">=", "bge"},
                            {"!=", "bne"},
                            {"==", "beq"}
                    };
                    printf("    %s  $t0,$t1,%s\n\n",
                           operandtoStr.at(ircode->ifElse.operation->variName).c_str(),
                           ircode->ifElse.if_label->variName.c_str()
                    );
                    break;
                }
                case InterCodeType::CALL: {
                    const auto call_sentences = caller(this->vari_names, args, param_to_reg);
                    printf("%s", call_sentences.first.c_str());
                    args.clear();
                    printf("    jal %s\n", ircode->assign.right->variName.c_str());
                    printf("%s", call_sentences.second.c_str());
                    printf("    sw $v0,_%s\n\n", ircode->assign.left->variName.c_str());
                    break;
                }
                case InterCodeType::ARG: {
                    args.push_back(ircode->SingleElement->variName);
                    break;
                }
                default: {
                    break;
                }
            }
        }
    }
}
