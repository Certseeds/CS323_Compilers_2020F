/*
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-10-07 18:48:42
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-11-08 23:40:52
 */
//
// Created by nanos on 2020/10/7.
//

#ifndef CS323_COMPLIERS_PROJECT3_INCLUDE_NODE_HPP
#define CS323_COMPLIERS_PROJECT3_INCLUDE_NODE_HPP

#include "interCode.hpp"
#include <functional>
#include <iostream>
#include <variant>
#include <unordered_map>

class Type;

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
    Type *type = nullptr;
    InterCode *interCode = nullptr;
    std::vector<InterCode *> intercodes;

    //void (*print)(int, Node *);
    Node();

    explicit Node(Node_TYPE type);

    static Node *getSingleNameNodePointer(const string &nam);

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

    [[nodiscard]] Node *const &get_nodes(size_t order) const {
        return this->nodes[order];
    }

    template<typename T=size_t, typename... Args>
    Node *const &get_nodes(size_t order, Args... rest) const {
        return this->nodes[order]->get_nodes(rest...);
    }

    void print_vector_intercode() const;

private:
    static void print_n_space(int space);

    void print_line(int space);

    Node(string name, Node_TYPE node_type, int nodes_num, Node_inside_type value);
};

#endif  //! CS323_COMPLIERS_PROJECT3_INCLUDE_NODE_HPP
