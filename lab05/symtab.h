#ifndef SYMTAB_H
#define SYMTAB_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

inline static constexpr size_t KEY_LEN = 32;
using VAL_T = int;

struct symtab;

/* symbol table entry, only used internally */
struct entry {
    char key[KEY_LEN + 1]{'\0'};
    VAL_T value{0};
};

void entry_init(entry * const self, char * const key, VAL_T value) {
    sprintf(self->key, "%s", key);
    self->value = value;
}


// init a single symbol table
symtab *symtab_init();

// insert a key-value pair to the table
// if insert success, return 1, otherwise 0
int symtab_insert(symtab *, char *, VAL_T);

// lookup the value of a specific key
// return -1 if not found
VAL_T symtab_lookup(symtab *, char *);

// remove a key-value pair from the table
// if remove success, return 1, otherwise 0
int symtab_remove(symtab *, char *);

#endif  /* SYMTAB_H */
