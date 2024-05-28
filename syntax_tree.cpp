#include "syntax_tree.h"
#include "quadruple_manager.h"
#include "directory_manager.h"
#include "semantic_cube.h"
#include "memory_manager.h"

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

std::string getType(Node *node)
{
    if (node == nullptr)
    {
        return "unknown";
    }

    if (node->type == "factor")
    {
        if (!node->numeric_type.empty())
        {
            if (node->numeric_type == "ID")
            {
                if (!isVariableDefined(node->value))
                {
                    std::cerr << "Error: Variable '" << node->value << "' no declarada\n";
                    exit(1);
                }
                return symbolTable[node->value].type;
            }
            else
            {
                return node->numeric_type;
            }
        }
    }
    else if (node->type == "expression" || node->type == "term")
    {
        if (node->children.size() < 2)
        {
            return "unknown";
        }
        std::string leftType = getType(node->children[0]);
        std::string rightType = getType(node->children[1]);

        if ((leftType == "FLOAT" && rightType == "FLOAT") ||
            (leftType == "INT" && rightType == "FLOAT") ||
            (leftType == "FLOAT" && rightType == "INT"))
        {
            return "FLOAT";
        }
        else
        {
            return "INT";
        }
    }

    return "unknown";
}

void generateQuadruples(Node *node)
{
    if (node == nullptr)
    {
        return;
    }

    if (node->type == "assignment" && !node->quadruplesGenerated)
    {

        if (!isVariableDefined(node->children[0]->value))
        {
            std::cerr << "Error: Variable '" << node->children[0]->value << "' no declarada\n";
            exit(1);
        }

        std::string varType = symbolTable[node->children[0]->value].type;
        std::string exprType = getType(node->children[1]);

        std::cout << "varType: " << varType << " exprType: " << exprType << std::endl;

        if (varType != exprType)
        {
            std::cerr << "Error: Tipos incompatibles en la asignación a '" << node->children[0]->value << "'\n";
            exit(1);
        }

        node->quadruplesGenerated = true; // Set the flag to indicate quadruples are generated for this node
        // For assignment nodes, generate quadruples for the expression on the right-hand side
        generateQuadruples(node->children[1]);

        // Allocate memory for the variable based on its type
        int memoryAddress = memoryManager.allocateMemoryByType(node->children[0]->value, varType);
        // Update the memory allocation for the variable in the symbol table
        symbolTable[node->children[0]->value].memoryAllocation = memoryAddress;
        // Generate quadruple for assignment
        std::string op = "=";
        std::string result = std::to_string(symbolTable[node->children[0]->value].memoryAllocation);
        std::string operand = node->children[1]->value; // Value to assign
        addQuadruple(op, operand, "", result);
    }
    else if (node->type == "expression" && !node->quadruplesGenerated)
    {
        node->quadruplesGenerated = true; // Set the flag to indicate quadruples are generated for this node
        // For expression nodes, generate quadruples for left and right children
        generateQuadruples(node->children[0]);
        generateQuadruples(node->children[1]);

        std::string op = node->value;
        std::string result = getNextTemporary();

        std::string leftOperand, rightOperand;
        if (node->children[0]->type == "ID")
        {
            leftOperand = std::to_string(symbolTable[node->children[0]->value].memoryAllocation);
        }
        else if (node->children[0]->type == "INT" || node->children[0]->type == "FLOAT")
        {
            leftOperand = node->children[0]->value;
        }
        else
        {
            leftOperand = node->children[0]->value;
        }

        if (node->children[1]->type == "ID")
        {
            rightOperand = std::to_string(symbolTable[node->children[1]->value].memoryAllocation);
        }
        else if (node->children[1]->type == "INT" || node->children[1]->type == "FLOAT")
        {
            rightOperand = node->children[1]->value;
        }
        else
        {
            rightOperand = node->children[1]->value;
        }

        addQuadruple(op, leftOperand, rightOperand, result);
        node->value = result; // Update the value of the expression node to be the result
    }

    else if (node->type == "term" && !node->quadruplesGenerated)
    {
        node->quadruplesGenerated = true;
        generateQuadruples(node->children[0]); // Generate quadruples for the first operand
        generateQuadruples(node->children[1]); // Generate quadruples for the second operand

        std::string op = node->value;
        std::string result = getNextTemporary();

        // review if is a value stored in a variable or a number
        std::string leftOperand, rightOperand;

        if (node->children[0]->type == "ID")
        {
            leftOperand = std::to_string(symbolTable[node->children[0]->value].memoryAllocation);
        }
        else if (node->children[0]->type == "INT" || node->children[0]->type == "FLOAT")
        {
            leftOperand = node->children[0]->value;
        }
        else
        {
            leftOperand = node->children[0]->value;
        }

        if (node->children[1]->type == "ID")
        {
            rightOperand = std::to_string(symbolTable[node->children[1]->value].memoryAllocation);
        }
        else if (node->children[1]->type == "INT" || node->children[1]->type == "FLOAT")
        {
            rightOperand = node->children[1]->value;
        }
        else
        {
            rightOperand = node->children[1]->value;
        }

        // Generate quadruple for the multiplication operation
        if (op == "*")
        {
            addQuadruple("*", leftOperand, rightOperand, result);
        }
        else if (op == "/")
        {
            addQuadruple("/", leftOperand, rightOperand, result);
        }

        // Update the value of the term node to be the result
        node->value = result;
    }

    else if (node->type == "print_statement" && !node->quadruplesGenerated)
    {
        node->quadruplesGenerated = true; // Set the flag to indicate quadruples are generated for this node

        // Generate quadruples for each expression or string literal to be printed
        for (auto &child : node->children)
        {
            std::cout << "child->type: " << child->type << std::endl;
            if (child->type == "CTE_STRING")
            {
                // Generate quadruple for printing the string literal
                addQuadruple("PRINT", "", "", child->value);
            }
            else
            {
                generateQuadruples(child);
                // Generate quadruple for printing the variable or expression
                addQuadruple("PRINT", "", "", std::to_string(symbolTable[child->value].memoryAllocation));
            }
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

        // review if is a value stored in a variable or a number

        std::string leftOperand, rightOperand;

        if (node->children[0]->numeric_type == "ID")
        {
            leftOperand = std::to_string(symbolTable[node->children[0]->value].memoryAllocation);
        }
        else if (node->children[0]->type == "INT" || node->children[0]->type == "FLOAT")
        {
            leftOperand = node->children[0]->value;
        }
        else
        {
            leftOperand = node->children[0]->value;
        }

        if (node->children[1]->numeric_type == "ID")
        {
            rightOperand = std::to_string(symbolTable[node->children[1]->value].memoryAllocation);
        }
        else if (node->children[1]->type == "INT" || node->children[1]->type == "FLOAT")
        {
            rightOperand = node->children[1]->value;
        }
        else
        {
            rightOperand = node->children[1]->value;
        }

        // review if allready have the memory allocation

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

        // Generate a label for the beginning of the do-while loop
        std::string labelStart = getNextLabel();
        addQuadruple("LABEL", "", "", labelStart);

        // Generate quadruples for the statements inside the do-while loop
        generateQuadruples(node->children[0]);

        // Generate quadruples for the comparison expression
        generateQuadruples(node->children[1]);

        // Generate a quadruple to jump back to the beginning of the do-while loop
        std::string condition = node->children[1]->value;

        addQuadruple("GOTO_TRUE", condition, "", labelStart);

        // Generate a label for the end of the do-while loop
        std::string labelEnd = getNextLabel();
        addQuadruple("LABEL", "", "", labelEnd);
    }

    for (Node *child : node->children)
    {
        generateQuadruples(child);
    }
}

// Path: main_test.cpp
