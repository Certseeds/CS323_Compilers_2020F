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
    this->vari_names.push_back(str);
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

void mipsAsm::add_intercodes(vector<InterCode *> ircodes) {
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
const auto load_vari_to_register = [](int32_t order, Operand *operand) {
    switch (operand->operandEnum) {
        case OperandType::VARIABLE: {
            return string("lw   $t").append(std::to_string(order)).append(",_").append(operand->variName);
        }
        case OperandType::CONSTANT: {
            if (operand->value == 0) {
                return string("move $t").append(std::to_string(order)).append(",$zero");
            }
        }
    }
};

void mipsAsm::output_intercodes() {
    for (const auto &ircodes: ircodes_vec) {
        for (const auto &ircode: ircodes) {
            switch (ircode->interCodeType) {
                case InterCodeType::LABEL:
                case InterCodeType::FUNCTION: {
                    printf("%s:\n", ircode->labelElement->jumpLabel.c_str());
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
                    printf("    %s\n", load_vari_to_register(0, ircode->SingleElement).c_str());
                    static const string return_sentenct = R"(move $v0,$t0
    jr $ra)";
                    printf("    %s\n\n", return_sentenct.c_str());
                    break;
                }
                case InterCodeType::WRITE: {
                    static constexpr const char *const write_begin =
                            R"(    addi $sp, $sp, -8 ### push stack to store $ra
    sw   $a0,  0($sp) ## store $a0
    sw   $ra,  4($sp) ### store $ra)";
                    static constexpr const char *const write_end =
                            R"(    move $a0,  $t0
    jal  write ### invoke write
    lw   $ra,  4($sp) ## read $ra
    lw   $a0,  0($sp) ## store $a0
    addi $sp, $sp, 8)";
                    printf("%s\n", write_begin);
                    printf("    lw   $t0,%s\n", ircode->SingleElement->get_asm_str().c_str());
                    printf("%s\n\n", write_end);
                    break;
                }
                case InterCodeType::READ: {
                    static constexpr const char *const read_begin =
                            R"(    addi $sp, $sp, -8 ### push stack to store $ra
    sw   $a0,  0($sp) ## store $a0
    sw   $ra,  4($sp) ### store $ra
    jal  read ### invoke read
    lw   $a0,  0($sp) ## store $a0
    lw   $ra,  4($sp) ## read $ra
    addi $sp, $sp, 8
    move $t0,$v0)";
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
                }
            }
        }
    }
}
