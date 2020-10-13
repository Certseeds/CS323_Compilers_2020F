%{
    #include"lex.yy.c"
    void yyerror(const char*);
//    | error COLON Value {puts(" UN Array be Key, recovered");}
%}

%token LC RC LB RB COLON COMMA
%token STRING NUMBER ILLGEAL_INT
%token TRUE FALSE VNULL
%%

Json:
      Value
    | Value COMMA error {puts("comma after the close, recovered");}
    | Value RB error {puts("Extra close RB, recovered");}
    ;
Value:
      Object
    | Array
    | ILLGEAL_INT error {puts("Numbers cannot have leading zeroes, recovered");}
    | STRING
    | NUMBER
    | TRUE
    | FALSE
    | VNULL
    ;


Object:
      LC RC
    | LC Members RC
    | LC Members RB error { puts("unmatched right bracket, recovered");}
    | LC Members RC Value error { puts("Extra value after close, recovered");}
    | LC Members COMMA error { puts("extra comma in Object 2, recovered");}
    ;
Members:
      Member
    | Member COMMA Members
    | Member COMMA error { puts("extra comma in Object, recovered");}
    ;
Member:
      STRING COLON Value
    | STRING COLON COLON Value error {puts("Double colon, recovered");}
    | STRING Value error {puts("Missing colon, recovered");}
    | STRING COMMA Value error {puts("Comma instead of colon, recovered");}
    ;
Array:
      LB RB
    | LB Values RB
    | LB Values error {puts("Unclosed array, recovered");}
    | LB Values RC error { puts("mismatch [}, recovered");}
    ;
Values:
      Value
    | Value COMMA Values
    | Value COLON Values error {puts("Colon instead of comma, recovered");}
    | Value COMMA error {puts("extra comma in Array, recovered");}
    | Value COMMA COMMA error {puts("double extra comma in Array, recovered");}
    | COMMA Value error {puts("<-- missing value, recovered");}
    ;
%%

void yyerror(const char *s){
    printf("syntax error: ");
}

int main(int argc, char **argv){
    if(argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        exit(-1);
    }
    else if(!(yyin = fopen(argv[1], "r"))) {
        perror(argv[1]);
        exit(-1);
    }
    yyparse();
    return 0;
}
