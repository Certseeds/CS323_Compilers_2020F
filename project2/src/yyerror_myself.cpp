//
// Created by nanos on 2020/10/7.
//

#include "yyerror_myself.hpp"

#define PARSER_error_OUTPUT stdout

void yyerror_myself(YYERROR_TYPE type) {
    static const std::unordered_map<YYERROR_TYPE, std::string> yyerror_map = {
            {YYERROR_TYPE::LACK_OF_RC, R"(closing curly braces  })"},
            {YYERROR_TYPE::LACK_OF_RB, R"(closing bracket ])"},
            {YYERROR_TYPE::LACK_OF_RP, R"(closing parenthesis ))"},
            {YYERROR_TYPE::LACK_OF_LC, R"(left curly braces  {)"},
            {YYERROR_TYPE::LACK_OF_LB, R"(left bracket [)"},
            {YYERROR_TYPE::LACK_OF_LP, R"(left parenthesis ()"},
            {YYERROR_TYPE::MISS_SPEC,  R"(specifier)"},
            {YYERROR_TYPE::MISS_SEMI,  R"(semicolon ;)"},
            {YYERROR_TYPE::MISS_COMMA, R"(COMMA ,)"},
    };
    fprintf(PARSER_error_OUTPUT, "Missing %s\n", yyerror_map.at(type).c_str());
}