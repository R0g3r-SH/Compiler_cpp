#include <cstdio>
#include <cstdlib>
#include "y.tab.h" // Update this line to match the generated header file name
#include <iostream>

extern FILE *yyin;
extern int yylex(); // Change to yylex() instead of yyparse()

int yyerror(const char *s)
{
    printf("Error: %s\n", s);
    return 1; // Return non-zero value to indicate error
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Uso: %s archivo.pixel\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("No se pudo abrir el archivo %s\n", argv[1]);
        return 1;
    }

    yyin = file;

    // Print file line by line
    printf("Contenido del archivo:\n");
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file))
    {
        printf("%s", buffer);
    }

    std::cout << std::endl;
    // Reset file pointer to the beginning of the file
    fseek(file, 0, SEEK_SET);

    // Parse the file
    int token;
    while ((token = yylex()) != 0)
    { // Loop until end of file
        switch (token)
        {
        case PROGRAM:
            printf("Token: PROGRAM\n");
            break;
        case ID:
            printf("Token: ID\n");
            break;
        case SEMI_COLON:
            printf("Token: SEMI_COLON\n");
            break;
        case VAR:
            printf("Token: VAR\n");
            break;
        case COMMA:
            printf("Token: COMMA\n");
            break;
        case POINTS:
            printf("Token: POINTS\n");
            break;
        case INT:
            printf("Token: INT\n");
            break;
        case FLOAT:
            printf("Token: FLOAT\n");
            break;
        case IF:
            printf("Token: IF\n");
            break;
        case ELSE:
            printf("Token: ELSE\n");
            break;
        case WHILE:
            printf("Token: WHILE\n");
            break;
        case LEFT_BRACE:
            printf("Token: LEFT_BRACE\n");
            break;
        case RIGHT_BRACE:
            printf("Token: RIGHT_BRACE\n");
            break;
        case LEFT_PAREN:
            printf("Token: LEFT_PAREN\n");
            break;
        case RIGHT_PAREN:
            printf("Token: RIGHT_PAREN\n");
            break;
        case EQUALS:
            printf("Token: EQUALS\n");
            break;
        case GREATER_THAN:
            printf("Token: GREATER_THAN\n");
            break;
        case LESS_THAN:
            printf("Token: LESS_THAN\n");
            break;
        case NOT_EQUALS:
            printf("Token: NOT_EQUALS\n");
            break;
        case PLUS:
            printf("Token: PLUS\n");
            break;
        case MINUS:
            printf("Token: MINUS\n");
            break;
        case TIMES:
            printf("Token: TIMES\n");
            break;
        case DIVIDE:
            printf("Token: DIVIDE\n");
            break;
        case CTE_INT:
            printf("Token: CTE_INT\n");
            break;
        case CTE_FLOAT:
            printf("Token: CTE_FLOAT\n");
            break;
        case CTE_STRING:
            printf("Token: CTE_STRING\n");
            break;
        case VOID:
            printf("Token: VOID\n");
            break;
        case PRINT:
            printf("Token: PRINT\n");
            break;
        case END:
            printf("Token: END\n");
            break;
        default:
            printf("Unrecognized token\n");
            break;
        }
    }

    fclose(file);
    return 0;
}
