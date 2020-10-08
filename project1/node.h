/*
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-10-07 18:48:42
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-10-08 11:28:17
 */
//
// Created by nanos on 2020/10/7.
//

#ifndef CS323_COMPLIERS_PROJECT1_NODE_HPP
#define CS323_COMPLIERS_PROJECT1_NODE_HPP

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
    char *name;
    int nodes_num;
    union {
        int linenum;
        char char_value;
        int int_value;
        float float_value;
        char *string_value;
    };
    struct Node **nodes;

    void (*print)(int, struct Node *);
};
void print_n_space(int n);

void print_line(int space, struct Node *node);

void print_str_value(int space, struct Node *node);

void print_int_value(int space, struct Node *node);

void print_float_value(int space, struct Node *node);

void print_char_value(int space, struct Node *node);

void print_name(int space, struct Node *node);

void print_nothing(int space, struct Node *node);

void node_set_sub(struct Node *node, int num, ...);

struct Node *new_node_key(char *nam);

struct Node *new_node_key_value(char *nam);

struct Node *new_node_line_num(char *nam, int line_nu, int nodes_nu);

#endif //CS323_COMPLIERS_PROJECT1_NODE_HPP
