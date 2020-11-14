//
// Created by nanos on 2020/11/7.
//

#include "visitSyntaxTree.hpp"
#include "semanticError.hpp"

static unordered_map<string, Node_TYPE> snt = {
        {string("int"),   Node_TYPE::INT},
        {string("float"), Node_TYPE::FLOAT},
        {string("char"),  Node_TYPE::CHAR},
};
static unordered_map<Node_TYPE, string> tns = {
        {Node_TYPE::INT,   string("int")},
        {Node_TYPE::FLOAT, string("float")},
        {Node_TYPE::CHAR,  string("char")},
};

string categoryAndTypeNameFromType(Type *type) {
    static const unordered_map<CATEGORY, string> ca_st = {
            {CATEGORY::PRIMITIVE, ""},
            {CATEGORY::ARRAY,     "array"},
            {CATEGORY::STRUCTURE, "struct"},
            {CATEGORY::FUNCTION,  "function"}
    };
    const string &categoryStr = ca_st.at(type->category);
    string typeName;
    switch (type->category) {
        case CATEGORY::PRIMITIVE: {
            typeName = tns[std::get<Node_TYPE>(type->type)];
            break;
        }
        case CATEGORY::ARRAY:
        case CATEGORY::STRUCTURE:
        case CATEGORY::FUNCTION: {
            typeName = symbolTable[type->name]->name;
            break;
        }
    }
    return string("").append(categoryStr).append(" ").append(typeName);
}

void idToExp(Node *exp, Node *id) {
    if (exp->name != "Exp" || id->name != "ID") {
        return;
    }
    exp->type = symbolTable[std::get<string>(id->value)];
}

void defStructTypeVisit(Node *node);

void defPureTypeVisit(Node *node);

string getStrValueFromDecList(Node *node);

void defStructDefinition(Node *node);

void defStructObjectDefinition(Node *node);

FieldList *getFiledListFromDefList(Node *node);

void extDefVisit_SES_PureType(Node *node);

void extDefVisit_SES_StructType(Node *node);

Array *getArrayFromVarDec(Node *node, Type *type);

/*
 * When Bison detect a Def, enter this function
 * */
