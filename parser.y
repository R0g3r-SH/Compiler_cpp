%{
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

#include "directory_manager.h"
#include "memory_manager.h"
#include "quadruple_manager.h"
#include "stacks.h"
#include "syntax_tree.h"

int yyerror(const char* s);

extern MemoryManager memoryManager;
int tempCounter = 0;


Node* rootNode = nullptr;

%}

%union {
    char *str;
    int num;
    float fnum;
    Node* node; 
}

%token PROGRAM ID SEMI_COLON VAR COMMA POINTS INT FLOAT IF ELSE WHILE LEFT_BRACE RIGHT_BRACE LEFT_PAREN RIGHT_PAREN EQUALS GREATER_THAN LESS_THAN NOT_EQUALS PLUS MINUS TIMES DIVIDE CTE_INT CTE_FLOAT CTE_STRING VOID PRINT DO END

%token <str> ID
%token <num> CTE_INT
%token <fnum> CTE_FLOAT
%token <str> CTE_STRING 
%token <str> RIGHT_BRACE
%token <str> LEFT_BRACE
%token <str> LEFT_PAREN
%token <str> RIGHT_PAREN

%type <node> program
%type <node> statements
%type <node> statement
%type <node> var_declaration
%type <node> assignment
%type <node> print_statement
%type <node> if_statement
%type <node> while_statement
%type <node> type
%type <node> var_list
%type <node> factor
%type <node> term
%type <node> expression
%type <node> comparison
%type <node> list_of_expressions
%type <node> list_of_cte_strings

%%

program : PROGRAM statements END { 

    $$ = new Node("program", "program");
    $$->children.push_back($2); // Add statements as a child of the program node
    rootNode = $$; // Save the root node
    printf("Program parsed !!! \n");

    printf("Syntax tree: \n");
    
    printSyntaxTree(rootNode); // Print the syntax tree 
    generateQuadruples(rootNode);

 }
        ;

statements : /* empty */ {
    // Construct an empty statements node
    $$ = new Node("statements", "");
}
           | statements statement {
               // Append the statement node to the statements node
               $$ = $1;
               $$->children.push_back($2);
           }
           ;

statement : var_declaration SEMI_COLON {
    // Construct the var_declaration node
    $$ = $1;
}
          | assignment SEMI_COLON {
              // Construct the assignment node
              $$ = $1;
          }
          | print_statement SEMI_COLON {
              // Construct the print_statement node
              $$ = $1;
          }
          | if_statement {
              // Construct the if_statement node
              $$ = $1;
          }
          | while_statement {
              // Construct the while_statement node
              $$ = $1;
          }
          ;

var_declaration
    : VAR var_list POINTS type {
        $$ = new Node("var_declaration", "");
        $$->children.push_back($2); // Add var_list as a child of var_declaration
        $$->children.push_back($4); // Add type as a child of var_declaration

        // Obtener la lista de variables y el tipo
        Node* varListNode = $2;
        std::string varType = $4->value;

        // Iterar sobre la lista de variables y agregar cada una a la tabla de símbolos
        for (Node* varNode : varListNode->children) {
            std::string varName = varNode->value;
            std::string varType = $4->value;

            // Agregar la variable a la tabla de símbolos
            addVariableToDirectory(varName, varType , 0);
        }
    }
    ;

var_list
    : ID {
        $$ = new Node("var_list", "");
        $$->children.push_back(new Node("ID", $1));
    }
    | var_list COMMA ID {
        $$ = $1;
        $$->children.push_back(new Node("ID", $3));
    }
    ;

factor : ID {
            // Construct the factor node with ID value
        if (!isVariableDefined($1)) {
            yyerror(("Variable '" + std::string($1) + "' no declarada").c_str());
            exit(1);
        }
        $$ = new Node("factor", $1 , "ID"); // Agregar el tipo de la variable al nodo "factor"
        }
       | CTE_INT {
            // Construct the factor node with CTE_INT value
            std::stringstream ss;
            ss << $1;
            $$ = new Node("factor", ss.str() , "INT"); // Agregar el tipo "INT" al nodo "factor
         
        
        }
       | CTE_FLOAT {
            // Construct the factor node with CTE_FLOAT value
            std::stringstream ss;
            ss << $1;
            $$ = new Node("factor", ss.str(), "FLOAT"); // Agregar el tipo "FLOAT" al nodo "factor
         
        }
       | LEFT_PAREN expression RIGHT_PAREN {
            // Construct the factor node with expression value
            $$ = $2;
        }
       | PLUS factor {
            // Construct the factor node with PLUS factor value
            $$ = $2;
        }
       | MINUS factor {
            // Construct the factor node with MINUS factor value
            $$ = $2;
        }
       ;

