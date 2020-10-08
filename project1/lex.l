%{
    #include "node.h"
    int isError = 0;
    #define LEXER_ERROR_OUTPUT stdout
%}
%{
    #include"syntax.tab.h"
    /* library inclusions */ 
    int yycolumn = 1;
    #define YY_USER_ACTION \
        yylloc.first_line = yylineno; \
        yylloc.last_line = yylineno; \
        yylloc.first_column = yycolumn; \
        yylloc.last_column = yycolumn + yyleng;\
        yycolumn += yyleng;
    //INT32_10 [+-]?(0|([1-9]{digit}*))
    /*
    it seems that in bison and flex,
    the YYLTYPE's definition is different
    one is a struct and another look like the before one's pointer
    */
    //UFLOAT32 {digit}+(.{digit}+)?([Ee][+-]?{digit}+)?
    //%option c++
%}
%option noyywrap
%option yylineno
letters [A-Za-z]
letters_ [A-Za-z_]
digit [0-9]
digit_16 [0-9a-fA-F]
UINT32_10 (0|([1-9]{digit}*))
UINT32_16 0[xX](0|[1-9a-fA-F]{digit_16}*)
UINT32_16_error_more_0 0[xX](0{2,}{digit_16}*)
UINT32_16_error_illgeal_char 0[xX]([1-9a-fA-F]{digit_16}*[g-z]{digit_16}*)
UINT32 {UINT32_10}|{UINT32_16}
UFLOAT32 {digit}+\.{digit}+
ID {letters_}({letters_}|{digit}){0,31}
CHAR '.'
CHAR_16 '\\x(0|[1-9a-fA-F]{digit_16})'
CHAR_16_more0 '\\x00{digit_16}*'
CHAR_16_illgeal_char '\\x([1-9a-fA-F]){digit_16}*[g-z]{digit_16}*'
CHAR_16_toolong '\\x{digit_16}{3,}'
%%
"//" {
    char c = input();
    while(c!='\n'){c=input();}
}
"\n" {yycolumn = 1;}
[ \t\r]+ {}
"int" {
    yylval.Node_value = new_node_key("TYPE");
    yylval.Node_value->string_value = "int\0";
    yylval.Node_value->print=&print_str_value;
    return TYPE;
}
"float" {
    yylval.Node_value = new_node_key("TYPE");
    yylval.Node_value->string_value = "float\0";
    yylval.Node_value->print=&print_str_value;
    return TYPE;
}
"char" {
    yylval.Node_value = new_node_key("TYPE");
    yylval.Node_value->string_value = "char\0";
    yylval.Node_value->print=&print_str_value;
    return TYPE;
}
"struct" {yylval.Node_value = new_node_key("STRUCT");return STRUCT;}
"if" {yylval.Node_value = new_node_key("IF");return IF;}
"else" {yylval.Node_value = new_node_key("ELSE");return ELSE;}
"while" {yylval.Node_value = new_node_key("WHILE");return WHILE;}
"return" {yylval.Node_value = new_node_key("RETURN");return RETURN;}
"." {yylval.Node_value = new_node_key("DOT");return DOT;}
";" {yylval.Node_value = new_node_key("SEMI");return SEMI;}
"," {yylval.Node_value = new_node_key("COMMA");return COMMA;}
"=" {yylval.Node_value = new_node_key("ASSIGN");return ASSIGN;}
"<" {yylval.Node_value = new_node_key("LT");return LT;}
"<=" {yylval.Node_value = new_node_key("LE");return LE;}
">" {yylval.Node_value = new_node_key("GT");return GT;}
">=" {yylval.Node_value = new_node_key("GE");return GE;}
"!=" {yylval.Node_value = new_node_key("NE");return NE;}
"==" {yylval.Node_value = new_node_key("EQ");return EQ;}
"+" {yylval.Node_value = new_node_key("PLUS");return PLUS;}
"-" {yylval.Node_value = new_node_key("MINUS");return MINUS;}
"*" {yylval.Node_value = new_node_key("MUL");return MUL;}
"/" {yylval.Node_value = new_node_key("DIV");return DIV;}
"&&" {yylval.Node_value = new_node_key("AND");return AND;}
"||" {yylval.Node_value = new_node_key("OR");return OR;}
"!" {yylval.Node_value = new_node_key("NOT");return NOT;}
"(" {yylval.Node_value = new_node_key("LP");return LP;}
")" {yylval.Node_value = new_node_key("RP");return RP;}
"[" {yylval.Node_value = new_node_key("LB");return LB;}
"]" {yylval.Node_value = new_node_key("RB");return RB;}
"{" {yylval.Node_value = new_node_key("LC");return LC;}
"}" {yylval.Node_value = new_node_key("RC");return RC;}
{ID} {
    yylval.Node_value = new_node_key("ID");
    yylval.Node_value->string_value = (char*)malloc(sizeof(char)*(yyleng+1));
    memcpy(yylval.Node_value->string_value,yytext,sizeof(char)*yyleng);
    yylval.Node_value->string_value[yyleng]='\0';
    yylval.Node_value->print=&print_str_value;
    // DONE
    //printf("ID %s %d\n",yytext,yyleng);
    return ID;
}
{UFLOAT32} {
    yylval.Node_value = new_node_key("FLOAT");
    yylval.Node_value->float_value=atof(yytext);
    yylval.Node_value->print=&print_float_value;
    return FLOAT;
}
{UINT32_10} {
    yylval.Node_value = new_node_key("INT");
    yylval.Node_value->int_value=atoi(yytext);
    yylval.Node_value->print=&print_int_value;
    return INT;
}
{UINT32_16} {
    yylval.Node_value = new_node_key("INT");
    yylval.Node_value->int_value=(int)strtol(yytext,NULL,0);
    yylval.Node_value->print=&print_int_value;
    return INT;
}
{UINT32_16_error_more_0} {
    isError=1;
    fprintf(LEXER_ERROR_OUTPUT, "Error type A at Line %s: Illgeal UINT32 hex-Leading 0 \n", yytext);
    return ILLEGAL_TOKEN;
}
{UINT32_16_error_illgeal_char} {
    isError=1;
    fprintf(LEXER_ERROR_OUTPUT, "Error type A at Line %s: UINT32_16_error_illgeal_char \n", yytext);
    return ILLEGAL_TOKEN;
}
{CHAR} {
    yylval.Node_value = new_node_key("CHAR");
    yylval.Node_value->char_value = yytext[1];
    yylval.Node_value->print=&print_char_value;
    return CHAR;
}
{CHAR_16} {
    yytext[1]='0';
    yytext[yyleng-1]='\0';
    yylval.Node_value = new_node_key("CHAR");
    yylval.Node_value->string_value = (char*)malloc(sizeof(char)*(yyleng));
    memcpy(yylval.Node_value->string_value,yytext+sizeof(char),sizeof(char)*(yyleng-1));
    yylval.Node_value->string_value[0]='\\';
    yylval.Node_value->string_value[yyleng-1]='\0';
    yylval.Node_value->print=&print_str_value;
    return CHAR;
}
{CHAR_16_more0} {
    isError=1;
    fprintf(LEXER_ERROR_OUTPUT,"Error type A at Line %d: unknown lexeme %s\n",yylineno, yytext);
    return ILLEGAL_TOKEN;
}
{CHAR_16_illgeal_char} {
    isError=1;
    fprintf(LEXER_ERROR_OUTPUT,"Error type A at Line %d: unknown lexeme %s\n",yylineno, yytext);
    return ILLEGAL_TOKEN;
}
{CHAR_16_toolong} {
    isError=1;
    fprintf(LEXER_ERROR_OUTPUT,"Error type A at Line %d: unknown lexeme %s\n",yylineno, yytext);
    return ILLEGAL_TOKEN;
}
[^0-9a-zA-Z_'\\\(\)\[\]\{\}\;\,\+\-\*\/] {
    isError=1;
    // illgeal characters
    fprintf(LEXER_ERROR_OUTPUT,"Error type A at Line %d: unknown lexeme %s\n",yylineno, yytext);
    //yymore();
    return ILLEGAL_TOKEN;
}
[0-9]*{ID} {
    isError=1;
    // Illgeal ID
    fprintf(LEXER_ERROR_OUTPUT,"Error type A at Line %d: unknown lexeme %s\n",yylineno, yytext);
    // TODO
    return ID;
}
%%