#include "syntax_tree.h"
#include "quadruple_manager.h"
#include <iostream>

void printSyntaxTree(const Node *root)
{
    // Print the current node

    std::cout << root->type << " " << root->value << std::endl;

    // Recursively print children
    for (const Node *child : root->children)
    {
        printSyntaxTree(child);
    }
}

void generateQuadruples(Node* node) {
    if (node == nullptr) {
        return;
    }

    if (node->type == "assignment") {
        // For assignment nodes, generate quadruples for the expression on the right-hand side
        generateQuadruples(node->children[1]);

        // Generate quadruple for assignment
        std::string op = "=";
        std::string result = node->children[0]->value; // Variable name
        std::string operand = node->children[1]->value; // Value to assign
        addQuadruple(op, operand, "", result);
    } else if (node->type == "expression") {
        // For expression nodes, generate quadruples for left and right children
        generateQuadruples(node->children[0]);
        generateQuadruples(node->children[1]);

        // Generate quadruple for the operation
        std::string op = node->value;
        std::string result = getNextTemporary();
        std::string leftOperand = node->children[0]->value;
        std::string rightOperand = node->children[1]->value;

        if (op == "+") {
            addQuadruple("+", leftOperand, rightOperand, result);
        } else if (op == "-") {
            addQuadruple("-", leftOperand, rightOperand, result);
        } else if (op == "*") {
            addQuadruple("*", leftOperand, rightOperand, result);
        } else if (op == "/") {
            addQuadruple("/", leftOperand, rightOperand, result);
        }

        // Update the value of the expression node to be the result
        node->value = result;
    }

    // Recursively process child nodes
    for (Node* child : node->children) {
        generateQuadruples(child);
    }
}

// Path: main_test.cpp
