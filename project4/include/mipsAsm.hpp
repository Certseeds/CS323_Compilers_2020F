//
// Created by nanos on 2021/1/20.
//

#ifndef CS323_COMPLIERS_PROJECT4_INCLUDE_MIPSASM_HPP
#define CS323_COMPLIERS_PROJECT4_INCLUDE_MIPSASM_HPP

#include "interCode.hpp"
#include <string>
#include <vector>

using std::string;
using std::vector;

class mipsAsm {
public:
    void outputDataAndText();

    void scan_symbolTable();

    void add_intercodes(vector<InterCode *> ircodes);

    void output_intercodes();

private:
    std::vector<std::string> vari_names;

    void insert_vari(const std::string &str);
};


#endif //CS323_COMPLIERS_PROJECT4_INCLUDE_MIPSASM_HPP
