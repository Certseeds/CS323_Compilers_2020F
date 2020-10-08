/*
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-10-07 22:38:55
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-10-08 14:43:48
 */
//
// Created by nanos on 2020/10/7.
//

#include "syntax.tab.c"
int main(int argc,char** argv){
    // root_node->name="123";
    // root_node->linenum=123;
    // root_node->nodes_num=0;
    // root_node->print=&print_line;
    // root_node->print(0,root_node);
    //
    if(argc <= 1){
        fprintf(PARSER_error_OUTPUT,"no input path");
        return 1;
    }
    else if(argc > 2){
        fprintf(PARSER_error_OUTPUT,"too much input path");
        return 1;
    }
    else{
        FILE *f = fopen(argv[1],"r");
        if(!f){
            fprintf(PARSER_error_OUTPUT,"error of path %s",argv[1]);
            return 1;
        }
        yyrestart(f);
        yyparse();
    }
    if(isError == 0){
        root_node->print(0);
    }
    return 0;
}