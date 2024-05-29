#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <filesystem>
#include <stack> // Add this line to include the <stack> library

#include "y.tab.h" 

#include "directory_manager.h"
#include "memory_manager.h"
#include "quadruple_manager.h"
#include "syntax_tree.h" 
#include "semantic_cube.h"




extern FILE *yyin;
extern int yyparse();

int yyerror(const char* s) {
    std::cerr << "Error: " << s << std::endl;
    return 1; // Return non-zero value to indicate error
}

void analyzeFile(const std::string& filePath, std::ofstream& logFile) {
    FILE *file = fopen(filePath.c_str(), "r");
    if (!file) {
        logFile << "No se pudo abrir el archivo " << filePath << std::endl;
        return;
    }

    yyin = file;

    // Print file name to log
    logFile << "Analizando archivo: " << filePath << std::endl;

    // Reset the symbol table
    symbolTable.clear();

    // Reset the quadruples queue
    clearQuadruples();

    // Parse the file
    if (yyparse() == 0) {
        logFile << "Análisis sintáctico completado con éxito." << std::endl;

        printVariableDirectory(logFile);


        printQuadruples(logFile);

        memoryManager.printMemory();

        fclose(file);

    } else {
        logFile << "Error en el análisis sintáctico." << std::endl;
    }


}

int main() {
    //save the logs in a file folder called logs

    //inicializar cubo semantico
    initializeCube();
    
    
    std::ofstream logFile("logs/log.txt");
    if (!logFile) {
        std::cerr << "No se pudo crear el archivo de logs." << std::endl;
        return 1;
    }

    std::string testsFolder = "tests";
    for (const auto& entry : std::filesystem::directory_iterator(testsFolder)) {
        if (entry.is_regular_file()) {
            analyzeFile(entry.path().string(), logFile);
        }
    }

    logFile.close();
    return 0;
}
