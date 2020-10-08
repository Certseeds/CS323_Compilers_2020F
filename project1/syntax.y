%{
    #ifndef __cplusplus
      #include "lex.yy.c"
    #else 
      #include "lex.yy.cc"
    #endif
    void yyerror(const char const *s);
    void lineinfor(void);
    struct Node* root_node;
    extern int isError;
    // %language "c++"
    #define PARSER_error_OUTPUT stdout
    //yydebug = 1;
    #include "yyerror_myself.h"
%}
%locations
%union{
    struct Node* Node_value;
}
%nonassoc LOWER_ERROR
%nonassoc <Node_value> ILLEGAL_TOKEN
%nonassoc <Node_value> LOWER_THAN_ELSE
%nonassoc <Node_value> ELSE
%token <Node_value> TYPE STRUCT
%token <Node_value> IF WHILE RETURN
%token <Node_value> INT
%token <Node_value> FLOAT
%token <Node_value> CHAR
%token <Node_value> ID
%right <Node_value> ASSIGN
%left <Node_value> OR
%left <Node_value> AND
%left <Node_value> LT LE GT GE NE EQ
%nonassoc LOWER_MINUS
%left <Node_value> PLUS MINUS
%left <Node_value> MUL DIV
%right <Node_value> NOT
%left <Node_value> LP RP LB RB DOT
%token <Node_value> SEMI COMMA
%token <Node_value> LC RC

%type <Node_value> Program ExtDefList
%type <Node_value> ExtDef ExtDecList Specifier StructSpecifier VarDec
%type <Node_value> FunDec VarList ParamDec CompSt StmtList Stmt DefList
%type <Node_value> Def DecList Dec Args Exp
%%
/* high-level definition */
Program: ExtDefList {
    $$=new_node_line_num("Program",@$.first_line,1);
    node_set_sub($$,1,$1);
    root_node=$$;
}
;
ExtDefList:{$$=new_node_line_num("ExtDefList",@$.first_line,0);$$->print=&print_nothing;}
    | ExtDef ExtDefList {$$=new_node_line_num("ExtDefList",@$.first_line,2); node_set_sub($$,2,$1,$2);}
    ;
ExtDef: Specifier ExtDecList SEMI  {$$=new_node_line_num("ExtDef",@$.first_line,3); node_set_sub($$,3,$1,$2,$3);}
    | Specifier SEMI {$$=new_node_line_num("ExtDef",@$.first_line,2); node_set_sub($$,2,$1,$2);}
    | Specifier FunDec CompSt {$$=new_node_line_num("ExtDef",@$.first_line,3); node_set_sub($$,3,$1,$2,$3);}
    | Specifier ExtDecList error  {yyerror_myself(MISS_SEMI);}
    | Specifier error {yyerror_myself(MISS_SEMI);}
    ;
ExtDecList: VarDec {$$=new_node_line_num("ExtDecList",@$.first_line,1);node_set_sub($$,1,$1);}
    | VarDec COMMA ExtDecList {$$=new_node_line_num("ExtDecList",@$.first_line,3); node_set_sub($$,3,$1,$2,$3);}
    | VarDec ExtDecList error {yyerror_myself(MISS_COMMA);}
    ;
/* specifier */
Specifier: TYPE {$$=new_node_line_num("Specifier",@$.first_line,1);node_set_sub($$,1,$1);}
    | StructSpecifier {$$=new_node_line_num("Specifier",@$.first_line,1);node_set_sub($$,1,$1);}
    ;
StructSpecifier: STRUCT ID LC DefList RC {
    $$=new_node_line_num("StructSpecifier",@$.first_line,5); node_set_sub($$,5,$1,$2,$3,$4,$5);}
    | STRUCT ID  {$$=new_node_line_num("StructSpecifier",@$.first_line,2); node_set_sub($$,2,$1,$2);}
    | STRUCT ID LC DefList error { isError = 1;yyerror_myself(LACK_OF_RC); }
    ;
/* declarator */
VarDec: ID {$$=new_node_line_num("VarDec",@$.first_line,1);node_set_sub($$,1,$1);}
    | VarDec LB INT RB {
    $$=new_node_line_num("VarDec",@$.first_line,4); node_set_sub($$,4,$1,$2,$3,$4);}
    | VarDec LB INT error %prec LOWER_ERROR {yyerror_myself(LACK_OF_RB);}
