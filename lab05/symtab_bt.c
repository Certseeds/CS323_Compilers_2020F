/*
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-10-13 19:24:49
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-10-14 20:20:37
 */
#include "symtab.h"

#define TABLESIZE 10007
/*
 * symbol table type, binary tree impl
 */
struct symtab {
    entry entry;
    struct symtab *left, *right;
};
struct symtab *BFS_TABLE[TABLESIZE];

// ************************************************************
//    Your implementation goes here
// ************************************************************
symtab *symtab_init_parm(char *key, VAL_T value) {
    symtab *self = (symtab *) malloc(sizeof(symtab));
    memset(self, '\0', sizeof(symtab));
    entry_init(&(self->entry), key, value);
    self->left = NULL;
    self->right = NULL;
    return self;
}

symtab *symtab_init() {
    symtab *self = (symtab *) malloc(sizeof(symtab));
    memset(self, '\0', sizeof(symtab));
    self->left = NULL;
    self->right = NULL;
    return self;
}


// is exist return 0
// insert success return 1
int symtab_insert(symtab *self, char *key, VAL_T value) {
    memset(BFS_TABLE, '\0', sizeof(BFS_TABLE));
    BFS_TABLE[0] = self;
    for (int begin = 0, last = 0; begin < TABLESIZE && begin <= last; begin++) {
        //printf("insert %d \n",begin);
        if (strcmp(BFS_TABLE[begin]->entry.key, key) == 0) {
            return 0;
        }
        if (BFS_TABLE[begin]->left != NULL) {
            ++last;
            BFS_TABLE[last] = BFS_TABLE[begin]->left;
        } else {
            BFS_TABLE[begin]->left = symtab_init_parm(key, value);
            //printf("insert left %d \n",last);
            return 1;
        }
        if (BFS_TABLE[begin]->right != NULL) {
            ++last;
            BFS_TABLE[last] = BFS_TABLE[begin]->right;
        } else {
            BFS_TABLE[begin]->right = symtab_init_parm(key, value);
            //printf("insert right %d \n",last);
            return 1;
        }
    }
    return -1;
}

VAL_T symtab_lookup(symtab *self, char *key) {
    memset(BFS_TABLE, '\0', sizeof(BFS_TABLE));
    BFS_TABLE[0] = self;
    for (int begin = 0, last = 0; begin < TABLESIZE && begin <= last; ++begin) {
        //printf("%d\n",begin);
        if (strcmp(BFS_TABLE[begin]->entry.key, key) == 0) {
            return BFS_TABLE[begin]->entry.value;
        }
        if (BFS_TABLE[begin]->left != NULL) {
            ++last;
            BFS_TABLE[last] = BFS_TABLE[begin]->left;
        }
        if (BFS_TABLE[begin]->right != NULL) {
            ++last;
            BFS_TABLE[last] = BFS_TABLE[begin]->right;
        }
    }
    return -1;
}

int symtab_remove(symtab *self, char *key) {
    memset(BFS_TABLE, '\0', sizeof(BFS_TABLE));
    BFS_TABLE[0] = self;
    int last = 0;
    int sign = -1;// the tag's sign
    for (int begin = 0; begin < TABLESIZE && begin <= last; begin++) {
        if (BFS_TABLE[begin]->left != NULL) {
            ++last;
            if (strcmp(BFS_TABLE[begin]->left->entry.key, key) == 0) {
                sign = last;
            }
            BFS_TABLE[last] = BFS_TABLE[begin]->left;
        }
        if (BFS_TABLE[begin]->right != NULL) {
            ++last;
            if (strcmp(BFS_TABLE[begin]->right->entry.key, key) == 0) {
                sign = last;
            }
            BFS_TABLE[last] = BFS_TABLE[begin]->right;
        }
    }
    if (sign != -1) {
        symtab *temp = BFS_TABLE[sign];
        BFS_TABLE[sign] = BFS_TABLE[last];
        free(temp);
        return 1;
    }
    return 0;
}
