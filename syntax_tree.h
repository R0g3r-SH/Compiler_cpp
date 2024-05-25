#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include <string>
#include <vector>

// Define the Node structure
struct Node {
    std::string type;
    std::string value;
    std::vector<Node*> children;

    Node(const std::string& type, const std::string& value) : type(type), value(value) {}
};

// Function to print the syntax tree recursively
void printSyntaxTree(const Node* root);

// Function to generate quadruples from the syntax tree

void generateQuadruples(Node* node);


#endif // SYNTAX_TREE_H
