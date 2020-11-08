/*
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-10-07 18:48:42
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-11-06 11:25:16
 */
//
// Created by nanos on 2020/10/7.
//

#ifndef CS323_COMPLIERS_PROJECT1_NODE_HPP
#define CS323_COMPLIERS_PROJECT1_NODE_HPP

#include <functional>
#include <iostream>
#include <string>
#include <variant>

using std::string;

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
    using Node_inside_type = std::variant<string, int, char, float>;
    // line num, char_value,int_value,float_value
public:
    string name;
    Node_TYPE TYPE;
    int nodes_num = 0;
    Node_inside_type value;
    std::vector<Node *> nodes;

    //void (*print)(int, Node *);
    Node();

    explicit Node(Node_TYPE type);

    explicit Node(string nam);

    explicit Node(const char *nam);

    explicit Node(float value);

    explicit Node(int value);

    explicit Node(char value);

    Node(string nam, Node_TYPE type);

    Node(string nam, int int_line_value, Node_TYPE type = Node_TYPE::LINE);

    Node(string nam, string str_value, Node_TYPE type = Node_TYPE::STRING);

    ~Node() = default;

    void print(int space = 0);

    void push_back(Node *subnode) {
        this->nodes_num++;
        this->nodes.push_back(subnode);
    }

    template<typename T, typename... Args>
    void push_back(T subnode1, Args... rest) {
        this->push_back(subnode1);
        this->push_back(rest...);
    }

    Node *&get_nodes(int order) {
        return this->nodes[order];
    }

    template<typename T=size_t, typename... Args>
    Node *&get_nodes(int order, Args... rest) {
        return this->nodes[order]->get_nodes(rest...);
    }

private:
    static void print_n_space(int space);

    void print_line(int space);

    Node(string name, Node_TYPE node_type, int nodes_num, Node_inside_type value);
};

#endif  //CS323_COMPLIERS_PROJECT1_NODE_HPP
