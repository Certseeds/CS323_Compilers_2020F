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
"int" {return TYPE;}
"float" {return TYPE;}
"char" {return TYPE;}
"struct" {return STRUCT;}
"if" {return IF;}
"else" {return ELSE;}
"while" {return WHILE;}
"return" {return RETURN;}
"." {return DOT;}
";" {return SEMI;}
"," {return COMMA;}
"=" {return ASSIGN;}
"<" {return LT;}
"<=" {return LE;}
">" {return GT;}
">=" {return GE;}
"!=" {return NE;}
"==" {return EQ;}
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return MUL;}
"/" {return DIV;}
"&&" {return AND;}
"||" {return OR;}
"!" {return NOT;}
"(" {return LP;}
")" {return RP;}
"[" {return LB;}
"]" {return RB;}
"{" {return LC;}
"}" {return RC;}
{ID} {
    // DONE
    // printf("ID %s\n",yytext);
    return ID;
}
{UFLOAT32} {
    yylval.float_value = atof(yytext);
    return FLOAT;
}
{UINT32_10} {
    yylval.int_value = atoi(yytext);
    return INT;
}
{UINT32_16} {
    yylval.int_value = (int)strtol(yytext,NULL,0);
    return INT;
}
{UINT32_16_error_more_0} {
    fprintf(stderr, "Error type A at Line %s: Illgeal UINT32 hex-Leading 0 \n", yytext);
    return ILLEGAL_TOKEN;
}
{UINT32_16_error_illgeal_char} {
    fprintf(stderr, "Error type A at Line %s: UINT32_16_error_illgeal_char \n", yytext);
    return ILLEGAL_TOKEN;
}
{CHAR} {
    yylval.char_value = yytext[1];
    return CHAR;
}
{CHAR_16} {
    yytext[1]='0';
    yytext[yyleng-1]='\0';
    // printf("hex char %s\n",yytext+1);
    yylval.char_value = strtoul(yytext+1,NULL,0);
    // printf("hex char %c \n",yylval.char_value);
    return CHAR;
}
{CHAR_16_more0} {
    fprintf(stderr,"Error type A at Line %d: unknown lexeme %s\n",yylineno, yytext);
    return ILLEGAL_TOKEN;
}
{CHAR_16_illgeal_char} {
    fprintf(stderr,"Error type A at Line %d: unknown lexeme %s\n",yylineno, yytext);
    return ILLEGAL_TOKEN;
}
{CHAR_16_toolong} {
    fprintf(stderr,"Error type A at Line %d: unknown lexeme %s\n",yylineno, yytext);
    return ILLEGAL_TOKEN;
}
[^0-9a-zA-Z_'\\\(\)\[\]\{\}\;\,\+\-\*\/] {
    // illgeal characters
    fprintf(stderr,"Error type A at Line %d: unknown lexeme %s\n",yylineno, yytext);
    //yymore();
    return ILLEGAL_TOKEN;
}
[0-9]{ID} {
    // Illgeal ID
    fprintf(stderr,"Error type A at Line %d: unknown lexeme %s\n",yylineno, yytext);
    // TODO
    return ID;
}
%%
// int main(int argc, char **argv){
//     char *file_path;
//     if(argc < 2){
//         fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
//         return EXIT_FAIL;
//     }
//     else if(argc == 2){
//         file_path = argv[1];
//         if(!(yyin = fopen(file_path, "r"))){
//             perror(argv[1]);
//             return EXIT_FAIL;
//         }
//         yylex();
//         return EXIT_OK;
//     }
//     else{
//         fputs("Too much arguments!\n", stderr);
//         return EXIT_FAIL;
//     }
// }
