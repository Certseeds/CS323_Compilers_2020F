/*
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-10-11 10:55:36
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-11-06 10:36:06
 */
//
// Created by nanos on 2020/10/7.
//

#include "node.hpp"

#include <utility>

void Node::print(int space) {
    if (this->TYPE == Node_TYPE::NOTHING) {
        return;
    }
    print_n_space(space);
    switch (this->TYPE) {
        case Node_TYPE::LINE: {
            this->print_line(space);
            break;
        }
        case Node_TYPE::NAME: {
            printf("%s\n", this->name.c_str());
            break;
        }
        case Node_TYPE::STRING: {
            printf("%s: %s\n", this->name.c_str(), std::get<string>(this->value).c_str());
            break;
        }
        case Node_TYPE::CHAR: {
            printf("%s: %c\n", this->name.c_str(), std::get<char>(this->value));
            break;
        }
        case Node_TYPE::FLOAT: {
            printf("%s: %f\n", this->name.c_str(), std::get<float>(this->value));
            break;
        }
        case Node_TYPE::INT: {
            printf("%s: %d\n", this->name.c_str(), std::get<int>(this->value));
            break;
        }
        case Node_TYPE::NOTHING: {
            return;
        }
    }
}

Node::Node() : Node("No Name", Node_TYPE::NAME, 0, "") {};

Node::Node(const char *const nam) : Node(string(nam)) {}

Node::Node(string nam) : Node(std::move(nam), Node_TYPE::NAME, 0, "") {}

Node::Node(float float_value) : Node("FLOAT", Node_TYPE::FLOAT, 0, float_value) {};

Node::Node(int int_value) : Node("INT", Node_TYPE::INT, 0, int_value) {};

Node::Node(char char_value) : Node("CHAR", Node_TYPE::CHAR, 0, char_value) {}

Node::Node(Node_TYPE type) : Node("No Name", type, 0, 0) {}

Node::Node(string nam, Node_TYPE type) : Node(std::move(nam), type, 0, 0) {};

Node::Node(string nam, int int_line_value, Node_TYPE type) : Node(std::move(nam), type, 0, int_line_value) {};

Node::Node(string nam, string str_value, Node_TYPE type) : Node(std::move(nam), type, 0, str_value) {};

Node::Node(string name, Node_TYPE node_type, int nodes_num, Node_inside_type value) : name(name), TYPE(node_type),
                                                                                      nodes_num(nodes_num),
                                                                                      value(value) {
    this->nodes = std::vector<Node *>(this->nodes_num);
};

void Node::print_n_space(int n) {
    std::cout << string(n, ' ');
}

void Node::print_line(int space) {
    printf("%s (%d)\n", this->name.c_str(), std::get<int>(this->value));
    for (const auto &iter : this->nodes) {
        iter->print(space + 2);
    }
}
