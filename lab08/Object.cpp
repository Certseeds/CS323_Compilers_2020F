/*
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-10-30 11:21:26
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-11-03 20:41:04
 */
#include "Object.hpp"

JsonObject::JsonObject(bool value) : JsonObject(CATEGORY::BOOLEAN, value) {}

JsonObject::JsonObject(std::string value) : JsonObject(CATEGORY::STRING, value) {}

JsonObject::JsonObject(double value) : JsonObject(CATEGORY::NUMBER, value) {}

JsonObject::JsonObject(void *value) : JsonObject(CATEGORY::VNULL, value) {}

JsonObject::JsonObject(ArrayValue *value) : JsonObject(CATEGORY::ARRAY, value) {}

JsonObject::JsonObject(ObjectMember *value) : JsonObject(CATEGORY::OBJECT, value) {}

JsonObject::JsonObject(CATEGORY cate, JSONTYPES value) : category(cate), value(value) {}

void JsonObject::printInside(int space) const {
    // std::cout << std::string(space, ' ') << "Type: " << printCate.at(this->category) << '\n';
    // std::cout << std::string(space, ' ') << "Value: ";
    switch (this->category) {
        case CATEGORY::STRING: {
            std::cout <<R"(")" << std::get<string>(this->value) << R"(")";
            break;
        }
        case CATEGORY::NUMBER: {
            std::cout << std::get<double>(this->value) ;
            break;
        }
        case CATEGORY::BOOLEAN: {
            std::cout << (std::get<bool>(this->value) ? "true" : "false");
            break;
        }
        case CATEGORY::VNULL: {
            std::cout << "null";
            break;
        }
        case CATEGORY::OBJECT: {
            std::cout << "{";
            const auto next = std::get<ObjectMember *>(this->value);
            if (next != nullptr) {
                next->printInside(space + 2);
            }
            std::cout << "}\n";
            break;
        }
        case CATEGORY::ARRAY: {
            std::cout << "[\n";
            const auto next = std::get<ArrayValue *>(this->value);
            if (next != nullptr) {
                next->printInside(space + 2);
            }
            std::cout << "]\n";
            break;
        }
        default:
            break;
    }
}

ObjectMember::ObjectMember() : ObjectMember("", nullptr) {}

ObjectMember::ObjectMember(std::string key, JsonObject *value) : key(key), value(value), next(nullptr) {}

void ObjectMember::printInside(int space) const {
    std::cout << R"(")" << this->key << R"(")" << ':';
    this->value->printInside(space + 2);
    if (next != nullptr) {
        std::cout << ",";
        this->next->printInside(space);
    }
}

ArrayValue::ArrayValue() : ArrayValue(nullptr, nullptr) {}

ArrayValue::ArrayValue(ArrayValue *next) : ArrayValue(nullptr, next) {}

ArrayValue::ArrayValue(JsonObject *json, ArrayValue *next) : value(json), next(next) {}

void ArrayValue::printInside(int space) const {
    this->value->printInside(space + 2);
    if (next != nullptr) {
        std::cout << ",";
        this->next->printInside(space);
    }
}
