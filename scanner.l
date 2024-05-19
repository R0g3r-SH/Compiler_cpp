%{
#include "y.tab.h"
%}
%option noyywrap

%%


[ \t\r\n]+   { /* Skip whitespace and line breaks */ }
PROGRAM     { printf("Token: PROGRAM\n"); return PROGRAM; }
";"         { return SEMI_COLON; }
VAR         { return VAR; }
","         { return COMMA; }
":"         { return POINTS; } // Match colon
"INT"   { yylval.str = strdup(yytext); return INT; }
"FLOAT"      { yylval.str = strdup(yytext); return FLOAT; }
"VOID"       { yylval.str = strdup(yytext); return VOID; }
IF          { return IF; }
ELSE        { return ELSE; }
WHILE       { return WHILE; }
DO          { return DO; }
"{"         { return LEFT_BRACE; }
"}"         { return RIGHT_BRACE; }
"("         { return LEFT_PAREN; }
")"         { return RIGHT_PAREN; }
"="        { return EQUALS; } // Example of matching a double equals sign
">"         { return GREATER_THAN; }
"<"         { return LESS_THAN; }
"!="        { return NOT_EQUALS; } // Example of matching not equals
"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return TIMES; }
"/"         { return DIVIDE; }
[0-9]+      { yylval.num = atoi(yytext); return CTE_INT; } // Match integers
[0-9]+"."[0-9]*  { yylval.fnum = atof(yytext); return CTE_FLOAT; } // Match floating-point numbers
\"[^\"\n]*\" { yylval.str = strdup(yytext+1); yylval.str[strlen(yylval.str)-1] = '\0'; return CTE_STRING; } // Match string literals
PRINT       { return PRINT; }
END         { return END; }
[a-zA-Z][a-zA-Z0-9]*   { yylval.str = strdup(yytext); return ID; }
    
%%
