%{
    #include <stack>
    #include <unordered_set>
    #include "Object.hpp"
    #include "lex.yy.c"
    void yyerror(const char*);
    using set_type = std::stack<std::unordered_set<std::string>>;
    set_type keys;
    JsonObject*  RootObject;
//    | error COLON Value {puts(" UN Array be Key, recovered");}
%}
%union{
    JsonObject* jsonobject;
    ArrayValue* arrayvalue;
    ObjectMember* objectmember;
    void * useless;
}
%token LC RC
%token LB RB COLON COMMA
%token <jsonobject> STRING NUMBER
%token <jsonobject> TRUE FALSE VNULL
%type <useless> LC_Out RC_Out
%type <jsonobject> Array Object Value PrintOutObject
%type <arrayvalue> Values
%type <objectmember> Members Member
%%
PrintOutObject: Object{puts("1");RootObject=$1;}
Value:
      Object{ $$=$1;}
    | Array{ $$=$1;}
    | STRING{ $$=$1;}
    | NUMBER{ $$=$1;}
    | TRUE{ $$=$1;}
    | FALSE{ $$=$1;}
    | VNULL{ $$=$1;}
    ;
Object:
      LC_Out RC_Out{
        $$ = new JsonObject(static_cast<ObjectMember*>(nullptr));
      }
    | LC_Out Members RC_Out{
        $$ = new JsonObject(static_cast<ObjectMember*>($2));
      }
    | LC_Out Members RB error { puts("unmatched right bracket, recovered");}
    | LC_Out Members RC Value error { puts("Extra value after close, recovered");}
    | LC_Out Members COMMA error { puts("extra comma in Object 2, recovered");}
    ;

LC_Out: LC  { keys.push(std::unordered_set<string>());};
RC_Out: RC { keys.pop();};
Members:
      Member{
        $$=$1;
      }
    | Member COMMA Members{
      $$=$1;
      $$->next = $3;
    }
    | Member COMMA error { puts("extra comma in Object, recovered");}
    ;
Member:
      STRING COLON Value{
        $$=new ObjectMember(std::get<std::string>($1->value),$3);
        std::string inserted = std::get<std::string>($1->value);
        if(keys.top().count(inserted) != 0){
            yyerror(inserted.c_str());
        }else{
            keys.top().insert(inserted);
        }
      }
    | STRING COLON COLON Value error {puts("Double colon, recovered");}
    | STRING Value error {puts("Missing colon, recovered");}
    | STRING COMMA Value error {puts("Comma instead of colon, recovered");}
    ;
Array:
      LB RB{
        $$=new JsonObject(static_cast<ArrayValue*>(nullptr));
      }
    | LB Values RB{
        $$=new JsonObject(static_cast<ArrayValue*>($2));
      }
    | LB Values error {puts("Unclosed array, recovered");}
    | LB Values RC error { puts("mismatch [}, recovered");}
    ;
Values:
      Value{
        $$=new ArrayValue($1);
      }
    | Value COMMA Values{
        $$=new ArrayValue($1,$3);
      }
    | Value COLON Values error {puts("Colon instead of comma, recovered");}
    | Value COMMA error {puts("extra comma in Array, recovered");}
    | Value COMMA COMMA error {puts("double extra comma in Array, recovered");}
    | COMMA Value error {puts("<-- missing value, recovered");}
    ;
%%

void yyerror(const char *s){
    printf("%s \"%s\"\n","duplicate key:",s);
    exit(0);
}