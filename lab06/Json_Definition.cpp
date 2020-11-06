/*
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-10-24 11:53:04
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-10-24 13:03:04
 */
/**
 * Exercise
 * • JSON object
 * Write a struct definition of a JSON object.
 * You may refer to project 2 doc, Listing 2.
**/
// because default use c so use a macro to set the maximum size of name.
// this can descripe the definition of a json object.
/** for a json object that only have STRING,NUMBER,TRUE,FALSE,VNULL
  THE struct is only a TYPE struct without any sub-sturct.
  which means in union it set to primitive.
  in the first union, it can set the primitive's values.
**/
/**
 * for a json object which is a Array,
 * outer is A type,which inside have a ARRAYLIST's pointer.
 * in ARRAYLIST's pointer, it just have a type and a next pointer.
*/
/**
 * for a json object which is a object,
 * outer is A type,which inside have a KVlist's pointer.
 * in KVlist's pointer, it just have a string-value pair, and the next pointer.
*/
#define NAME_MAX_LENGTH 32

typedef struct Type {
    union {
        char STRING_VALUE[NAME_MAX_LENGTH];
        double NUMBER_VALUE;
        bool TRUE_VALUE;
        bool FALSE_VALUE;
        void *VNULL_VALUE;
    };  // i dont know the struct need or not store the value's in json object
    // if just need to stroe the struct or type, this union do not need to set.
    // if need to store the details of each primitice element, it can be set.
    enum {
        OBJECT,
        ARRAY,
        PRIMITIVE
    } category;
    union {
        enum {
            STRING,
            NUMBER,
            TRUE,
            FALSE,
            VNULL
        } primitive;
        struct ArrayList *ARRAYLIST;
        struct KVList *OBJECTLIST;
    };
} Type;
typedef struct ArrayList {
    struct Type *TYPE;  //json's array do not need all element have same type
    struct ArrayList *next;
} ArrayList;
typedef struct Key_value {
    struct Type *STRING_KEY_TYPE;  // this one is always STRING
    struct Type *VALUE_type;       // this is just any TYPE
} Key_value;
typedef struct KVList {
    struct Key_value *KEY_VALUE;
    struct KVList *next;
} KVList;