FunDec: ID LP VarList RP {
    $$=new_node_line_num("FunDec",@$.first_line,4); node_set_sub($$,4,$1,$2,$3,$4);}
    | ID LP RP  {$$=new_node_line_num("FunDec",@$.first_line,3); node_set_sub($$,3,$1,$2,$3);}
    | ID LP VarList error {yyerror_myself(LACK_OF_RP);}
    | ID LP error {yyerror_myself(LACK_OF_RP);}
    ;
VarList: ParamDec COMMA VarList {$$=new_node_line_num("VarList",@$.first_line,3); node_set_sub($$,3,$1,$2,$3);}
    | ParamDec VarList error {yyerror_myself(MISS_COMMA);}
    | ParamDec {$$=new_node_line_num("VarList",@$.first_line,1); node_set_sub($$,1,$1);}
    ;
ParamDec: Specifier VarDec {$$=new_node_line_num("ParamDec",@$.first_line,2); node_set_sub($$,2,$1,$2);}
    ;
/* statement */
CompSt: LC DefList StmtList RC {
    $$=new_node_line_num("CompSt",@$.first_line,4); node_set_sub($$,4,$1,$2,$3,$4);}
;
StmtList:  {$$=new_node_line_num("StmtList",@$.first_line,0);$$->print=&print_nothing;}
    |  Stmt StmtList {$$=new_node_line_num("StmtList",@$.first_line,2); node_set_sub($$,2,$1,$2);}
    ;
Stmt: Exp SEMI {$$=new_node_line_num("Stmt",@$.first_line,2); node_set_sub($$,2,$1,$2);}
    | CompSt {$$=new_node_line_num("Stmt",@$.first_line,1);node_set_sub($$,1,$1);}
    | RETURN Exp SEMI {$$=new_node_line_num("Stmt",@$.first_line,3); node_set_sub($$,3,$1,$2,$3);}
    | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE {
    $$=new_node_line_num("Stmt",@$.first_line,5); node_set_sub($$,5,$1,$2,$3,$4,$5);}
    | IF LP Exp RP Stmt ELSE Stmt {
    $$=new_node_line_num("Stmt",@$.first_line,7); node_set_sub($$,7,$1,$2,$3,$4,$5,$6,$7);}
    | WHILE LP Exp RP Stmt {
    $$=new_node_line_num("Stmt",@$.first_line,5); node_set_sub($$,5,$1,$2,$3,$4,$5);}
    | WHILE LP Exp error Stmt {yyerror_myself(LACK_OF_RP); }
    | Exp error {yyerror_myself(MISS_SEMI);}
    | RETURN Exp error {yyerror_myself(MISS_SEMI);}
    | IF LP Exp error Stmt  {YYERROR;yyerror_myself(LACK_OF_RP); }
    | IF error Exp RP Stmt {yyerror_myself(LACK_OF_LP); }
    ;
/* local definition */
DefList: {$$=new_node_line_num("DefList",@$.first_line,0);$$->print=&print_nothing;}
    | Def DefList {$$=new_node_line_num("DefList",@$.first_line,2); node_set_sub($$,2,$1,$2);}
    ;
Def: Specifier DecList SEMI {$$=new_node_line_num("Def",@$.first_line,3); node_set_sub($$,3,$1,$2,$3);}
    | Specifier DecList error {yyerror_myself(MISS_SEMI);}
    | error DecList SEMI {yyerror_myself(MISS_SPEC);}
    ;
DecList: Dec {$$=new_node_line_num("DecList",@$.first_line,1);node_set_sub($$,1,$1);}
    | Dec COMMA DecList {$$=new_node_line_num("DecList",@$.first_line,3); node_set_sub($$,3,$1,$2,$3);}
    | Dec  DecList error {yyerror_myself(MISS_COMMA);}
;
Dec: VarDec {$$=new_node_line_num("Dec",@$.first_line,1); node_set_sub($$,1,$1);}
    | VarDec ASSIGN Exp {$$=new_node_line_num("Dec",@$.first_line,3); node_set_sub($$,3,$1,$2,$3);}
    ;
/* Expression */
Args: Exp COMMA Args  {$$=new_node_line_num("Args",@$.first_line,3); node_set_sub($$,3,$1,$2,$3);}
    | Exp {$$=new_node_line_num("Args",@$.first_line,1);node_set_sub($$,1,$1);}
/*TODO the lack of COMMA in exp and Args*/
    ;
