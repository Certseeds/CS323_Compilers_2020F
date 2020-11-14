//
// Created by nanos on 2020/11/7.
//

#include "visitSyntaxTree.hpp"

void defStructTypeVisit(Node *node);

void defPureTypeVisit(Node *node);

string getStrValueFromDecList(Node *node);

void defStructDefinition(Node *node);

void defStructObjectDefinition(Node *node);

FieldList *getFiledListFromDefList(Node *node);

/*
 * When Bison detect a Def, enter this function
 * */
void defVisit(Node *node) {
    //node->print();
}

void checkRvalueInLeftSide(Node *node) {
    std::cout << "RValue" << std::endl;
    //node->print();
}

/*
 * Specifier is Type
DecList
  Dec
    VarDec
      ID: code
 * */
string getStrValueFromDecList(Node *node) {
    //node->print();
    return "";
}

/*
 * Specifier is Type
Def
  Specifier
    TYPE: Node_Type::
  DecList
    Dec
      VarDec
        ID: code
  SEMI
 * */
void defPureTypeVisit(Node *node) {
    //node->print();
}

/*
 * Specifier is StructSpecifier
Def (9)
  Specifier (9)
    StructSpecifier (9)
      STRUCT
      ID: my_struct
  DecList (9)
    Dec (9)
      VarDec (9)
        ID: obj
  SEMI
 * */
void defStructTypeVisit(Node *node) {
    //node->print();
}

/*
ExtDef
  Specifier // this can be type or structSpecifier
    TYPE: int
  ExtDecList
    VarDec
      ID: global
  SEMI*/
void extDefVisit_SES(Node *node) {
    std::cout << "SES\n";
    node->print();
}

/*
ExtDef (2)
  Specifier (2)
    StructSpecifier (2)
      STRUCT
      ID: my_struct
      LC
      DefList (4)
        Def (4)
          Specifier (4)
            TYPE: int
          DecList (4)
            Dec (4)
              VarDec (4)
                ID: code
          SEMI
      RC
  SEMI
*/
void extDefVisit_SS(Node *node) {
    std::cout << "SS\n";
    node->print();
}

void extDefVisit_SFC(Node *node) {
    std::cout << "SFC\n";
    node->print();
}

void expVisit(Node *node) {
    node->print();
}


FieldList *getFiledListFromDefList(Node *node) {
}