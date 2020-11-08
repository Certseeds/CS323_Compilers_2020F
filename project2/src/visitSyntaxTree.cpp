//
// Created by nanos on 2020/11/7.
//

#include "visitSyntaxTree.hpp"

unordered_map<string, Node_TYPE> snt = {
        {"int",   Node_TYPE::INT},
        {"float", Node_TYPE::FLOAT},
        {"char",  Node_TYPE::CHAR},
};

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
    string name = getStrValueFromDecList(node->get_nodes(1));
    if (symbolTable.count(name) != 0) {
        // throw error in there
        // error type 3: variable is redefined in the same scope
    }
    if (node->get_nodes(0, 0)->nodes.empty()) {
        defPureTypeVisit(node);
    } else {
        defStructTypeVisit(node);
    }
}

/*
 * Specifier is Type
DecList
  Dec
    VarDec
      ID: code
 * */
string getStrValueFromDecList(Node *node) {
    if (node->name == "DecList") {
        Node *VarDec = node->get_nodes(0, 0);
        while (VarDec->name == "VarDec") {
            VarDec = VarDec->get_nodes(0);
        }
        return std::get<string>(VarDec->value);
    } else {
        std::cerr << "Input Node Wrong\n";
        return "";
    }
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
  // DO not forget VarDec can contain array
 * */
Array *getArrayFromVarDec(Node *node, Type *type);

void defPureTypeVisit(Node *node) {
    std::cout << "empty\n";
    //node->print(0);
    string name = getStrValueFromDecList(node->get_nodes(1));
    if (node->get_nodes(1, 0, 0)->nodes.size() == 1) {
        // pure type without array
        symbolTable[name] = new Type(name, CATEGORY::PRIMITIVE, snt[std::get<string>(node->get_nodes(0, 0)->value)]);
    } else {
        symbolTable[name] = new Type(name, CATEGORY::ARRAY,
                                     getArrayFromVarDec(node->get_nodes(1, 0, 0),
                                                        new Type("", CATEGORY::PRIMITIVE,
                                                                 snt[std::get<string>(node->get_nodes(0, 0)->value)])));
    }
}

Array *getArrayFromVarDec(Node *node, Type *type) {
    if (node == nullptr || node->name != "VarDec") {
        return nullptr;
    } else {
        int size = std::get<int>(node->get_nodes(2)->value);
        node->print();
        if (node->get_nodes(0)->nodes.size() == 1) {
            return new Array(type, size);
        } else {
            return new Array(new Type("", CATEGORY::ARRAY,
                                      getArrayFromVarDec(node->get_nodes(0),
                                                         type)), size);
        }
    }
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
    std::cout << "un empty\n";
    //node->print(0);
    string name = getStrValueFromDecList(node->get_nodes(1));
    string struct_name = std::get<string>(node->get_nodes(0, 0, 1)->value);
    if (symbolTable.count(struct_name) == 0) {
        // error there
    } else {
        if (node->get_nodes(1, 0, 0)->nodes.size() == 1) {
            symbolTable[name] = symbolTable[struct_name];
            // pure struct without Array
        } else {
            symbolTable[name] = new Type(name, CATEGORY::ARRAY,
                                         getArrayFromVarDec(node->get_nodes(1, 0, 0),
                                                            new Type("", CATEGORY::PRIMITIVE,
                                                                     snt[std::get<string>(
                                                                             node->get_nodes(0, 0, 1)->value)])));
        }
    }
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
    if (node->get_nodes(0, 0)->nodes.empty()) {
        string name = std::get<string>(node->get_nodes(1, 0, 0)->value);
        if (symbolTable.count(name) != 0) {
            // error type 3
        } else {
            symbolTable[name] = new Type(name, CATEGORY::PRIMITIVE,
                                         snt[std::get<string>(node->get_nodes(0, 0)->value)]);
        }
    } else {
        string structName = std::get<string>(node->get_nodes(0, 0, 1)->value);
        extDefVisit_SS(node);
        string variableName = std::get<string>(node->get_nodes(1, 0, 0)->value);
        if (symbolTable.count(variableName) != 0) {
            // error type 3
        } else {
            symbolTable[variableName] = symbolTable[structName];
        }
        // inside is StructSpecifier
    }
    node->print(0);
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
    string name = std::get<string>(node->get_nodes(0, 0, 1)->value);
    if (symbolTable.count(name) != 0) {
        //error type 3
    } else {
        if (node->get_nodes(0, 0, 3)->nodes.empty()) {
            symbolTable[name] = new Type(name, CATEGORY::STRUCTURE, static_cast<FieldList *>(nullptr));
            return;
        } else {
            symbolTable[name] = new Type(name, CATEGORY::STRUCTURE, getFiledListFromDefList(node->get_nodes(0, 0, 3)));
        }
    }
    node->print(0);
}

void extDefVisit_SFC(Node *node) {
    std::cout << "SFC\n";
    node->print(0);
}

void expVisit(Node *node) {
    node->print(0);
}

FieldList *getFiledListFromDefList(Node *node) {
    if (node == nullptr || node->nodes.empty() || node->name != "DefList") {
        return nullptr;
    }
    string name;
    name = getStrValueFromDecList(node->get_nodes(0, 1));
    if (node->get_nodes(0, 0, 0)->nodes.empty()) {
        // struct内为normal变量visitSyntaxTree.cpp
        //if (node->get_nodes(0, 0, 0)->name == "TYPE") {
        //name = getStrValueFromDecList(node->get_nodes(0, 1));
        //} else if (node->get_nodes(0, 0, 0)->name == "StructSpecifier") {
        //}
        if (symbolTable.count(name) == 0) {
            // error , 出现未定义变量
        }
    } else {
        // struct内有struct
        name = name;
    }
    return new FieldList(name, symbolTable[name], getFiledListFromDefList(node->get_nodes(1)));
}