/*
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-10-30 11:21:26
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-10-30 22:33:04
 */
#include "Object.hpp"

JsonObject::JsonObject(bool value) : category(CATEGORY::BOOLEAN), value(value) {}

JsonObject::JsonObject(std::string value) : category(CATEGORY::STRING), value(value) {}

JsonObject::JsonObject(double value) : category(CATEGORY::NUMBER), value(value) {}

JsonObject::JsonObject(void *value) : category(CATEGORY::VNULL), value(value) {}

JsonObject::JsonObject(ArrayValue *value) : category(CATEGORY::ARRAY), value(value) {}

JsonObject::JsonObject(ObjectMember *value) : category(CATEGORY::OBJECT), value(value) {}

void JsonObject::printInside(int space) const {
    std::cout << std::string(space, ' ') << "Type: " << printCate.at(this->category) << '\n';
    std::cout << std::string(space, ' ') << "Value: ";
    switch (this->category) {
        case CATEGORY::STRING: {
            std::cout << std::get<string>(this->value) << '\n';
            break;
        }
        case CATEGORY::NUMBER: {
            std::cout << std::get<double>(this->value) << '\n';
            break;
        }
        case CATEGORY::BOOLEAN: {
            std::cout << (std::get<bool>(this->value) ? "true" : "false") << '\n';
            break;
        }
        case CATEGORY::VNULL: {
            std::cout << "Nullptr\n";
            break;
        }
        case CATEGORY::OBJECT: {
            std::cout << " Object\n";
            const auto next = std::get<ObjectMember *>(this->value);
            if (next != nullptr) {
                next->printInside(space + 2);
            }
            break;
        }
        case CATEGORY::ARRAY: {
            std::cout << " Array \n";
            const auto next = std::get<ArrayValue *>(this->value);
            if (next != nullptr) {
                next->printInside(space + 2);
            }
            break;
        }
        default:
            break;
    }
}

ObjectMember::ObjectMember() : value(nullptr), next(nullptr) {}

ObjectMember::ObjectMember(std::string key, JsonObject *value) : key(key), value(value), next(nullptr) {}

void ObjectMember::printInside(int space) const {
    std::cout << std::string(space, ' ') << "Type: ObjectMember \n";
    std::cout << std::string(space, ' ') << "Key: " << this->key << '\n';
    this->value->printInside(space + 2);
    if (next != nullptr) {
        this->next->printInside(space);
    }
}

ArrayValue::ArrayValue() : value(nullptr), next(nullptr) {}

ArrayValue::ArrayValue(JsonObject *json, ArrayValue *next) : value(json), next(next) {}

ArrayValue::ArrayValue(JsonObject *json) : value(json), next(nullptr) {}

ArrayValue::ArrayValue(ArrayValue *next) : next(next) {}

void ArrayValue::printInside(int space) const {
    std::cout << std::string(space, ' ') << "Type: ArrayValue\n";
    this->value->printInside(space + 2);
    if (next != nullptr) {
        this->next->printInside(space);
    }
}