Exp: Exp ASSIGN Exp {$$=new_node_line_num("Exp",@$.first_line,3); node_set_sub($$,3,$1,$2,$3);}
    | Exp AND Exp {$$=new_node_line_num("Exp",@$.first_line,3); node_set_sub($$,3,$1,$2,$3);}
    | Exp OR Exp {$$=new_node_line_num("Exp",@$.first_line,3); node_set_sub($$,3,$1,$2,$3);}
    | Exp LT Exp {$$=new_node_line_num("Exp",@$.first_line,3); node_set_sub($$,3,$1,$2,$3);}
    | Exp LE Exp {$$=new_node_line_num("Exp",@$.first_line,3); node_set_sub($$,3,$1,$2,$3);}
    | Exp GT Exp {$$=new_node_line_num("Exp",@$.first_line,3); node_set_sub($$,3,$1,$2,$3);}
    | Exp GE Exp {$$=new_node_line_num("Exp",@$.first_line,3); node_set_sub($$,3,$1,$2,$3);}
    | Exp NE Exp {$$=new_node_line_num("Exp",@$.first_line,3); node_set_sub($$,3,$1,$2,$3);}
    | Exp EQ Exp {$$=new_node_line_num("Exp",@$.first_line,3); node_set_sub($$,3,$1,$2,$3);}
    | Exp PLUS Exp {$$=new_node_line_num("Exp",@$.first_line,3); node_set_sub($$,3,$1,$2,$3);}
    | Exp MINUS Exp {$$=new_node_line_num("Exp",@$.first_line,3); node_set_sub($$,3,$1,$2,$3);}
    | Exp MUL Exp {$$=new_node_line_num("Exp",@$.first_line,3); node_set_sub($$,3,$1,$2,$3);}
    | Exp DIV Exp {$$=new_node_line_num("Exp",@$.first_line,3); node_set_sub($$,3,$1,$2,$3);}
    | LP Exp RP {$$=new_node_line_num("Exp",@$.first_line,3); node_set_sub($$,3,$1,$2,$3);}
    | LP Exp error {yyerror_myself(LACK_OF_RP);}
    | MINUS Exp %prec LOWER_MINUS {$$=new_node_line_num("Exp",@$.first_line,1);node_set_sub($$,2,$1,$2);}
    | NOT Exp {$$=new_node_line_num("Exp",@$.first_line,1);node_set_sub($$,2,$1,$2);}
    | ID LP Args RP {$$=new_node_line_num("Exp",@$.first_line,4);
        node_set_sub($$,4,$1,$2,$3,$4);}
    | ID LP Args error {yyerror_myself(LACK_OF_RP);}
    | ID LP RP {$$=new_node_line_num("Exp",@$.first_line,3); node_set_sub($$,3,$1,$2,$3);}
    | ID LP error {yyerror_myself(LACK_OF_RP);}
    | Exp LB Exp RB{
        $$=new_node_line_num("Exp",@$.first_line,4);
        node_set_sub($$,4,$1,$2,$3,$4);
    }
    | Exp LB Exp error {yyerror_myself(LACK_OF_RB);}
    | Exp DOT ID {
        $$=new_node_line_num("Exp",@$.first_line,3);
        node_set_sub($$,3,$1,$2,$3);
    }
    | ID {$$=new_node_line_num("Exp",@$.first_line,1);node_set_sub($$,1,$1);}
    | INT {$$=new_node_line_num("Exp",@$.first_line,1);node_set_sub($$,1,$1);}
    | FLOAT {$$=new_node_line_num("Exp",@$.first_line,1);node_set_sub($$,1,$1);}
    | CHAR {$$=new_node_line_num("Exp",@$.first_line,1);node_set_sub($$,1,$1);}
    | Exp ILLEGAL_TOKEN Exp {}
    | ILLEGAL_TOKEN {}
    ;
%%
void yyerror(const char const *s){
    isError=1;
    fprintf(PARSER_error_OUTPUT,"Error type B at Line %d: ",yylloc.first_line-1);
    //fprintf(PARSER_error_OUTPUT, "syntax Error: %s\n", s);
    //lineinfor();
}

void lineinfor(void){
    fprintf(PARSER_error_OUTPUT, "begin at:(%d,%d)\n",yylloc.first_line,yylloc.first_column);
    fprintf(PARSER_error_OUTPUT, "end at:(%d,%d)\n",yylloc.last_line,yylloc.last_column);
}
