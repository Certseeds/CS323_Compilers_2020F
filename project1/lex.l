%{
    const int EXIT_FAIL =-1;
    const int EXIT_OK =0;
    int indicator = 0;
    char *addr_type = NULL;
%}
%option noyywrap

letters [A-Za-z]
letters_ [{letter}_]
digit [0-9]
dight_16 [0-9a-f]
INT32_10 ^[+-]?(0|([1-9]{digit}*))$
UINT32_10 ^(0|([1-9]{digit}*))$
UINT32_16 ^0[xX](0|[1-9a-f]{digit_16}*)$
INT32 {INT32_10}|{UINT32_16}
UFLOAT32 ^{digit}+(.{digit}*)?([Ee][+-]?{digit}+)?$
ID {letters_}({letters_}|{digit}){1,31}
CHAR ^'[]'$
%%
{INT32_10} {
    // TODO hexadecimal
    int value = text_10_to_int32(yytext);
    printf("INT32 decimal %d\n",value);
}
{UINT32_16} {
    int value = text_16_to_int32(yytext);
    printf("INT hexadecimal %d\n",value);
}

{UFLOAT32} {
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
int text_16_to_int32(const char* const arg){
    int length = strlen(arg);
    int index = 2;
    long will_return = 0;
    for(;index<length;++index){
        if(arg[index] >= 'a'){
            arg[index] = arg[index]-'a'+'0'+10;
        }
        will_return*=16;
        will_return += (arg[index]-'0');
        if(will_return > INT32_MAX){
            // TODO
        }
    }
    // printf("%ld",will_return);
    return will_return;
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
