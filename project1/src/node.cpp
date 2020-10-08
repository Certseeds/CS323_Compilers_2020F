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
        case Node_TYPE::LINE : {
            this->print_line(space);
            break;
        }
        case Node_TYPE::NAME: {
            printf("%s\n", this->name.c_str());
            break;
        }
        case Node_TYPE::STRING: {
            printf("%s: %s\n", this->name.c_str(), this->string_value.c_str());
            break;
        }
        case Node_TYPE::CHAR: {
            printf("%s: %c\n", this->name.c_str(), this->char_value);
            break;
        }
        case Node_TYPE::FLOAT: {
            printf("%s: %f\n", this->name.c_str(), this->float_value);
            break;
        }
        case Node_TYPE::INT: {
            printf("%s: %d\n", this->name.c_str(), this->int_value);
            break;
        }
        case Node_TYPE::NOTHING: {
            return;
        }
    }
}

Node::Node() : name("No Name"), TYPE(Node_TYPE::NAME){}

Node::Node(std::string nam) : name(std::move(nam)), TYPE(Node_TYPE::NAME) {}

Node::Node(float value) : name("FLOAT"), TYPE(Node_TYPE::FLOAT), float_value(value) {}

Node::Node(int value) : name("INT"), TYPE(Node_TYPE::INT), int_value(value) {}

Node::Node(char value) : name("CHAR"), TYPE(Node_TYPE::CHAR), char_value(value) {}

Node::Node(Node_TYPE type) : name("No Name"), TYPE(type) {}

Node::Node(std::string nam, Node_TYPE type) : name(std::move(nam)), TYPE(type) {}

Node::Node(std::string nam, int line_nu) :
        name(std::move(nam)), TYPE(Node_TYPE::LINE), linenum(line_nu) {
    this->nodes = std::vector<Node *>(this->nodes_num);
}

Node::Node(std::string nam, int line_nu, Node_TYPE type) :
        name(std::move(nam)), TYPE(type), linenum(line_nu) {
    this->nodes = std::vector<Node *>(this->nodes_num);
}


Node::Node(std::string nam, std::string value, Node_TYPE type) :
        name(std::move(nam)), string_value(std::move(value)), TYPE(type) {}

void Node::print_n_space(int n) { std::cout << std::string(n, ' '); }

void Node::print_line(int space) {
    printf("%s (%d)\n", this->name.c_str(), this->linenum);
    for (const auto &iter :this->nodes) {
        iter->print(space + 2);
    }

}
