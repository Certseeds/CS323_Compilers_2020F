/*
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-10-07 18:48:42
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-10-08 13:37:55
 */
//
// Created by nanos on 2020/10/7.
//

#ifndef CS323_COMPLIERS_PROJECT1_NODE_HPP
#define CS323_COMPLIERS_PROJECT1_NODE_HPP

#include <string>
#include <iostream>
#include <functional>

enum class Node_TYPE {
    LINE,
    NAME,
    STRING,
    CHAR,
    INT,
    FLOAT,
    NOTHING
};

class Node {
public:
    std::string name;
    std::string string_value;
    Node_TYPE TYPE;
    int nodes_num = 0;
    union {
        int linenum;
        char char_value;
        int int_value;
        float float_value;
    };
    std::vector<Node *> nodes;

    //void (*print)(int, Node *);
    Node();

    explicit Node(Node_TYPE type);

    Node(std::string nam);

    explicit Node(float value);

    explicit Node(int value);

    explicit Node(char value);

    Node(std::string nam, int line_nu);

    explicit Node(std::string nam, Node_TYPE type);

    Node(std::string nam, int line_nu, Node_TYPE type);

    Node(std::string nam, std::string value, Node_TYPE type);

    ~Node() = default;

    void print(int space);

    void node_set_sub(Node *subnode) {
        this->nodes_num++;
        this->nodes.push_back(subnode);
    }

    template<typename T, typename... Args>
    void node_set_sub(T subnode1, Args ... rest) {
        this->node_set_sub(subnode1);
        this->node_set_sub(rest ...);
    }

private:
    void print_n_space(int space);

    void print_line(int space);
};


#endif //CS323_COMPLIERS_PROJECT1_NODE_HPP
