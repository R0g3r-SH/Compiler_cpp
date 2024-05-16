%{
#include <stdio.h>
%}

%{
int yyerror(const char* s);
%}

%union {
    char *str;
    int num;
    float fnum;
}


%token PROGRAM ID SEMI_COLON VAR COMMA POINTS INT FLOAT IF ELSE WHILE LEFT_BRACE RIGHT_BRACE LEFT_PAREN RIGHT_PAREN EQUALS GREATER_THAN LESS_THAN NOT_EQUALS PLUS MINUS TIMES DIVIDE CTE_INT CTE_FLOAT CTE_STRING VOID PRINT END

%%

program : PROGRAM ID SEMI_COLON statements END { printf("Programa válido\n"); }
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

var_declaration : VAR ID POINTS type
                ;

type : INT
     | FLOAT
     | VOID
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
 