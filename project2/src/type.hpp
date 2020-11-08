//
// Created by nanos on 2020/11/7.
//

#ifndef CS323_COMPLIERS_TYPE_HPP
#define CS323_COMPLIERS_TYPE_HPP

#include <string>
#include <variant>
#include <vector>
#include "node.hpp"

using std::string;
using std::variant;
using std::vector;

enum class CATEGORY {
    PRIMITIVE, ARRAY, STRUCTURE
};

class Array;

class FieldList;

class Type {
    using PRIMI = variant<Node_TYPE, Array *, FieldList *>;
public:
    string name;
    CATEGORY category;
    PRIMI type;
    vector<Type *> parms = vector<Type *>(0);

    Type() = default;

    Type(string _name, CATEGORY _category, PRIMI _type);

};

class Array {
public:
    Type *base;
    int size;

    Array(Type *base, int size);
};

class FieldList {
public:
    string name;
    Type *type;
    FieldList *next;

    FieldList(string name, Type *type, FieldList *next);

};

#endif //CS323_COMPLIERS_TYPE_HPP
