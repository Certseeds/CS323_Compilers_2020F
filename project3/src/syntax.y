%{
    #include <string>
    #include <unordered_map>
    #include "type.hpp"
    #include "visitSyntaxTree.hpp"
    #include "translate.hpp"
    using std::string;
    using std::unordered_map;
    #define YY_NO_UNPUT
    #include "lex.yy.c"
    void yyerror(const char *s);
    void lineinfor(void);
    Node* root_node;
    unordered_map<string,Type*> symbolTable= initSymBolTable();
    vector<InterCode*> ircodes;
    extern int isError;
    #define PARSER_error_OUTPUT stdout
    #include "yyerror_myself.hpp"
%}
%require "3.0.4"
%locations
%union{
    Node* Node_value;
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
%type <Node_value> ExtDef ExtDecList Specifier StructSpecifier VarDec Specifier_FunDec_Recv
%type <Node_value> FunDec VarList ParamDec CompSt StmtList Stmt DefList
%type <Node_value> Def DecList Dec Args Exp
%%
/* high-level definition */
Program: ExtDefList {
    $$= new Node("Program",@$.first_line);
    $$->push_back($1);
    root_node=$$;
};
ExtDefList:{$$=new Node("ExtDefList",@$.first_line,Node_TYPE::NOTHING);}
    | ExtDef ExtDefList {$$=new Node("ExtDefList",@$.first_line); $$->push_back($1,$2);}
    ;
ExtDef: Specifier ExtDecList SEMI  {
    $$=new Node("ExtDef",@$.first_line);
    $$->push_back($1,$2,$3);
    extDefVisit_SES($$);
    }
    | Specifier SEMI {
    $$=new Node("ExtDef",@$.first_line);
    $$->push_back($1,$2);
    extDefVisit_SS($$);
    }
    | Specifier_FunDec_Recv CompSt {
    $$=new Node("ExtDef",@$.first_line);
    $$->push_back($1->nodes[0],$1->nodes[1],$2);
    extDefVisit_SFC($$);
    translate_functionBodyDefine($$,$1,$2);
    $$->print_vector_intercode();
    }
    | Specifier ExtDecList error  {yyerror_myself(YYERROR_TYPE::MISS_SEMI);}
    | Specifier error {yyerror_myself(YYERROR_TYPE::MISS_SEMI);}
    ;
Specifier_FunDec_Recv:Specifier FunDec{
    $$=new Node("Specifier_FunDec_Recv",@$.first_line);
    $$->push_back($1,$2);
    Specifier_FunDec_Recv_SF($$);
    translate_enterFunction($$);
    //$$->print_vector_intercode();
};
ExtDecList: VarDec {$$=new Node("ExtDecList",@$.first_line);$$->push_back($1);}
    | VarDec COMMA ExtDecList {$$=new Node("ExtDecList",@$.first_line);$$->push_back($1,$2,$3);}
    | VarDec ExtDecList error {yyerror_myself(YYERROR_TYPE::MISS_COMMA);}
    ;
/* specifier */
Specifier: TYPE {$$=new Node("Specifier",@$.first_line);$$->push_back($1);}
    | StructSpecifier {$$=new Node("Specifier",@$.first_line);$$->push_back($1);}
    ;
StructSpecifier: STRUCT ID LC DefList RC {
    $$=new Node("StructSpecifier",@$.first_line); $$->push_back($1,$2,$3,$4,$5);}
    | STRUCT ID  {$$=new Node("StructSpecifier",@$.first_line); $$->push_back($1,$2);}
    | STRUCT ID LC DefList error { isError = 1;yyerror_myself(YYERROR_TYPE::LACK_OF_RC); }
    ;
/* declarator */
VarDec: ID {$$=new Node("VarDec",@$.first_line);$$->push_back($1);}
    | VarDec LB INT RB {
    $$=new Node("VarDec",@$.first_line); $$->push_back($1,$2,$3,$4);}
    | VarDec LB INT error %prec LOWER_ERROR {yyerror_myself(YYERROR_TYPE::LACK_OF_RB);}
FunDec: ID LP VarList RP {
    $$=new Node("FunDec",@$.first_line); $$->push_back($1,$2,$3,$4);funDecVisit($$);}
    | ID LP RP  {$$=new Node("FunDec",@$.first_line); $$->push_back($1,$2,$3);funDecVisit($$);}
    | ID LP VarList error {yyerror_myself(YYERROR_TYPE::LACK_OF_RP);}
    | ID LP error {yyerror_myself(YYERROR_TYPE::LACK_OF_RP);}
    ;
VarList: ParamDec COMMA VarList {$$=new Node("VarList",@$.first_line); $$->push_back($1,$2,$3);}
    | ParamDec VarList error {yyerror_myself(YYERROR_TYPE::MISS_COMMA);}
    | ParamDec {$$=new Node("VarList",@$.first_line); $$->push_back($1);}
    ;
ParamDec: Specifier VarDec {$$=new Node("ParamDec",@$.first_line); $$->push_back($1,$2);}
    ;
/* statement */
CompSt: LC DefList StmtList RC {
    $$=new Node("CompSt",@$.first_line); $$->push_back($1,$2,$3,$4);
    translate_CompstMerge($$,$2,$3);
    }
;
StmtList:  {$$=new Node("StmtList",@$.first_line,Node_TYPE::NOTHING);}
    |  Stmt StmtList {$$=new Node("StmtList",@$.first_line); $$->push_back($1,$2);
        translate_StmtlistMerge($$);
    }
    ;
Stmt: Exp SEMI {
    $$=new Node("Stmt",@$.first_line); $$->push_back($1,$2);
        translate_StmtMergeExp($$);
    }
    | CompSt {
    $$=new Node("Stmt",@$.first_line);$$->push_back($1);
      $$->intercodes = $1->intercodes;
    }
    | RETURN Exp SEMI {
    $$=new Node("Stmt",@$.first_line); $$->push_back($1,$2,$3);
     translate_Return($$);
    }
    | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE {
    $$=new Node("Stmt",@$.first_line); $$->push_back($1,$2,$3,$4,$5);
    translate_if($$);
    }
    | IF LP Exp RP Stmt ELSE Stmt {
    $$=new Node("Stmt",@$.first_line); $$->push_back($1,$2,$3,$4,$5,$6,$7);
    translate_ifelse($$);
    }
    | WHILE LP Exp RP Stmt {
    $$=new Node("Stmt",@$.first_line); $$->push_back($1,$2,$3,$4,$5);
    translate_while($$);
    }
    | WHILE LP Exp error Stmt {yyerror_myself(YYERROR_TYPE::LACK_OF_RP); }
    | Exp error {yyerror_myself(YYERROR_TYPE::MISS_SEMI);}
    | RETURN Exp error {yyerror_myself(YYERROR_TYPE::MISS_SEMI);}
    | IF LP Exp error Stmt  {YYERROR;yyerror_myself(YYERROR_TYPE::LACK_OF_RP); }
    | IF error Exp RP Stmt {yyerror_myself(YYERROR_TYPE::LACK_OF_LP); }
    ;
/* local definition */
DefList: {$$=new Node("DefList",@$.first_line,Node_TYPE::NOTHING);}
    | Def DefList {
    $$=new Node("DefList",@$.first_line); $$->push_back($1,$2);
    translate_DeflistMerge($$);
    }
    ;
/*
// Definition of
basic  name;
// */
Def: Specifier DecList SEMI {
    $$=new Node("Def",@$.first_line);
    $$->push_back($1,$2,$3);
    defVisit($$);
    $$->intercodes = $2->intercodes;
    }
    | Specifier DecList error {yyerror_myself(YYERROR_TYPE::MISS_SEMI);}
    | error DecList SEMI {
    yyerror_myself(YYERROR_TYPE::MISS_SPEC);
    printf("error\n");
    $$->print();
    $2->print();
    }
    ;
DecList: Dec {
    $$=new Node("DecList",@$.first_line);$$->push_back($1);
    $$->intercodes = $1->intercodes;
    }
    | Dec COMMA DecList {
    $$=new Node("DecList",@$.first_line); $$->push_back($1,$2,$3);
      translate_DecListMerge($$);
    }
    | Dec DecList error {yyerror_myself(YYERROR_TYPE::MISS_COMMA);}
;
Dec: VarDec {$$=new Node("Dec",@$.first_line); $$->push_back($1);}
    | VarDec ASSIGN Exp {
    $$=new Node("Dec",@$.first_line); $$->push_back($1,$2,$3);
    // 声明时初始化
    translate_varDecAssign($$);
    }
    ;
/* Expression */
Args: Exp COMMA Args  {$$=new Node("Args",@$.first_line); $$->push_back($1,$2,$3);}
    | Exp {
    $$=new Node("Args",@$.first_line);$$->push_back($1);
    $$->intercodes = $1->intercodes;
    }
/*TODO the lack of COMMA in exp and Args*/
    ;
Exp: Exp ASSIGN Exp {
    $$=new Node("Exp",@$.first_line);
    $$->push_back($1,$2,$3);
    checkRvalueInLeftSide($$);
    checkTypeMatch($1,$3,@2.first_line);
    translate_Exp($$);
    }
    | Exp AND Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getBoolOperatorType($$,$1,$3);}
    | Exp OR Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getBoolOperatorType($$,$1,$3);}
    | Exp LT Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getAlrthOperatorType($$,$1,$3);}
    | Exp LE Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getAlrthOperatorType($$,$1,$3);}
    | Exp GT Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getAlrthOperatorType($$,$1,$3);}
    | Exp GE Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getAlrthOperatorType($$,$1,$3);}
    | Exp NE Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getAlrthOperatorType($$,$1,$3);}
    | Exp EQ Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getAlrthOperatorType($$,$1,$3);}
    | Exp PLUS Exp {
    $$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getAlrthOperatorType($$,$1,$3);
    translate_Exp($$);
    }
    | Exp MINUS Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getAlrthOperatorType($$,$1,$3);
        translate_Exp($$);
    }
    | Exp MUL Exp {
    $$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getAlrthOperatorType($$,$1,$3);
    translate_Exp($$);
    }
    | Exp DIV Exp {$$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);getAlrthOperatorType($$,$1,$3);
            translate_Exp($$);
    }
    | LP Exp RP {
    $$=new Node("Exp",@$.first_line); $$->push_back($1,$2,$3);$$->type=$2->type;
    $$->interCode = $2->interCode;
    $$->intercodes = $2->intercodes;
    } // lp is (
    | LP Exp error {yyerror_myself(YYERROR_TYPE::LACK_OF_RP);}
    | MINUS Exp %prec LOWER_MINUS {
    $$=new Node("Exp",@$.first_line);
    $$->push_back($1,$2);
    $$->type=$2->type;
    checkAlrthOperatorType($2);
    translate_minus_exp($$);
    }
    | NOT Exp {$$=new Node("Exp",@$.first_line);$$->push_back($1,$2);$$->type=$2->type;}
    | ID LP Args RP {
      checkInvokeExist($1,@1.first_line);
      checkFunctionParams($1,$3,@3.first_line);
      $$=new Node("Exp",@$.first_line);
      $$->push_back($1,$2,$3,$4);
      getReturnTypeOfFunction($$,$1);
      translate_functionWithParamInvoke($$);
      }
    | ID LP Args error {yyerror_myself(YYERROR_TYPE::LACK_OF_RP);}
    | ID LP RP {
      checkInvokeExist($1,@1.first_line);
      checkFunctionParams($1,nullptr,@3.first_line);
      $$=new Node("Exp",@$.first_line);
      $$->push_back($1,$2,$3);
      getReturnTypeOfFunction($$,$1);
      translate_functionInvoke($$);
    }
    | ID LP error {yyerror_myself(YYERROR_TYPE::LACK_OF_RP);}
    | Exp LB Exp RB{
        $$=new Node("Exp",@$.first_line);
        $$->push_back($1,$2,$3,$4);
        // LB is [
        checkArrayExists($1);
        getArrayType($$,$1,$3);
    }
    | Exp LB Exp error {yyerror_myself(YYERROR_TYPE::LACK_OF_RB);}
    | Exp DOT ID {
        $$=new Node("Exp",@$.first_line);
        $$->push_back($1,$2,$3);
        checkNoSuchMember($$);
        searchAndPutTypeOfDot($$,$1,$3);
    }
    | ID {
    $$=new Node("Exp",@$.first_line);$$->push_back($1);
    checkIdExists($1,@1.first_line);
    idToExp($$,$1);
    }
    | INT {
    $$=new Node("Exp",@$.first_line);$$->push_back($1);
    $$->type = Type::getPrimitiveINT();
    translate_Exp($$);
//    $$->interCode = translate_Exp_INT($1);
//    $$->interCode->print();
    }
    | FLOAT {$$=new Node("Exp",@$.first_line);$$->push_back($1);
        $$->type = Type::getPrimitiveFLOAT();
        }
    | CHAR {$$=new Node("Exp",@$.first_line);$$->push_back($1);
            $$->type = Type::getPrimitiveCHAR();}
    | Exp ILLEGAL_TOKEN Exp {}
    | ILLEGAL_TOKEN {}
    ;
%%
void yyerror(const char *s){
    isError=1;
    if(s[0]  == '0'){}
    fprintf(PARSER_error_OUTPUT,"Error type B at Line %d: ",yylloc.first_line-1);
    //fprintf(PARSER_error_OUTPUT, "syntax Error: %s\n", s);
    //lineinfor();
}

void lineinfor(void){
    fprintf(PARSER_error_OUTPUT, "begin at:(%d,%d)\n",yylloc.first_line,yylloc.first_column);
    fprintf(PARSER_error_OUTPUT, "end at:(%d,%d)\n",yylloc.last_line,yylloc.last_column);
}
