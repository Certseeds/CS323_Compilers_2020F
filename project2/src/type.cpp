//
// Created by nanos on 2020/11/7.
//

#include "type.hpp"

#include <utility>


Type::Type(string _name, CATEGORY _category, Type::PRIMI _type) :
        name(std::move(_name)),
        category(_category),
        type(std::move(_type)) {
}

Type::Type(bool _isFunction) : isFunction(_isFunction) {
    //parms = vector<Type *>(0);
}

Array::Array(Type *base, int size) : base(base), size(size) {}

FieldList::FieldList(string name, Type *type, FieldList *next) : name(std::move(name)), type(type), next(next) {}
