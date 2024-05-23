%{
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

#include "directory_manager.h"
#include "memory_manager.h"
#include "quadruple_manager.h"
#include "stacks.h"

int yyerror(const char* s);

extern MemoryManager memoryManager;
int tempCounter = 0;

%}

%union {
    char *str;
    int num;
    float fnum;
}

%token PROGRAM ID SEMI_COLON VAR COMMA POINTS INT FLOAT IF ELSE WHILE LEFT_BRACE RIGHT_BRACE LEFT_PAREN RIGHT_PAREN EQUALS GREATER_THAN LESS_THAN NOT_EQUALS PLUS MINUS TIMES DIVIDE CTE_INT CTE_FLOAT CTE_STRING VOID PRINT DO END

%token <str> ID
%token <num> CTE_INT
%token <fnum> CTE_FLOAT
%token <str> CTE_STRING

%type <str> var_list
%type <str> type
%type <str> factor
%type <str> term
%type <str> expression
%type <str> comparison
%type <str> assignment
%type <str> list_of_expressions
%type <str> list_of_cte_strings

%%

program : PROGRAM statements END { printf("Programa válido\n"); }
        ;

statements : /* empty */
           | statements statement
           ;

statement : var_declaration SEMI_COLON
          | assignment SEMI_COLON
          | print_statement SEMI_COLON
          | if_statement
          | while_statement
          ;

type : INT { $$ = strdup("INT"); }
     | FLOAT { $$ = strdup("FLOAT"); }
     | VOID { $$ = strdup("VOID"); }
     ;

var_declaration
    : VAR var_list POINTS type {
        printf("Variable(s) declared\n");
        // Split the variable list by commas
        std::stringstream ss($2);
        std::string var;
        while (std::getline(ss, var, ',')) {
            // Trim whitespace (if needed)
            var.erase(0, var.find_first_not_of(' ')); 
            var.erase(var.find_last_not_of(' ') + 1);

            printf("ID: %s, Type: %s\n", var.c_str(), $4);
            // Add to symbol table
            addVariableToDirectory(var, $4);

            // Allocate memory for the variable
            if (strcmp($4, "INT") == 0) {
                memoryManager.allocateInt(var);
            } else if (strcmp($4, "FLOAT") == 0) {
                memoryManager.allocateFloat(var);
            }
        }
        free($2); // Free the allocated memory for $2
        free($4); // Free the allocated memory for $4
    }
    ;

var_list
    : ID { $$ = strdup($1); }
    | var_list COMMA ID { 
        std::string result = std::string($1) + ", " + $3;
        $$ = strdup(result.c_str());
        free($1); // Free the allocated memory for $1
        free($3); // Free the allocated memory for $3
      }
    ;

factor : ID {
            // Get the memory address of the variable
            int address = memoryManager.allocateInt($1);
            char buffer[20];
            sprintf(buffer, "%d", address);
            $$ = strdup(buffer);
        }
       | CTE_INT {
            char buffer[20];
            sprintf(buffer, "%d", $1);
            $$ = strdup(buffer);
        }
       | CTE_FLOAT {
            char buffer[20];
            sprintf(buffer, "%f", $1);
            $$ = strdup(buffer);
        }
       | LEFT_PAREN expression RIGHT_PAREN {
            $$ = $2;
        }
       | PLUS factor {
            $$ = $2;
        }
       | MINUS factor {
            $$ = $2;
        }
       ;

term : factor {
            $$ = $1;
        }
     | term TIMES factor {
            // Generate quadruple for multiplication
            int tempAddress = memoryManager.allocateTemp();
            char temp[20];
            sprintf(temp, "t%d", tempAddress);
            generateQuadruple("MUL", $1, $3, temp);
            $$ = strdup(temp);
            free($1);
            free($3);
        }
     | term DIVIDE factor {
            // Generate quadruple for division
            int tempAddress = memoryManager.allocateTemp();
            char temp[20];
            sprintf(temp, "t%d", tempAddress);
            generateQuadruple("DIV", $1, $3, temp);
            $$ = strdup(temp);
            free($1);
            free($3);
        }
     ;

expression : term {
                $$ = $1;
            }
           | expression PLUS term {
                // Generate quadruple for addition
                int tempAddress = memoryManager.allocateTemp();
                char temp[20];
                sprintf(temp, "t%d", tempAddress);
                generateQuadruple("ADD", $1, $3, temp);
                $$ = strdup(temp);
                free($1);
                free($3);
            }
           | expression MINUS term {
                // Generate quadruple for subtraction
                int tempAddress = memoryManager.allocateTemp();
                char temp[20];
                sprintf(temp, "t%d", tempAddress);
                generateQuadruple("SUB", $1, $3, temp);
                $$ = strdup(temp);
                free($1);
                free($3);
            }
           ;

comparison : expression
           | expression GREATER_THAN expression
           | expression LESS_THAN expression
           | expression NOT_EQUALS expression
           ;

assignment : ID EQUALS expression {
                // Get the memory address for the variable being assigned
                int address = memoryManager.allocateInt($1);
                char addressStr[20];
                sprintf(addressStr, "%d", address);
                // Generate quadruple for assignment
                generateQuadruple("ASSIGN", $3, "", addressStr);
                free($3);
            }
           ;

list_of_cte_strings : CTE_STRING
                    | list_of_cte_strings COMMA CTE_STRING
                    ;

list_of_expressions : expression
                    | list_of_expressions COMMA expression
                    ;

print_statement : PRINT LEFT_PAREN list_of_expressions RIGHT_PAREN {
    // Generate quadruples for each expression to be printed
    std::stringstream ss($3);
    std::string expression;
    while (std::getline(ss, expression, ',')) {
        // Trim whitespace (if needed)
        expression.erase(0, expression.find_first_not_of(' ')); 
        expression.erase(expression.find_last_not_of(' ') + 1);

        // Generate quadruple for printing the expression
        generateQuadruple("PRINT", expression.c_str(), "", "");
    }
}
                | PRINT LEFT_PAREN list_of_cte_strings RIGHT_PAREN {
    // Generate quadruples for each constant string to be printed
    std::stringstream ss($3);
    std::string cte_string;
    while (std::getline(ss, cte_string, ',')) {
        // Trim whitespace (if needed)
        cte_string.erase(0, cte_string.find_first_not_of(' ')); 
        cte_string.erase(cte_string.find_last_not_of(' ') + 1);

        // Generate quadruple for printing the constant string
        generateQuadruple("PRINT", cte_string.c_str(), "", "");
    }
}
                ;




if_statement : IF LEFT_PAREN comparison RIGHT_PAREN LEFT_BRACE statements RIGHT_BRACE
             | IF LEFT_PAREN comparison RIGHT_PAREN LEFT_BRACE statements RIGHT_BRACE ELSE LEFT_BRACE statements RIGHT_BRACE
             ;

while_statement : WHILE LEFT_BRACE statements RIGHT_BRACE DO LEFT_PAREN comparison RIGHT_PAREN 
{
     printf("While statement\n");
}
                ;

%%

