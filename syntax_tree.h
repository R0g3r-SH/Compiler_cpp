#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include <string>
#include <vector>

class Node {
public:
    std::string type;
    std::string value;
    std::vector<Node*> children;
    std::string numeric_type; 
    bool quadruplesGenerated = false;
    bool isIfElse; // Flag to indicate if it's an IF-ELSE statement


     Node(std::string type, std::string value, std::string numeric_type = "") 
        : type(type), value(value), numeric_type(numeric_type), isIfElse(false) {} // Constructor
};


// Function to print the syntax tree recursively
void printSyntaxTree(const Node* root);

// Function to generate quadruples from the syntax tree

void generateQuadruples(Node* node);


#endif // SYNTAX_TREE_H
