//
// Created by nanos on 2020/11/7.
//

#include "type.hpp"


Type::Type(string _name, CATEGORY _category, Type::PRIMI _type) :
        name(std::move(_name)),
        category(_category),
        type(std::move(_type)) {
}

#define getPrimitive(TYPE) \
Type *Type::getPrimitive##TYPE() {\
    static auto will_return = new Type{#TYPE, CATEGORY::PRIMITIVE, Node_TYPE::TYPE};\
    return will_return;\
}
getPrimitive(INT);

getPrimitive(CHAR);

getPrimitive(FLOAT);

#undef getPrimitive

Type *Type::getPrimitiveType(Node_TYPE type) {
    switch (type) {
        case Node_TYPE::INT : {
            return Type::getPrimitiveINT();
        }
        case Node_TYPE::FLOAT : {
            return Type::getPrimitiveFLOAT();
        }
        case Node_TYPE::CHAR : {
            return Type::getPrimitiveCHAR();
        }
        default: {
        }
    }
}

Array::Array(Type *base, int size) : base(base), size(size) {}

FieldList::FieldList(string name, Type *type, FieldList *next) : name(std::move(name)), type(type), next(next) {}
