%{
    #include "lex.yy.c"
    void yyerror(const char const *s);
    void lineinfor(void);
    struct Node{
        char * name;
        int linenum;
        Node[] nodes;
    };
%}
%locations
%union{
    char char_value;
    int int_value;
    float float_value;
    char * string_value;
}
%nonassoc ILLEGAL_TOKEN
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%token TYPE STRUCT
%token IF WHILE RETURN
%token <int_value> INT 
%token <float_value> FLOAT
%token <string_value> CHAR
%token ID
%right ASSIGN
%left OR
%left AND
%left LT LE GT GE NE EQ
%left PLUS MINUS
%left MUL DIV
%right NOT
%left LP RP LB RB DOT
%token SEMI COMMA
%token LC RC
%%
/* high-level definition */
Program: ExtDefList;
ExtDefList:
    | ExtDef ExtDefList
    ;
ExtDef: Specifier ExtDecList SEMI
    | Specifier SEMI
    | Specifier FunDec CompSt
    ;
ExtDecList: VarDec
    | VarDec COMMA ExtDecList
    ;
/* specifier */
Specifier: TYPE
    | StructSpecifier
    ;
StructSpecifier: STRUCT ID LC DefList RC
    | STRUCT ID
    ;
/* declarator */
VarDec: ID
    | VarDec LB INT RB
    ;
FunDec: ID LP VarList RP
    | ID LP VarList error {fprintf(stderr,"Missing closing parenthesis \')\'\n");}
    | ID LP RP
    | ID LP error {fprintf(stderr,"Missing closing parenthesis \')\'\n");}
    ;
VarList: ParamDec COMMA VarList
    | ParamDec
    ;
ParamDec: Specifier VarDec
    ;
/* statement */
CompSt: LC DefList StmtList RC
    ;
StmtList:
    |  Stmt StmtList
    ;
Stmt: Exp SEMI
    | CompSt
    | RETURN Exp SEMI 
    | RETURN Exp error {fprintf(stderr,"Missing semicolon \';\'\n");}
    | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE
    | IF LP Exp RP Stmt ELSE Stmt
    | WHILE LP Exp RP Stmt
    | Exp error
    ;
/* local definition */
DefList: 
    |Def DefList
    ;
Def: Specifier DecList SEMI
    |Specifier DecList error {fprintf(stderr,"Missing semicolon \';\'\n");}
    | error DecList SEMI {fprintf(stderr,"Missing specifier \n");}
    ;
DecList: Dec
    | Dec COMMA DecList
    ;
Dec: VarDec
    | VarDec ASSIGN Exp
    ;
/* Expression */
Args: Exp COMMA Args
    | Exp
    ;
Exp: Exp ASSIGN Exp
    | Exp AND Exp
    | Exp OR Exp
    | Exp LT Exp
    | Exp LE Exp
    | Exp GT Exp
    | Exp GE Exp
    | Exp NE Exp
    | Exp EQ Exp
    | Exp PLUS Exp
    | Exp MINUS Exp
    | Exp MUL Exp
    | Exp DIV Exp
    | LP Exp RP
    | MINUS Exp
    | NOT Exp
    | ID LP Args RP
    | ID LP Args error {fprintf(stderr,"Missing closing parenthesis \')\'\n");}
    | ID LP RP
    | ID LP error {fprintf(stderr,"Missing closing parenthesis \')\'\n");}
    | Exp LB Exp RB
    | Exp DOT ID
    | ID
    | INT
    | FLOAT
    | CHAR
    | Exp ILLEGAL_TOKEN Exp
    | ILLEGAL_TOKEN
    ;
;
%%
void yyerror(const char const *s){
    fprintf(stderr,"Error type B at Line %d: ",yylloc.first_line);
    //fprintf(stderr, "syntax Error: %s\n", s);
    //lineinfor();
}
void lineinfor(void){
    fprintf(stderr, "begin at:(%d,%d)\n",yylloc.first_line,yylloc.first_column);
    fprintf(stderr, "end at:(%d,%d)\n",yylloc.last_line,yylloc.last_column);
}
int main(int argc,char** argv){
    Node* node = malloc(sizeof(Node));
    //yydebug = 1;
    //
    if(argc <= 1){
        fprintf(stderr,"no input path");
        return 1;
    }
    else if(argc > 2){
        fprintf(stderr,"too much input path");
        return 1;
    }
    else{
        FILE *f = fopen(argv[1],"r");
        if(!f){
            fprintf(stderr,"error of path %s",argv[1]);
            return 1;
        }
        yyrestart(f);
        yyparse();
    }
    return 0;
}