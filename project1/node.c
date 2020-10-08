//
// Created by nanos on 2020/10/7.
//

#include "node.h"

struct Node *new_node_key(char *nam) {
    struct Node *will_return = (struct Node *) malloc(sizeof(struct Node));
    will_return->name = nam;
    will_return->nodes_num = 0;
    will_return->nodes = NULL;
    will_return->print = &print_name;
    return will_return;
    // TODO-values
}

struct Node *new_node_line_num(char *nam, int line_nu, int nodes_nu) {
    struct Node *will_return = new_node_key(nam);
    will_return->linenum = line_nu;
    will_return->nodes_num = nodes_nu;
    will_return->nodes = (struct Node **) malloc(sizeof(struct Node *) * nodes_nu);
    for (int i = 0; i < nodes_nu; ++i) {
        will_return->nodes[i] = (struct Node *) malloc(sizeof(struct Node));
    }
    will_return->print = &print_line;
    return will_return;
}

void node_set_sub(struct Node *node, int num, ...) {
    va_list valist;
    va_start(valist, num);
    for (int i = 0; i < num; i++) {
        node->nodes[i] = va_arg(valist, struct Node*);
    }
    va_end(valist);
}

void print_n_space(int n) { for (int i = 0; i < n; ++i) { printf(" "); }}

void print_line(int space, struct Node *node) {
    print_n_space(space);
    printf("%s (%d)\n", node->name, node->linenum);
    if (node->nodes_num != 0) {
        for (int i = 0; i < node->nodes_num; i++) {
            node->nodes[i]->print(space + 2, node->nodes[i]);
        }
    }
}

void print_int_value(int space, struct Node *node) {
    print_n_space(space);
    printf("%s: %d\n", node->name, node->int_value);
}

void print_float_value(int space, struct Node *node) {
    print_n_space(space);
    printf("%s: %f\n", node->name, node->float_value);
}

void print_char_value(int space, struct Node *node) {
    print_n_space(space);
    printf("%s: %c\n", node->name, node->char_value);
}

void print_str_value(int space, struct Node *node) {
    print_n_space(space);
    printf("%s: %s\n", node->name, node->string_value);
}

void print_name(int space, struct Node *node) {
    print_n_space(space);
    printf("%s\n", node->name);
}

void print_nothing(int space, struct Node *node) {}