type : INT {
    $$ = new Node("type", "INT");
}
     | FLOAT {
         $$ = new Node("type", "FLOAT");
     }
     | VOID {
         $$ = new Node("type", "VOID");
     }
     ;

term : factor {
            $$ = $1;
        }
     | term TIMES factor {
         $$ = new Node("term", "*");
         $$->children.push_back($1);
         $$->children.push_back($3);
     }
     | term DIVIDE factor {
         $$ = new Node("term", "/");
         $$->children.push_back($1);
         $$->children.push_back($3);
     }
     ;

expression : term {
                $$ = $1;
            }
           | expression PLUS term {
               $$ = new Node("expression", "+");
               $$->children.push_back($1);
               $$->children.push_back($3);
           }
           | expression MINUS term {
               $$ = new Node("expression", "-");
               $$->children.push_back($3);
           }
           ;

comparison : expression
           | expression GREATER_THAN expression {
               $$ = new Node("comparison", ">");
               $$->children.push_back($1);
               $$->children.push_back($3);
           }
           | expression LESS_THAN expression {
               $$ = new Node("comparison", "<");
               $$->children.push_back($1);
               $$->children.push_back($3);
           }
           | expression NOT_EQUALS expression {
               $$ = new Node("comparison", "!=");
               $$->children.push_back($1);
               $$->children.push_back($3);
           }
           ;


assignment : ID EQUALS expression {
             if (!isVariableDefined($1)) {
                yyerror(("Error: Variable '" + std::string($1) + "' no declarada").c_str());
                exit(1);
                }
                
                $$ = new Node("assignment", "=");
                $$->children.push_back(new Node("ID", $1));
                $$->children.push_back($3);
            }
           ;

print_statement : PRINT LEFT_PAREN list_of_expressions RIGHT_PAREN {
                    $$ = new Node("print_statement", "print");
                    for (auto& child : $3->children) {
                        $$->children.push_back(child);
                    }
                 }
                | PRINT LEFT_PAREN list_of_cte_strings RIGHT_PAREN {
                    $$ = new Node("print_statement", "print");
                    for (auto& child : $3->children) {
                        $$->children.push_back(child);
                    }
                }
                ;

if_statement : IF LEFT_PAREN comparison RIGHT_PAREN LEFT_BRACE statements RIGHT_BRACE {
                  $$ = new Node("if_statement", "if");
                  $$->children.push_back($3);
                  $$->children.push_back($6);
                  $$->isIfElse = false; // Set isIfElse flag to false
              }
             | IF LEFT_PAREN comparison RIGHT_PAREN LEFT_BRACE statements RIGHT_BRACE ELSE LEFT_BRACE statements RIGHT_BRACE {
                 $$ = new Node("if_statement", "if_else");
                 $$->children.push_back($3);
                 $$->children.push_back($6);
                 $$->children.push_back($10);
                $$->isIfElse = true; // Set isIfElse flag to true
              }
              ;

while_statement : DO LEFT_BRACE statements RIGHT_BRACE WHILE LEFT_PAREN comparison RIGHT_PAREN {
                     $$ = new Node("while_statement", "while");
                     $$->children.push_back($3); // statements
                     $$->children.push_back($7); // comparison
                 }
                 ;


list_of_cte_strings : CTE_STRING {
                        $$ = new Node("list_of_cte_strings", $1);
                     }
                    | list_of_cte_strings COMMA CTE_STRING {
                        $$ = $1;
                        $$->children.push_back(new Node("CTE_STRING", $3));
                     }
                     ;

list_of_expressions : expression {
                        $$ = new Node("list_of_expressions", "");
                        $$->children.push_back($1);
                     }
                    | list_of_expressions COMMA expression {
                        $$ = $1;
                        $$->children.push_back($3);
                     }
                     ;

%%


