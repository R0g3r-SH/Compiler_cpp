%{
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "directory_manager.h"

int yyerror(const char* s);


%}

%union {
    char *str;
    int num;
    float fnum;
}

%token PROGRAM ID SEMI_COLON VAR COMMA POINTS INT FLOAT IF ELSE WHILE LEFT_BRACE RIGHT_BRACE LEFT_PAREN RIGHT_PAREN EQUALS GREATER_THAN LESS_THAN NOT_EQUALS PLUS MINUS TIMES DIVIDE CTE_INT CTE_FLOAT CTE_STRING VOID PRINT DO END

%token <str> ID
%type <str> var_list
%type <str> type

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
            addVariableToDirectory( var, $4 );
     
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

assignment : ID EQUALS expression
           ;

expression : term
           | expression PLUS term
           | expression MINUS term
           ;

term : factor
     | term TIMES factor
     | term DIVIDE factor
     ;

factor : ID
       | CTE_INT
       | CTE_FLOAT
       | LEFT_PAREN expression RIGHT_PAREN
       ;

print_statement : PRINT LEFT_PAREN expression RIGHT_PAREN
                ;

if_statement : IF LEFT_PAREN expression RIGHT_PAREN LEFT_BRACE statements RIGHT_BRACE
             | IF LEFT_PAREN expression RIGHT_PAREN LEFT_BRACE statements RIGHT_BRACE ELSE LEFT_BRACE statements RIGHT_BRACE
             ;

while_statement : WHILE LEFT_PAREN expression RIGHT_PAREN LEFT_BRACE statements RIGHT_BRACE
                ;

%%