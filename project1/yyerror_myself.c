//
// Created by nanos on 2020/10/7.
//

#include "yyerror_myself.h"

#define PARSER_error_OUTPUT stdout

void yyerror_myself(enum YYERROR_TYPE type) {
    const char *msg = NULL;
    switch (type) {
        case LACK_OF_RC: {
            msg="Missing closing curly braces  \'}\'";
            break;
        }
        case LACK_OF_RB: {
            msg="Missing closing bracket \']\'";
            break;
        }
        case LACK_OF_RP: {
            msg = "Missing closing parenthesis \')\'";
            break;
        }
        case LACK_OF_LC: {
            msg="Missing left curly braces  \'{\'";
            break;
        }
        case LACK_OF_LB: {
            msg="Missing left bracket \'[\'";
            break;
        }
        case LACK_OF_LP: {
            msg = "Missing left parenthesis \'(\'";
            break;
        }
        case MISS_SPEC:{
            msg="Missing specifier";
            break;
        }
        case MISS_SEMI:{
            msg = "Missing semicolon \';\'";
            break;
        }
        case MISS_COMMA:{
            msg = "Missing COMMA \',\'";
        }
    }
    fprintf(PARSER_error_OUTPUT, "%s\n", msg);
}