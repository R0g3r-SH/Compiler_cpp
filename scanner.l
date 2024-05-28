%{
#include "y.tab.h"
%}
%option noyywrap

%%

[ \t\r\n]+   { /* Skip whitespace and line breaks */ }
PROGRAM      { printf("Token: PROGRAM\n"); return PROGRAM; }
";"          { return SEMI_COLON; }
VAR          { return VAR; }
","          { return COMMA; }
":"          { return POINTS; } 
"INT"        { yylval.str = strdup(yytext); return INT; }
"FLOAT"      { yylval.str = strdup(yytext); return FLOAT; }
"VOID"       { yylval.str = strdup(yytext); return VOID; }
IF           { return IF; }
ELSE         { return ELSE; }
WHILE        { return WHILE; }
DO           { return DO; }
"{"          { return LEFT_BRACE; }
"}"          { return RIGHT_BRACE; }
"("          { return LEFT_PAREN; }
")"          { return RIGHT_PAREN; }
"="          { return EQUALS; }
">"          { return GREATER_THAN; }
"<"          { return LESS_THAN; }
"!="         { return NOT_EQUALS; }
"+"          { return PLUS; }
"-"          { return MINUS; }
"*"          { return TIMES; }
"/"          { return DIVIDE; }

[0-9]+       { yylval.num = atoi(yytext); return CTE_INT; }

[0-9]+"."[0-9]* { yylval.fnum = atof(yytext); return CTE_FLOAT; }
\"[^\"\n]*\" { yylval.str = strdup(yytext+1); yylval.str[strlen(yylval.str)-1] = '\0'; return CTE_STRING; }
PRINT        { return PRINT; }
END          { return END; }
[a-zA-Z][a-zA-Z0-9]*  { yylval.str = strdup(yytext); return ID; }

%%
