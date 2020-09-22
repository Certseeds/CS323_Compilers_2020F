%{
    #include"lex.yy.c"
    void yyerror(const char *s);
    int result;
// P is ()
// B is []
// C is {}

%}
%token LP RP LB RB LC RC
%%
String: snd { result=1;};

snd: in  
    | LP snd RP 
    | LB snd RB 
    | LC snd RC 
    | snd snd 
;
in:   LP RP
    | LB RB  
    | LC RC  
;
%%
void yyerror(const char *s){
    result=0;
}
int validParentheses(char *expr){
    yy_scan_string(expr);
    result=-1;
    yyparse();
    return result;
}
