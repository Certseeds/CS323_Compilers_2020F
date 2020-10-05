%{
    #ifndef __cplusplus
      #include "lex.yy.c"
    #else 
      #include "lex.yy.cc"
    #endif
    void print_n_space(int n);
    void yyerror(const char const *s);
    void lineinfor(void);
    struct Node* root_node;
    extern int isError;
    // %language "c++"
%}
%locations
%union{
    struct Node* Node_value;
}
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
    ;
ExtDecList: VarDec {$$=new_node_line_num("ExtDecList",@$.first_line,1);node_set_sub($$,1,$1);}
    | VarDec COMMA ExtDecList {$$=new_node_line_num("ExtDecList",@$.first_line,3); node_set_sub($$,3,$1,$2,$3);}
    ;
/* specifier */
Specifier: TYPE {$$=new_node_line_num("Specifier",@$.first_line,1);node_set_sub($$,1,$1);}
    | StructSpecifier {$$=new_node_line_num("Specifier",@$.first_line,1);node_set_sub($$,1,$1);}
    ;
StructSpecifier: STRUCT ID LC DefList RC {
    $$=new_node_line_num("StructSpecifier",@$.first_line,5); node_set_sub($$,5,$1,$2,$3,$4,$5);}
    | STRUCT ID  {$$=new_node_line_num("StructSpecifier",@$.first_line,2); node_set_sub($$,2,$1,$2);}
    ;
/* declarator */
VarDec: ID {$$=new_node_line_num("VarDec",@$.first_line,1);node_set_sub($$,1,$1);}
    | VarDec LB INT RB {
    $$=new_node_line_num("VarDec",@$.first_line,4); node_set_sub($$,4,$1,$2,$3,$4);}
    ;
FunDec: ID LP VarList RP {
    $$=new_node_line_num("FunDec",@$.first_line,4); node_set_sub($$,4,$1,$2,$3,$4);}
    | ID LP VarList error {fprintf(stderr,"Missing closing parenthesis \')\'\n");}
    | ID LP RP  {$$=new_node_line_num("FunDec",@$.first_line,3); node_set_sub($$,3,$1,$2,$3);}
    | ID LP error {fprintf(stderr,"Missing closing parenthesis \')\'\n");}
    ;
VarList: ParamDec COMMA VarList  {$$=new_node_line_num("VarList",@$.first_line,3); node_set_sub($$,3,$1,$2,$3);}
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
    | RETURN Exp error {fprintf(stderr,"Missing semicolon \';\'\n");}
    | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE {
    $$=new_node_line_num("Stmt",@$.first_line,5); node_set_sub($$,5,$1,$2,$3,$4,$5);}
    | IF LP Exp RP Stmt ELSE Stmt {
    $$=new_node_line_num("Stmt",@$.first_line,7); node_set_sub($$,7,$1,$2,$3,$4,$5,$6,$7);}
    | WHILE LP Exp RP Stmt {
    $$=new_node_line_num("Stmt",@$.first_line,5); node_set_sub($$,5,$1,$2,$3,$4,$5);}
    | Exp error {}
    ;
/* local definition */
DefList: {$$=new_node_line_num("DefList",@$.first_line,0);$$->print=&print_nothing;}
    | Def DefList {$$=new_node_line_num("DefList",@$.first_line,2); node_set_sub($$,2,$1,$2);}
    ;
Def: Specifier DecList SEMI {$$=new_node_line_num("Def",@$.first_line,3); node_set_sub($$,3,$1,$2,$3);}
    | Specifier DecList error {fprintf(stderr,"Missing semicolon \';\'\n");}
    | error DecList SEMI {fprintf(stderr,"Missing specifier \n");}
    ;
DecList: Dec {$$=new_node_line_num("DecList",@$.first_line,1);node_set_sub($$,1,$1);}
    | Dec COMMA DecList {$$=new_node_line_num("DecList",@$.first_line,3); node_set_sub($$,3,$1,$2,$3);}
    ;
Dec: VarDec {$$=new_node_line_num("Dec",@$.first_line,1); node_set_sub($$,1,$1);}
    | VarDec ASSIGN Exp {$$=new_node_line_num("Dec",@$.first_line,3); node_set_sub($$,3,$1,$2,$3);}
    ;
