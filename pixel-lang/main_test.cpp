 #include <cstdio>
#include <cstdlib>
#include "y.tab.h"  // Update this line to match the generated header file name

extern FILE *yyin;
extern int yyparse();

int yyerror(const char* s) {
    printf("Error: %s\n", s);
    return 1; // Return non-zero value to indicate error
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s archivo.pixel\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("No se pudo abrir el archivo %s\n", argv[1]);
        return 1;
    }

    yyin = file;

    // Print file line by line
    printf("Contenido del archivo:\n");
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    // Reset file pointer to the beginning of the file
    fseek(file, 0, SEEK_SET);

    // Parse the file
    if (yyparse() == 0) {
        printf("Análisis sintáctico completado con éxito.\n");
    } else {
        printf("Error en el análisis sintáctico.\n");
    }

    fclose(file);
    return 0;
}