#ifndef _yy_defines_h_
#define _yy_defines_h_

#define PROGRAM 257
#define ID 258
#define SEMI_COLON 259
#define VAR 260
#define COMMA 261
#define POINTS 262
#define INT 263
#define FLOAT 264
#define IF 265
#define ELSE 266
#define WHILE 267
#define LEFT_BRACE 268
#define RIGHT_BRACE 269
#define LEFT_PAREN 270
#define RIGHT_PAREN 271
#define EQUALS 272
#define GREATER_THAN 273
#define LESS_THAN 274
#define NOT_EQUALS 275
#define PLUS 276
#define MINUS 277
#define TIMES 278
#define DIVIDE 279
#define CTE_INT 280
#define CTE_FLOAT 281
#define CTE_STRING 282
#define VOID 283
#define PRINT 284
#define DO 285
#define END 286
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

   
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;

#endif /* _yy_defines_h_ */
