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

void generateQuadruples(Node *node)
{
    if (node == nullptr)
    {
        return;
    }

    if (node->type == "assignment" && !node->quadruplesGenerated)
    {

        node->quadruplesGenerated = true; // Set the flag to indicate quadruples are generated for this node
        // For assignment nodes, generate quadruples for the expression on the right-hand side
        generateQuadruples(node->children[1]);

        // Generate quadruple for assignment
        std::string op = "=";
        std::string result = node->children[0]->value;  // Variable name
        std::string operand = node->children[1]->value; // Value to assign
        addQuadruple(op, operand, "", result);
    }
    else if (node->type == "expression" && !node->quadruplesGenerated)
    {
        node->quadruplesGenerated = true; // Set the flag to indicate quadruples are generated for this node
        // For expression nodes, generate quadruples for left and right children
        generateQuadruples(node->children[0]);
        generateQuadruples(node->children[1]);

        // Generate quadruple for the operation
        std::string op = node->value;
        std::string result = getNextTemporary();
        std::string leftOperand = node->children[0]->value;
        std::string rightOperand = node->children[1]->value;

        if (op == "+")
        {
            addQuadruple("+", leftOperand, rightOperand, result);
        }
        else if (op == "-")
        {
            addQuadruple("-", leftOperand, rightOperand, result);
        }
        else if (op == "*")
        {
            addQuadruple("*", leftOperand, rightOperand, result);
        }
        else if (op == "/")
        {
            addQuadruple("/", leftOperand, rightOperand, result);
        }

        // Update the value of the expression node to be the result
        node->value = result;
    }
    else if (node->type == "print_statement" && !node->quadruplesGenerated)
    {
        node->quadruplesGenerated = true; // Set the flag to indicate quadruples are generated for this node

        // Generate quadruples for each expression to be printed
        for (auto &child : node->children)
        {
            generateQuadruples(child);
            // Generate quadruple for printing the expression
            addQuadruple("PRINT", "", "", child->value);
        }
    }

    else if (node->type == "if_statement" && !node->quadruplesGenerated)
    {
        node->quadruplesGenerated = true; // Set the flag to indicate quadruples are generated for this node

        // Generate quadruples for the comparison expression
        generateQuadruples(node->children[0]);

        // Generate a quadruple to jump to the else part if the comparison is false
        std::string condition = node->children[0]->value;
        std::string labelElse = getNextLabel();
        addQuadruple("GOTO_FALSE", condition, "", labelElse);

        // Generate quadruples for the statements in the if block
        generateQuadruples(node->children[1]);

        if (node->isIfElse)
        {
            // Generate a quadruple to jump to the end of the if-else statement
            std::string labelEnd = getNextLabel();
            addQuadruple("GOTO", "", "", labelEnd);

            // Generate a label for the else part
            addQuadruple("LABEL", "", "", labelElse);

            // Generate quadruples for the statements in the else block
            generateQuadruples(node->children[2]);

            // Generate a label for the end of the if-else statement
            addQuadruple("LABEL", "", "", labelEnd);
        }
        else
        {
            // Generate a label for the end of the if statement
            addQuadruple("LABEL", "", "", labelElse);
        }
    }

    else if (node->type == "comparison")
    {
        // Generate quadruples for left and right children
        generateQuadruples(node->children[0]);
        generateQuadruples(node->children[1]);

        // Generate quadruple for the comparison
        std::string op = node->value;
        std::string result = getNextTemporary();
        std::string leftOperand = node->children[0]->value;
        std::string rightOperand = node->children[1]->value;

        if (op == "==")
        {
            addQuadruple("==", leftOperand, rightOperand, result);
        }
        else if (op == "!=")
        {
            addQuadruple("!=", leftOperand, rightOperand, result);
        }
        else if (op == "<")
        {
            addQuadruple("<", leftOperand, rightOperand, result);
        }
        else if (op == ">")
        {
            addQuadruple(">", leftOperand, rightOperand, result);
        }
        else if (op == "<=")
        {
            addQuadruple("<=", leftOperand, rightOperand, result);
        }
        else if (op == ">=")
        {
            addQuadruple(">=", leftOperand, rightOperand, result);
        }

        // Update the value of the comparison node to be the result
        node->value = result;
    }

    else if (node->type == "while_statement" && !node->quadruplesGenerated)
    {
        node->quadruplesGenerated = true; // Set the flag to indicate quadruples are generated for this node

        // Generate a label for the beginning of the while loop
        std::string labelStart = getNextLabel();
        addQuadruple("LABEL", "", "", labelStart);

        // Generate quadruples for the comparison expression
        generateQuadruples(node->children[1]);

        // Generate a quadruple to jump out of the loop if the comparison is false
        std::string condition = node->children[1]->value;
        std::string labelEnd = getNextLabel();
        addQuadruple("GOTO_FALSE", condition, "", labelEnd);

        // Generate quadruples for the statements inside the while loop
        generateQuadruples(node->children[0]);

        // Generate a quadruple to jump back to the beginning of the while loop
        addQuadruple("GOTO", "", "", labelStart);

        // Generate a label for the end of the while loop
        addQuadruple("LABEL", "", "", labelEnd);
    }
  
    for (Node *child : node->children)
    {
        generateQuadruples(child);
    }
}

// Path: main_test.cpp