/* Expression */
Args: Exp COMMA Args  {$$=new_node_line_num("Args",@$.first_line,3); node_set_sub($$,3,$1,$2,$3);}
    | Exp {$$=new_node_line_num("Args",@$.first_line,1);node_set_sub($$,1,$1);}
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
    | MINUS Exp {$$=new_node_line_num("Exp",@$.first_line,1);node_set_sub($$,2,$1,$2);}
    | NOT Exp {$$=new_node_line_num("Exp",@$.first_line,1);node_set_sub($$,2,$1,$2);}
    | ID LP Args RP {$$=new_node_line_num("Exp",@$.first_line,4);
        node_set_sub($$,3,$1,$2,$3,$4);}
    | ID LP Args error {fprintf(stderr,"Missing closing parenthesis \')\'\n");}
    | ID LP RP {$$=new_node_line_num("Exp",@$.first_line,3); node_set_sub($$,3,$1,$2,$3);}
    | ID LP error {fprintf(stderr,"Missing closing parenthesis \')\'\n");}
    | Exp LB Exp RB{
        $$=new_node_line_num("Exp",@$.first_line,4);
        node_set_sub($$,4,$1,$2,$3,$4);
    }
    | Exp DOT ID {
        $$=new_node_line_num("Exp",@$.first_line,3);
        node_set_sub($$,3,$1,$2,$3);
    }
    | ID {$$=new_node_line_num("Exp",@$.first_line,1);node_set_sub($$,1,$1);}
    | INT {$$=new_node_line_num("Exp",@$.first_line,1);node_set_sub($$,1,$1);}
    | FLOAT {$$=new_node_line_num("Exp",@$.first_line,1);node_set_sub($$,1,$1);}
    | CHAR {$$=new_node_line_num("Exp",@$.first_line,1);node_set_sub($$,1,$1);}
    | Exp ILLEGAL_TOKEN Exp
    | ILLEGAL_TOKEN {}
    ;
;
%%
void yyerror(const char const *s){
    isError=1;
    fprintf(stderr,"Error type B at Line %d: ",yylloc.first_line);
    //fprintf(stderr, "syntax Error: %s\n", s);
    //lineinfor();
}
void lineinfor(void){
    fprintf(stderr, "begin at:(%d,%d)\n",yylloc.first_line,yylloc.first_column);
    fprintf(stderr, "end at:(%d,%d)\n",yylloc.last_line,yylloc.last_column);
}

struct Node* new_node_key(char* nam){
    struct Node* will_return = (struct Node*)malloc(sizeof(struct Node));
    will_return->name=nam;
    will_return->nodes_num=0;
    will_return->nodes=NULL;
    will_return->print=&print_name;
    // TODO-values
}
struct Node* new_node_line_num(char* nam,int line_nu,int nodes_nu){
    struct Node* will_return = new_node_key(nam);
    will_return->linenum=line_nu;
    will_return->nodes_num=nodes_nu;
    will_return->nodes=(struct Node**)malloc(sizeof(struct Node *)*nodes_nu);
    for(int i = 0;i<nodes_nu;++i){
        will_return->nodes[i]=(struct Node*)malloc(sizeof(struct Node));
    }
    will_return->print=&print_line;
}
void node_set_sub(struct Node* node,int num,...){
    va_list valist;
    va_start(valist,num);
    for(int i = 0;i<num;i++){
        node->nodes[i]=va_arg(valist,struct Node*);
    }
    va_end(valist);
}
void print_n_space(int n){for(int i = 0;i<n;++i){printf(" ");}}
void print_line(int space,struct Node* node){
    print_n_space(space);
    printf("%s (%d)\n",node->name,node->linenum);
    if(node->nodes_num != 0){
        for(int i = 0;i< node->nodes_num;i++){
            node->nodes[i]->print(space+2,node->nodes[i]);
        }
    }
}
void print_int_value(int space,struct Node* node){
    print_n_space(space);
    printf("%s: %d\n",node->name,node->int_value);
}
void print_float_value(int space,struct Node* node){
    print_n_space(space);
    printf("%s: %f\n",node->name,node->float_value);
}
void print_char_value(int space,struct Node* node){
    print_n_space(space);
    printf("%s: %c\n",node->name,node->char_value);
}
void print_str_value(int space,struct Node* node){
    print_n_space(space);
    printf("%s: %s\n",node->name,node->string_value);
}
void print_name(int space,struct Node* node){
    print_n_space(space);
    printf("%s\n",node->name);
}
void print_nothing(int space,struct Node* node){}
int main(int argc,char** argv){
    // root_node->name="123";
    // root_node->linenum=123;
    // root_node->nodes_num=0;
    // root_node->print=&print_line;
    // root_node->print(0,root_node);
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
    if(isError == 0){
        root_node->print(0,root_node);
    }
    return 0;
}