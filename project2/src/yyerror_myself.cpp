//
// Created by nanos on 2020/10/7.
//

#include "yyerror_myself.hpp"

#define PARSER_error_OUTPUT stdout

void yyerror_myself(enum YYERROR_TYPE type) {
    std::string msg;
    switch (type) {
        case YYERROR_TYPE::LACK_OF_RC: {
            msg = "Missing closing curly braces  \'}\'";
            break;
        }
        case YYERROR_TYPE::LACK_OF_RB: {
            msg = "Missing closing bracket \']\'";
            break;
        }
        case YYERROR_TYPE::LACK_OF_RP: {
            msg = "Missing closing parenthesis \')\'";
            break;
        }
        case YYERROR_TYPE::LACK_OF_LC: {
            msg = "Missing left curly braces  \'{\'";
            break;
        }
        case YYERROR_TYPE::LACK_OF_LB: {
            msg = "Missing left bracket \'[\'";
            break;
        }
        case YYERROR_TYPE::LACK_OF_LP: {
            msg = "Missing left parenthesis \'(\'";
            break;
        }
        case YYERROR_TYPE::MISS_SPEC: {
            msg = "Missing specifier";
            break;
        }
        case YYERROR_TYPE::MISS_SEMI: {
            msg = "Missing semicolon \';\'";
            break;
        }
        case YYERROR_TYPE::MISS_COMMA: {
            msg = "Missing COMMA \',\'";
        }
    }
    fprintf(PARSER_error_OUTPUT, "%s\n", msg.c_str());
}