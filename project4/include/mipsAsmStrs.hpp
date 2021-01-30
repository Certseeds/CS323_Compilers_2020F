//
// Created by nanos on 2021/1/30.
//

static constexpr const auto write_begin =
        R"(    addi $sp, $sp, -8 ### push stack to store $ra
    sw   $a0,  0($sp) ## store $a0
    sw   $ra,  4($sp) ### store $ra)";
static constexpr const auto write_end =
        R"(    move $a0,  $t0
    jal  write ### invoke write
    lw   $ra,  4($sp) ## read $ra
    lw   $a0,  0($sp) ## store $a0
    addi $sp, $sp, 8)";
static constexpr const auto read_begin =
        R"(    addi $sp, $sp, -8 ### push stack to store $ra
    sw   $a0,  0($sp) ## store $a0
    sw   $ra,  4($sp) ### store $ra
    jal  read ### invoke read
    lw   $a0,  0($sp) ## store $a0
    lw   $ra,  4($sp) ## read $ra
    addi $sp, $sp, 8
    move $t0,$v0)";
static constexpr const auto function_begin =
        R"(    addi $sp,$sp,-32
    sw $s0,0($sp)
    sw $s1,4($sp)
    sw $s2,8($sp)
    sw $s3,12($sp)
    sw $s4,16($sp)
    sw $s5,20($sp)
    sw $s6,24($sp)
    sw $s7,28($sp))";
static constexpr const auto function_end =
        R"(    lw $s7,28($sp)
    lw $s6,24($sp)
    lw $s5,20($sp)
    lw $s4,16($sp)
    lw $s3,12($sp)
    lw $s2,8($sp)
    lw $s1,4($sp)
    lw $s0,0($sp)
    addi $sp,$sp,32)";
const auto caller = [](unordered_set<string> setOfVaris, vector<string> args,
                       std::unordered_map<string, int32_t> param_to_reg) {
    vector<string> begin_strs;
    vector<string> end_strs;
    std::unordered_map<string, int> varitoInt{param_to_reg};
    begin_strs.push_back(string("    addi $sp, $sp, -").append(std::to_string((4 + setOfVaris.size() + 1) * 4)));
    begin_strs.push_back(R"(    sw $a0,  0($sp) ## store $a0)");
    begin_strs.push_back(R"(    sw $a1,  4($sp) ## store $a1)");
    begin_strs.push_back(R"(    sw $a2,  8($sp) ## store $a2)");
    begin_strs.push_back(R"(    sw $a3,  12($sp) ## store $a3)");
    end_strs.push_back(R"(    lw $a0,  0($sp) ## store $a0)");
    end_strs.push_back(R"(    lw $a1,  4($sp) ## store $a1)");
    end_strs.push_back(R"(    lw $a2,  8($sp) ## store $a2)");
    end_strs.push_back(R"(    lw $a3,  12($sp) ## store $a3)");
    int order = 4;
    for (const auto &item :setOfVaris) {
        begin_strs.push_back(string("    lw $t0,_").append(item));
        begin_strs.push_back(string("    sw $t0, ").append(std::to_string((order++) * 4).append("($sp)")));
        end_strs.push_back(string("    lw $t0,").append(std::to_string((order - 1) * 4).append("($sp)")));
        end_strs.push_back(string("    sw $t0,_").append(item));
        if (varitoInt.count(item) == 0) {
            varitoInt[item] = order - 1;
        }
    }
    begin_strs.push_back(string("    sw $ra, ").append(std::to_string((order++) * 4).append("($sp)")));
    end_strs.push_back(string("    lw $ra, ").append(std::to_string((order - 1) * 4).append("($sp)")));
    end_strs.push_back(string("    addi $sp, $sp, ").append(std::to_string((4 + setOfVaris.size() + 1) * 4)));
    for (auto i = 0u; i < args.size(); i++) {
        begin_strs.push_back(string("    lw $a")
                                     .append(std::to_string(args.size() - 1 - i)).append(",")
                                     .append(std::to_string(varitoInt[args[i]] * 4)).append("($sp)"));
    }
    std::string will_return_begin;
    std::string will_return_end;
    for (const auto &str : begin_strs) {
        will_return_begin += str + '\n';
    }
    for (const auto &str: end_strs) {
        will_return_end += str + '\n';
    }
    return std::pair{will_return_begin, will_return_end};
};