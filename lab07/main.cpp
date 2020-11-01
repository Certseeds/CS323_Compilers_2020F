/*
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-10-30 10:50:47
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-10-30 22:24:54
 */
#include <iostream>

#include "Object.hpp"

using std::cout;

int yyparse(void);

extern FILE *yyin;
extern JsonObject *RootObject;

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_path>" << '\n';
        std::cerr << "Output will be the struct and value of the json Object\n";
        return -1;
    } else if (!(yyin = fopen(argv[1], "r"))) {
        perror(argv[1]);
        return -1;
    }
    yyparse();
    RootObject->printInside();
    return 0;
}