void defVisit(Node *node) {
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

void defPureTypeVisit(Node *node) {
    Node *decList = node->get_nodes(1);
    string name = getStrValueFromDecList(decList);
    auto _type = snt[std::get<string>(node->get_nodes(0, 0)->value)];
    do {
        if (symbolTable.count(name) != 0) {
            variableRedefined(std::get<int>(node->value), name);
        }
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
    Node *decList = node->get_nodes(1);
    string variableName = getStrValueFromDecList(decList);
    string structName = std::get<string>(node->get_nodes(0, 0, 1)->value);
    if (symbolTable.count(structName) == 0) {
        //TODO error there
        // WHICH ERROR DID it belong to ?
    } else {
        do {
            if (symbolTable.count(variableName) != 0) {
                variableRedefined(std::get<int>(node->value), variableName);
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

Array *getArrayFromVarDec(Node *node, Type *type) {
    if (node == nullptr || node->name != "VarDec") {
        return nullptr;
    } else {
        int size = std::get<int>(node->get_nodes(2)->value);
#ifdef DEBUG
        node->print();
#endif
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
ExtDef
  Specifier // this can be type or structSpecifier
    TYPE: int
  ExtDecList
    VarDec
      ID: global
  SEMI*/

void extDefVisit_SES(Node *node) {
    //std::cout << "SES\n";
    if (node->get_nodes(0, 0)->nodes.empty()) {
        // global puretype variables
        extDefVisit_SES_PureType(node);
    } else {
        //global struct def and varis
        extDefVisit_SES_StructType(node);
        // inside is StructSpecifier
    }
#ifdef DEBUG
    node->print(0);
#endif
}

void extDefVisit_SES_PureType(Node *node) {
    Node *extDecList = node->get_nodes(1);
    string name = getStrValueFromExtDecList(extDecList);
    auto _type = snt[std::get<string>(node->get_nodes(0, 0)->value)];
    do {
        if (symbolTable.count(name) != 0) {
            variableRedefined(std::get<int>(node->value), name);
        }
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
    if (symbolTable.count(structName) != 0) {
        structRedefined(std::get<int>(node->value), structName);
    } else {
        do {
            if (symbolTable.count(variableName) != 0) {
                variableRedefined(std::get<int>(node->value), variableName);
            }
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
    // definition of Struct
    //std::cout << "SS\n";
    if (node->get_nodes(0, 0)->name == "TYPE") {
        // ignore the pureType's def likt `float;`
        return;
    }
    string name = std::get<string>(node->get_nodes(0, 0, 1)->value); // this is structName
    if (symbolTable.count(name) != 0) {
        structRedefined(std::get<int>(node->value), name);
    } else {
        if (node->get_nodes(0, 0, 3)->nodes.empty()) {
            symbolTable[name] = new Type(name, CATEGORY::STRUCTURE, static_cast<FieldList *>(nullptr));
            return;
        } else {
            symbolTable[name] = new Type(name, CATEGORY::STRUCTURE, getFiledListFromDefList(node->get_nodes(0, 0, 3)));
        }
    }
#ifdef DEBUG
    node->print(0);
#endif
}

// input is a Specifier Node
// Return is its Type's string
Type *getSpecifierType(Node *node) {
    if (node->name != "Specifier") {
        return nullptr;
    }
    if (node->get_nodes(0)->nodes.empty()) {
        return new Type(std::get<string>(node->get_nodes(0)->value), CATEGORY::PRIMITIVE,
                        snt[std::get<string>(node->get_nodes(0)->value)]);
    } else {
        return symbolTable[std::get<string>(node->get_nodes(0, 1)->value)];
    }
}

void extDefVisit_SFC(Node *node) {
    Type *functionType = new Type();
    Node *specifier = node->get_nodes(0);
    auto specifierType = getSpecifierType(specifier);
    functionType->category = CATEGORY::FUNCTION;
    functionType->returnType = specifierType;
    functionType->name = std::get<string>(node->get_nodes(1, 0)->value);
    if (symbolTable.count(functionType->name) != 0) {
        functionRedefined(std::get<int>(node->value), functionType->name);
        return;
    } else {
        if (node->get_nodes(1)->nodes.size() != 4) {
            // no need to put anything
            functionType->type = static_cast<FieldList *>(nullptr);
        } else {
            Node *funDec = node->get_nodes(1);
            Node *varList = funDec->get_nodes(2);
            FieldList fieldList;
            fieldList.next = new FieldList();
            FieldList *fieldListPtr = fieldList.next;
            functionType->type = fieldList.next;
            do {
                string paramName = std::get<string>(varList->get_nodes(0, 1, 0)->value);
                fieldListPtr->name = paramName;
                fieldListPtr->type = symbolTable[paramName];
                if (varList->nodes.size() == 1) {
                    break;
                }
                varList = varList->get_nodes(2);
                fieldListPtr->next = new FieldList();
                fieldListPtr = fieldListPtr->next;
            } while (true);
        }
    }
    symbolTable[functionType->name] = functionType;
    //std::cout << "SFC\n";
#ifdef DEBUG
    node->print(0);
#endif
}

void expVisit(Node *node) {
#ifdef DEBUG
    node->print(0);
#endif
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

void checkRvalueInLeftSide(Node *node) {
    if (node->name != "Exp") {
        // error
    }
    Node *leftExpNode = node->get_nodes(0);
    switch (leftExpNode->nodes.size()) {
        case 1: {
            if (leftExpNode->get_nodes(0)->name == "ID") { return; }
            break;
        }
        case 3: {
            if (leftExpNode->get_nodes(0)->name == "Exp" && leftExpNode->get_nodes(2)->name == "ID" &&
                leftExpNode->get_nodes(1)->name == "DOT") { return; }
            break;
        }
        case 4: {
            if (leftExpNode->get_nodes(0)->name == "Exp" && leftExpNode->get_nodes(2)->name == "Exp" &&
                leftExpNode->get_nodes(1)->name == "LB" && leftExpNode->get_nodes(3)->name == "RB") { return; }
            break;
        }
    }
    rvalueLeftSetError(std::get<int>(node->value));

}

void checkIdExists(Node *node, int lineNum) {
    if (node->name != "ID") {
        return;
    }
    string idName = std::get<string>(node->value);
    if (symbolTable.count(idName) == 0) {
        variableNoDefinition(lineNum, idName);
    }
}

void funDecVisit(Node *node) {
    if (node->nodes.size() == 3) {
        return;
    }
    Node *varList = node->get_nodes(2);
    do {
        Node *specifier = varList->get_nodes(0, 0);
        auto specifierType = getSpecifierType(specifier);
        string paramName = std::get<string>(varList->get_nodes(0, 1, 0)->value);
        if (symbolTable.count(paramName) != 0) {
            variableRedefined(std::get<int>(varList->value), paramName);
        }
        if (specifierType->category == CATEGORY::PRIMITIVE) {
            specifierType->name = paramName;
        }
        symbolTable[paramName] = specifierType;
        if (varList->nodes.size() == 1) {
            break;
        }
        varList = varList->get_nodes(2);
    } while (true);
}

void checkNoSuchMember(Node *node) {
    /* Exp
     *   Exp
     *   DOT
     *   ID
     */
    if (node->name != "Exp") {
        return;
    }
    if (node->get_nodes(0)->type == nullptr) {
        return;
    }
    if (node->get_nodes(0)->type->category != CATEGORY::STRUCTURE) {
        nonStructFVariable(std::get<int>(node->value));
    }
}

void searchAndPutTypeOfDot(Node *expOut, Node *expIn, Node *ID) {
    if (expIn->type == nullptr) {
        nonStructFVariable(std::get<int>(expIn->value));
        return;
    }
    if (expIn->type->type.index() != 2) {
        return;
    }
    FieldList *fieldList = std::get<FieldList *>(expIn->type->type);
    string idName = std::get<string>(ID->value);
    while (fieldList != nullptr) {
        if (fieldList->name == idName) {
            expOut->type = symbolTable[idName];
            return;
        }
        fieldList = fieldList->next;
    }
    noSuchMember(std::get<int>(expOut->value), idName);
}


void checkInvokeExist(Node *node, int lineNum) {
    string functionName = std::get<string>(node->value);
    if (symbolTable.count(functionName) == 0) {
        functionNoDefinition(lineNum, functionName);
    } else if (symbolTable[functionName]->category != CATEGORY::FUNCTION) {
        invokeNonFunctionVariable(lineNum, functionName);
    }
}

void getReturnTypeOfFunction(Node *expOut, Node *ID) {
    string functionName = std::get<string>(ID->value);
    if (symbolTable.count(functionName) == 0 || symbolTable[functionName]->category != CATEGORY::FUNCTION) {
        return;
    }
    Type *returnType = symbolTable[functionName]->returnType;
    expOut->type = returnType;
}

void checkFunctionParams(Node *ID, Node *args, int lineNum) {
    string functionName = std::get<string>(ID->value);
    if (symbolTable.count(functionName) == 0 || symbolTable[functionName]->category != CATEGORY::FUNCTION) {
        return;
    }
    Type *functionType = symbolTable[functionName];
    FieldList *fieldList = functionType->type.index() == 0 ? nullptr : std::get<FieldList *>(functionType->type);
    if (args == nullptr) {
        if (fieldList == nullptr) {
            return;
        } else {
            int except = 1;
            while (fieldList->next != nullptr) {
                fieldList = fieldList->next;
                except++;
            }
            invalidArgumentNumber(lineNum, functionName, except, 0);
        }
    } else {
        if (fieldList == nullptr) {
            // check args的参数数量
            int actually = 1;
            Node *tempArgs = args;
            while (tempArgs->nodes.size() != 1) {
                tempArgs = tempArgs->get_nodes(2);
                actually++;
            }
            invalidArgumentNumber(lineNum, functionName, 0, actually);
            return;
        } else {
            // both check args, but check fieldList
            int except = 1;
            int actually = 1;
            {
                FieldList *tempFieldList = std::get<FieldList *>(functionType->type);
                while (tempFieldList->next != nullptr) {
                    tempFieldList = tempFieldList->next;
                    except++;
                }
            }
            {
                Node *tempArgs = args;
                while (tempArgs->nodes.size() != 1) {
                    tempArgs = tempArgs->get_nodes(2);
                    actually++;
                }
            }
            if (except != actually) {
                invalidArgumentNumber(lineNum, functionName, except, actually);
            }
            int count = 0;
            while (count < std::min(except, actually)) {
                count++;
                Type *filed = fieldList->type;
                string argsName;
                if (args->get_nodes(0, 0)->value.index() != 0) {
                    if (filed->category != CATEGORY::PRIMITIVE ||
                        std::get<Node_TYPE>(filed->type) != args->get_nodes(0, 0)->TYPE) {
                        invalidArgumentType(lineNum, functionName, categoryAndTypeNameFromType(filed),
                                            tns[args->get_nodes(0, 0)->TYPE]);
                    }
                } else {
                    argsName = std::get<string>(args->get_nodes(0, 0)->value);
                }
                if (symbolTable.count(argsName) == 0) {
                    continue;
                } else {
                    Type *argsType = symbolTable[argsName];
                    if (filed->category != argsType->category) {
                        invalidArgumentType(lineNum, functionName, categoryAndTypeNameFromType(filed),
                                            categoryAndTypeNameFromType(argsType));
                    } else if (filed->category == CATEGORY::PRIMITIVE &&
                               std::get<Node_TYPE>(filed->type) != std::get<Node_TYPE>(argsType->type)) {
                        invalidArgumentType(lineNum, functionName, categoryAndTypeNameFromType(filed),
                                            categoryAndTypeNameFromType(argsType));
                    } else if (filed->category == CATEGORY::STRUCTURE && filed->name != argsType->name) {
                        invalidArgumentType(lineNum, functionName, categoryAndTypeNameFromType(filed),
                                            categoryAndTypeNameFromType(argsType));
                    } else if (filed->category == CATEGORY::ARRAY) {
                        int levelField = 1;
                        int levelArgs = 1;
                        Type *baseTypeOfField;
                        Type *baseTypeOfArgs;
                        {
                            Type *tempField = filed;
                            while (tempField != nullptr && tempField->type.index() == 1) {
                                tempField = std::get<Array *>(tempField->type)->base;
                                levelField++;
                            }
                            baseTypeOfField = tempField;
                        }
                        {
                            Type *tempArgs = argsType;
                            while (tempArgs != nullptr && tempArgs->type.index() == 1) {
                                tempArgs = std::get<Array *>(tempArgs->type)->base;
                                levelArgs++;
                            }
                            baseTypeOfArgs = tempArgs;
                        }
                        if (levelArgs != levelField || baseTypeOfArgs->category != baseTypeOfField->category) {
                            invalidArgumentType(lineNum, functionName, categoryAndTypeNameFromType(filed),
                                                categoryAndTypeNameFromType(argsType));
                        } else if (baseTypeOfField->category == CATEGORY::PRIMITIVE) {
                            if (std::get<Node_TYPE>(baseTypeOfField->type) !=
                                std::get<Node_TYPE>(baseTypeOfArgs->type)) {
                                invalidArgumentType(lineNum, functionName, categoryAndTypeNameFromType(filed),
                                                    categoryAndTypeNameFromType(argsType));
                            }
                        } else if (baseTypeOfField->category == CATEGORY::STRUCTURE) {
                            if (baseTypeOfArgs->name != baseTypeOfField->name) {
                                invalidArgumentType(lineNum, functionName, categoryAndTypeNameFromType(filed),
                                                    categoryAndTypeNameFromType(argsType));
                            }
                        }
                    }
                }
                fieldList = fieldList->next;
                args = args->get_nodes(2);
            }
        }
    }

}

void checkArrayExists(Node *Exp) {
    Node *temp = Exp;
    if (Exp->nodes.size() == 1) {
        string arrayName = std::get<string>(Exp->get_nodes(0)->value);
        if (symbolTable.count(arrayName) != 0) {
            Type *arrayType = symbolTable[arrayName];
            if (arrayType->category != CATEGORY::ARRAY) {
                indexOnNonArray(std::get<int>(Exp->value));
            }
        } else {
            indexOnNonArray(std::get<int>(Exp->value));
        }
    } else {
        //
        Type *arrayType = Exp->type;
        if (arrayType == nullptr || arrayType->category != CATEGORY::ARRAY) {
            indexOnNonArray(std::get<int>(Exp->value));
        }
    }
}

void checkIntegerExp(Node *Exp) {
    if (Exp->type == nullptr) {
        nonIntegerTypeIndexing(std::get<int>(Exp->value));
        return;
    }
    if (Exp->type->category != CATEGORY::PRIMITIVE || std::get<Node_TYPE>(Exp->type->type) != Node_TYPE::INT) {
        nonIntegerTypeIndexing(std::get<int>(Exp->value));
    }
}

void getArrayType(Node *expOut, Node *expIn) {
    if (expOut->nodes.size() == 1) {
        string arrayName = std::get<string>(expOut->get_nodes(0)->value);
        if (symbolTable.count(arrayName) != 0) {
            Type *arrayType = symbolTable[arrayName];
            if (arrayType->category == CATEGORY::ARRAY) {
                expOut->type = arrayType;
            }
        } else {
        }
    } else {
        //
        Type *arrayType = expIn->type;
        if (arrayType == nullptr) {
            expOut->type = static_cast<Type *>( nullptr);
            return;
        }
        if (arrayType->category == CATEGORY::ARRAY) {
            expOut->type = std::get<Array *>(arrayType->type)->base;
        }
    }
}


bool checkBoolOperatorType(Node *exp) {
    if (exp->type == nullptr) {
        binaryOperatorNonNumber(std::get<int>(exp->value));
        return false;
    }
    if (exp->type->category != CATEGORY::PRIMITIVE || std::get<Node_TYPE>(exp->type->type) != Node_TYPE::INT) {
        binaryOperatorNonNumber(std::get<int>(exp->value));
        return false;
    }
    return true;
}

void getBoolOperatorType(Node *expOut, Node *expIn1, Node *expIn2) {
    bool check1 = checkBoolOperatorType(expIn1);
    bool check2 = checkBoolOperatorType(expIn2);
    if (check1 && check2) {
        expOut->type = new Type("INT", CATEGORY::PRIMITIVE, Node_TYPE::INT);
    }
}

Node_TYPE checkAlrthOperatorType(Node *exp) {
    if (exp->type == nullptr) {
        binaryOperatorNonNumber(std::get<int>(exp->value));
        return Node_TYPE::LINE;
    }
    if (exp->type->category != CATEGORY::PRIMITIVE ||
        (std::get<Node_TYPE>(exp->type->type) != Node_TYPE::INT &&
         std::get<Node_TYPE>(exp->type->type) != Node_TYPE::FLOAT)) {
        binaryOperatorNonNumber(std::get<int>(exp->value));
        return Node_TYPE::LINE;
    }
    return std::get<Node_TYPE>(exp->type->type);
}

void getAlrthOperatorType(Node *expOut, Node *expIn1, Node *expIn2) {
    auto check1 = checkAlrthOperatorType(expIn1);
    auto check2 = checkAlrthOperatorType(expIn2);

    if (check1 == Node_TYPE::LINE || check2 == Node_TYPE::LINE) {
    } else if (check1 == Node_TYPE::FLOAT || check2 == Node_TYPE::FLOAT) {
        expOut->type = new Type("float", CATEGORY::PRIMITIVE, Node_TYPE::FLOAT);
    } else {
        expOut->type = new Type("int", CATEGORY::PRIMITIVE, Node_TYPE::INT);
    }
}
