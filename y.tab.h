#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include "syntax_tree.h"
#ifndef _yy_defines_h_
#define _yy_defines_h_

#define PROGRAM 257
#define ID 258
#define SEMI_COLON 259
#define MAIN 260
#define VAR 261
#define COMMA 262
#define POINTS 263
#define INT 264
#define FLOAT 265
#define IF 266
#define ELSE 267
#define WHILE 268
#define LEFT_BRACE 269
#define RIGHT_BRACE 270
#define LEFT_PAREN 271
#define RIGHT_PAREN 272
#define EQUALS 273
#define GREATER_THAN 274
#define LESS_THAN 275
#define NOT_EQUALS 276
#define PLUS 277
#define MINUS 278
#define TIMES 279
#define DIVIDE 280
#define CTE_INT 281
#define CTE_FLOAT 282
#define CTE_STRING 283
#define VOID 284
#define PRINT 285
#define DO 286
#define END 287
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union YYSTYPE {
    char *str;
    int num;
    float fnum;
    Node* node; 
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;

#endif /* _yy_defines_h_ */
