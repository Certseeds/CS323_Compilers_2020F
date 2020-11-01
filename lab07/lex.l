%{
    #include "syntax.tab.h"
    // illgeal_int 0+[1-9][0-9]*
%}
%option noyywrap

unic u[0-9a-fA-F]{4}
esc \\([\"\\/bfnrt]|{unic})
scp [^"\\\x00-\x1f]
string \"({esc}|{scp})*\"

int 0|[1-9][0-9]*
frac \.[0-9]+
exp [Ee][+-]?[0-9]+
number -?{int}{frac}?{exp}?

empty [ \n\r\t]

%%

"{" { return LC; }
"}" { return RC; }
"[" { return LB; }
"]" { return RB; }
":" { return COLON; }
"," { return COMMA; }

"true" { 
    yylval.jsonobject = new JsonObject(true);
    //yylval.jsonobject = nullptr;
    return TRUE; 
}
"false" {
    yylval.jsonobject = new JsonObject(false); 
    return FALSE; 
}
"null" {
    yylval.jsonobject = new JsonObject(static_cast<void*>(nullptr));
    return VNULL; 
}

{string} {
    yylval.jsonobject = new JsonObject(std::string(yytext).substr(1,yyleng-2));
    //std::cout << std::get<std::string>(yylval.jsonobject->value) << std::endl;
    return STRING;
}
{number} {
    yylval.jsonobject = new JsonObject(static_cast<double>(atof(yytext)));
    //std::cout << std::get<double>(yylval.jsonobject->value) << std::endl;
    return NUMBER; 
    }
{empty} {}

. { printf("lexical error: %s\n", yytext); }
