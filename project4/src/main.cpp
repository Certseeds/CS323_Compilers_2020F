/*
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-10-07 22:38:55
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-10-11 11:47:46
 */
#include "syntax.tab.c"

extern mipsAsm mips_asm;

int main(int argc, char **argv) {
    if (argc <= 1) {
        fprintf(PARSER_error_OUTPUT, "no input path");
        return 1;
    } else if (argc > 2) {
        fprintf(PARSER_error_OUTPUT, "too much input path");
        return 1;
    } else {
        FILE *f = fopen(argv[1], "r");
        if (!f) {
            fprintf(PARSER_error_OUTPUT, "error of path %s", argv[1]);
            return 1;
        }
        yyrestart(f);
        yyparse();
    }
    if (isError == 0) {
        //root_node->print(0);
        //std::cout << symbolTable.size() << std::endl;
    }
    mips_asm.scan_symbolTable();
    mips_asm.outputDataAndText();
    mips_asm.output_intercodes();
    return 0;
}