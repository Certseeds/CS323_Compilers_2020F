%{
    const int EXIT_FAIL =-1;
    const int EXIT_OK =0;
    int indicator = 0;
    int line = 0;
    char *addr_type = NULL;
    //
%}
%option noyywrap
letters [A-Za-z]
letters_ [A-Za-z_]
digit [0-9]
digit_16 [0-9a-f]
INT32_10 [+-]?(0|([1-9]{digit}*))
UINT32_10 (0|([1-9]{digit}*))
UINT32_16 0[xX](0|[1-9a-f]{digit_16}*)
UINT32 {UINT32_10}|{UINT32_16}
UFLOAT32 ^{digit}+(.{digit}*)?([Ee][+-]?{digit}+)?$
ID {letters_}({letters_}|{digit}){0,31}
TYPE_INT "int"
TYPE_FLOAT "float"
TYPE_CHAR "char"
CHAR ^.$
%%
\n {line++;}
" " {}
{TYPE_INT} {printf("TYPE int\n");}
{TYPE_FLOAT} {printf("TYPE float\n");}
{TYPE_CHAR} {printf("TYPE char\n");}
"(" {printf("LP\n");}
")" {printf("RP\n");}
"[" {printf("LB\n");}
"]" {printf("RB\n");}
"{" {printf("LC\n");}
"}" {printf("RC\n");}
"=" {printf("ASSIGN\n");}
"," {printf("COMMA\n");}
";" {printf("SEMI\n");}
{UINT32_10} {
    // TODO hexadecimal
    int value = atoi(yytext);
    printf("INT %d\n",value);
}
{UINT32_16} {
    int value = strtol(yytext,NULL,0);
    printf("INT hexadecimal %d\n",value);
}
{UFLOAT32} {
    float value = atof(yytext);
    printf("FLOAT %f\n",value);
}
{ID} {
    // DONE
    printf("ID %s\n",yytext);
}
{CHAR} {printf("CHAR %s\n",yytext);}
. {printf("Error type A at Line %d: Unknown characters \'%s\'\n",yylineno, yytext); }
%%
int main(int argc, char **argv){
    char *file_path;
    if(argc < 2){
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return EXIT_FAIL;
    }
    else if(argc == 2){
        file_path = argv[1];
        if(!(yyin = fopen(file_path, "r"))){
            perror(argv[1]);
            return EXIT_FAIL;
        }
        yylex();
        return EXIT_OK;
    }
    else{
        fputs("Too much arguments!\n", stderr);
        return EXIT_FAIL;
    }
}
