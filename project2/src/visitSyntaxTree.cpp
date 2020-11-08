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

void extDefVisit_SES_PureType(Node *node);

void extDefVisit_SES_StructType(Node *node);

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

string getStrValueFromExtDecList(Node *node) {
    if (node->name == "ExtDecList") {
        Node *VarDec = node->get_nodes(0);
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
    ////node->print(0);
    Node *decList = node->get_nodes(1);
    string name = getStrValueFromDecList(decList);
    auto _type = snt[std::get<string>(node->get_nodes(0, 0)->value)];
    do {
        if (decList->get_nodes(0, 0)->nodes.size() == 1) {
            symbolTable[name] = new Type(name, CATEGORY::PRIMITIVE, _type);
        } else {
            symbolTable[name] = new Type(name, CATEGORY::ARRAY,
                                         getArrayFromVarDec(decList->get_nodes(0, 0),
                                                            new Type("", CATEGORY::PRIMITIVE, _type)));
        }
        if (decList->nodes.size() == 1) {
            break;
        }
        decList = decList->get_nodes(2);
        name = getStrValueFromDecList(decList);
    } while (true);
}

Array *getArrayFromVarDec(Node *node, Type *type) {
    if (node == nullptr || node->name != "VarDec") {
        return nullptr;
    } else {
        int size = std::get<int>(node->get_nodes(2)->value);
        //node->print();
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
    Node *decList = node->get_nodes(1);
    string variableName = getStrValueFromDecList(decList);
    string structName = std::get<string>(node->get_nodes(0, 0, 1)->value);
    if (symbolTable.count(structName) == 0) {
        //TODO error there
    } else {
        do {
            if (symbolTable.count(variableName) != 0) {
                //TODO
            }
            if (decList->get_nodes(0, 0)->nodes.size() == 1) {
                symbolTable[variableName] = symbolTable[structName];
                // struct Variable without array
            } else {
                // struct Variable with array
                symbolTable[variableName] = new Type(variableName, CATEGORY::ARRAY,
                                                     getArrayFromVarDec(decList->get_nodes(0, 0),
                                                                        symbolTable[structName]));
            }
            if (decList->nodes.size() == 1) {
                return;
            }
            decList = decList->get_nodes(2);
            variableName = getStrValueFromDecList(decList);
        } while (true);
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
        // global puretype variables
        extDefVisit_SES_PureType(node);
    } else {
        //global struct def and varis
        extDefVisit_SES_StructType(node);
        // inside is StructSpecifier
    }
    //node->print(0);
}

void extDefVisit_SES_PureType(Node *node) {
    Node *extDecList = node->get_nodes(1);
    string name = getStrValueFromExtDecList(extDecList);
    auto _type = snt[std::get<string>(node->get_nodes(0, 0)->value)];
    do {
        if (extDecList->get_nodes(0, 0)->nodes.empty()) {
            symbolTable[name] = new Type(name, CATEGORY::PRIMITIVE, _type);
        } else {
            symbolTable[name] = new Type(name, CATEGORY::ARRAY,
                                         getArrayFromVarDec(extDecList->get_nodes(0),
                                                            new Type("", CATEGORY::PRIMITIVE, _type)));
        }
        if (extDecList->nodes.size() == 1) {
            break;
        }
        extDecList = extDecList->get_nodes(2);
        name = getStrValueFromExtDecList(extDecList);
    } while (true);
}

void extDefVisit_SES_StructType(Node *node) {
    string structName = std::get<string>(node->get_nodes(0, 0, 1)->value);
    Node *extDefList = node->get_nodes(1);
    string variableName = getStrValueFromExtDecList(extDefList);
    extDefVisit_SS(node);
    if (symbolTable.count(variableName) != 0) {
        //TODO error type 3
    } else {
        do {
            if (extDefList->get_nodes(0)->nodes.size() == 1) {
                //Struct with variable definition
                symbolTable[variableName] = symbolTable[structName];
            } else {
                //Struct with variable definition - with Array
                symbolTable[variableName] = new Type(variableName, CATEGORY::ARRAY,
                                                     getArrayFromVarDec(extDefList->get_nodes(0),
                                                                        symbolTable[structName]));
            }
            if (extDefList->nodes.size() == 1) {
                return;
            }
            extDefList = extDefList->get_nodes(2);
            variableName = getStrValueFromExtDecList(extDefList);
        } while (true);
    }
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
    if (node->get_nodes(0, 0)->name == "TYPE") {
        // ignore the pureType's def likt `float;`
        return;
    }
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
    //node->print(0);
}

void extDefVisit_SFC(Node *node) {
    std::cout << "SFC\n";
    //node->print(0);
}

void expVisit(Node *node) {
    //node->print(0);
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