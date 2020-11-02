/*
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-10-30 11:00:26
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-11-02 12:04:39
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
    using JSONTYPES = variant<ObjectMember *, ArrayValue *, std::string, double, bool, void *>;

public:
    CATEGORY category;
    JSONTYPES value;

    explicit JsonObject(bool value);

    explicit JsonObject(std::string value);

    explicit JsonObject(double value);

    explicit JsonObject(void *value);

    explicit JsonObject(ArrayValue *value);

    explicit JsonObject(ObjectMember *value);

    void printInside(int space = 0) const;

    ~JsonObject() = default;

private:
    JsonObject(CATEGORY cate, JSONTYPES value);
};

class ObjectMember {
public:
    std::string key;
    JsonObject *value;
    ObjectMember *next;

    ObjectMember();

    ObjectMember(std::string key, JsonObject *value);

    void printInside(int space = 0) const;

    ~ObjectMember() = default;
};

class ArrayValue {
public:
    JsonObject *value;
    ArrayValue *next;

    ArrayValue();

    explicit ArrayValue(ArrayValue *next);

    ArrayValue(JsonObject *json, ArrayValue *next = nullptr);

    void printInside(int space = 0) const;

    ~ArrayValue() = default;
};

#endif  //! CS323_COMPLIERS_LAB07_OBJECT
