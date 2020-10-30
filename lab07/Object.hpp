/*
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-10-30 11:00:26
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-10-30 22:27:23
 */
#ifndef CS323_COMPLIERS_LAB07_OBJECT
#define CS323_COMPLIERS_LAB07_OBJECT

#include <iostream>
#include <map>
#include <string>
#include <variant>

using std::cout;
using std::endl;
using std::string;
using std::variant;
enum class CATEGORY {
    OBJECT = 1,
    ARRAY = 2,
    STRING = 3,
    NUMBER = 4,
    BOOLEAN = 5,
    VNULL = 6
};
const static std::map <CATEGORY, std::string> printCate{
        {CATEGORY::OBJECT,  "OBJECT"},
        {CATEGORY::ARRAY,   "ARRAY"},
        {CATEGORY::STRING,  "STRING"},
        {CATEGORY::NUMBER,  "NUMBER"},
        {CATEGORY::BOOLEAN, "BOOLEAN"},
        {CATEGORY::VNULL,   "VNULL"},
};

class ObjectMember;

class ArrayValue;

class JsonObject {
public:
    CATEGORY category;
    variant<ObjectMember *, ArrayValue *, std::string, double, bool, void *> value;

    explicit JsonObject(bool value);

    explicit JsonObject(std::string value);

    explicit JsonObject(double value);

    explicit JsonObject(void *value);

    explicit JsonObject(ArrayValue *value);

    explicit JsonObject(ObjectMember *value);

    void printInside(int space = 0) const;
};

class ObjectMember {
public:
    std::string key;
    JsonObject *value;
    ObjectMember *next;

    ObjectMember();

    ObjectMember(std::string key,JsonObject* value);

    void printInside(int space = 0) const;
};

class ArrayValue {
public:
    JsonObject *value;
    ArrayValue *next;

    ArrayValue();

    explicit ArrayValue(ArrayValue *next);

    explicit ArrayValue(JsonObject *json);

    ArrayValue(JsonObject *json, ArrayValue *next);

    void printInside(int space = 0) const;
};

#endif  //! CS323_COMPLIERS_LAB07_OBJECT
