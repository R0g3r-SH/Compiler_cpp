%{
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "directory_manager.h"


%}

%{
int yyerror(const char* s);
%}

%union {
    char *str;
    int num;
    float fnum;

   
}


%token PROGRAM ID SEMI_COLON VAR COMMA POINTS INT FLOAT IF ELSE WHILE LEFT_BRACE RIGHT_BRACE LEFT_PAREN RIGHT_PAREN EQUALS GREATER_THAN LESS_THAN NOT_EQUALS PLUS MINUS TIMES DIVIDE CTE_INT CTE_FLOAT CTE_STRING VOID PRINT DO END

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

type : INT
     | FLOAT
     | VOID
     ;


var_declaration : VAR ID POINTS type {
    printf("Variable declarada\n");
    // Accessing the type attribute using appropriate type
    printf("ID: %s, Type: %s\n", $2.str, $4.str);
    printf("Variable declarada\n");
     //add to symbol table
     addVariableToDirectory(std::string($2.str), std::string($4.str)); 

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
 