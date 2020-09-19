%{
    const int EXIT_FAIL =-1;
    const int EXIT_OK =0;
    int indicator = 0;
    char *addr_type = NULL;
%}
%option noyywrap

letters_ [A-Za-z_]
digit [0-9]
INT_LENGTH32 ^[+-]?(0|([1-9]{digit}*))$
FLOAT_LENGTH32 ^{digit}*(.{digit}+)?([Ee][+-]?{digit}+)?$
ID {letters_}({letters_}|{digit}){1,31}
CHAR [a-zA-Z]
%%
{INT_LENGTH32} {
    // TODO hexadecimal
    int value = text_10_to_int32(yytext);
    printf("INT %d\n",value);
}
{FLOAT_LENGTH32} {
    // TODO analysis
    printf("FLOAT %s\n",yytext);
}
{ID} {
    // DONE
    printf("ID %s\n",yytext);
}
{CHAR} {
    // TODO
}
\n {}
. {printf("Error type A at Line %d: Unknown characters \'%s\'\n",yylineno, yytext); }
%%
int text_10_to_int32(const char* const arg){
    int length = strlen(arg);
    int index = 0;
    long will_return = 0;
    int sign = 1;
    if(arg[0]=='-' || arg[0] == '+'){
        index++;
        if(arg[0]=='-'){
            sign = -1;
        }
    }
    for(;index<length;++index){
        will_return*=10;
        will_return += (arg[index]-'0');
        if(sign == 1 && will_return > INT32_MAX){
            // TODO
        }else if(sign == -1 && will_return >= INT32_MAX){
            // TODO
        }
    }
    // printf("%ld",will_return);
    return will_return*sign;
}
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
