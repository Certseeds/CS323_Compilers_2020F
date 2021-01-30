/*
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-10-13 19:24:49
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-10-14 20:20:37
 */
#include <array>

#ifdef __cplusplus
extern "C" {
#endif

#include "symtab.h"

inline static constexpr int32_t TABLE_SIZE = 10007;
/*
 * symbol table type, binary tree impl
 */
struct symtab {
    entry entry{};
    symtab *left = nullptr, *right = nullptr;

    symtab() {
        memset(&this->entry, '\0', sizeof(this->entry));
    }

    symtab(char *const key, VAL_T value) {
        entry_init(&(this->entry), key, value);
    }
};
static std::array<symtab *, TABLE_SIZE> BFS_TABLE{nullptr,};
// ************************************************************
//    Your implementation goes here
// ************************************************************

symtab *symtab_init() {
    return new symtab();
}

// is exist return 0
// insert success return 1
int symtab_insert(symtab *const self, char *const key, VAL_T value) {
    memset(&BFS_TABLE, '\0', sizeof(BFS_TABLE));
    BFS_TABLE[0] = self;
    for (int begin = 0, last = 0; begin < TABLE_SIZE && begin <= last; begin++) {
        //printf("insert %d \n",begin);
        if (strcmp(BFS_TABLE[begin]->entry.key, key) == 0) {
            return 0;
        }
        if (BFS_TABLE[begin]->left != nullptr) {
            ++last;
            BFS_TABLE[last] = BFS_TABLE[begin]->left;
        } else {
            BFS_TABLE[begin]->left = new symtab(key, value);
            //printf("insert left %d \n",last);
            return 1;
        }
        if (BFS_TABLE[begin]->right != nullptr) {
            ++last;
            BFS_TABLE[last] = BFS_TABLE[begin]->right;
        } else {
            BFS_TABLE[begin]->right = new symtab(key, value);
            //printf("insert right %d \n",last);
            return 1;
        }
    }
    return -1;
}

VAL_T symtab_lookup(symtab *const self,char * const key) {
    memset(&BFS_TABLE, '\0', sizeof(BFS_TABLE));
    BFS_TABLE[0] = self;
    for (int begin = 0, last = 0; begin < TABLE_SIZE && begin <= last; ++begin) {
        //printf("%d\n",begin);
        if (strcmp(BFS_TABLE[begin]->entry.key, key) == 0) {
            return BFS_TABLE[begin]->entry.value;
        }
        if (BFS_TABLE[begin]->left != nullptr) {
            ++last;
            BFS_TABLE[last] = BFS_TABLE[begin]->left;
        }
        if (BFS_TABLE[begin]->right != nullptr) {
            ++last;
            BFS_TABLE[last] = BFS_TABLE[begin]->right;
        }
    }
    return -1;
}

int symtab_remove(symtab *const self, char * const key) {
    memset(&BFS_TABLE, '\0', sizeof(BFS_TABLE));
    BFS_TABLE[0] = self;
    int last = 0;
    int sign = -1;// the tag's sign
    for (int begin = 0; begin < TABLE_SIZE && begin <= last; begin++) {
        if (BFS_TABLE[begin]->left != nullptr) {
            ++last;
            if (strcmp(BFS_TABLE[begin]->left->entry.key, key) == 0) {
                sign = last;
            }
            BFS_TABLE[last] = BFS_TABLE[begin]->left;
        }
        if (BFS_TABLE[begin]->right != nullptr) {
            ++last;
            if (strcmp(BFS_TABLE[begin]->right->entry.key, key) == 0) {
                sign = last;
            }
            BFS_TABLE[last] = BFS_TABLE[begin]->right;
        }
    }
    if (sign != -1) {
        auto *const temp = BFS_TABLE[sign];
        BFS_TABLE[sign] = BFS_TABLE[last];
        delete temp;
        return 1;
    }
    return 0;
}

#ifdef __cplusplus
}
#endif