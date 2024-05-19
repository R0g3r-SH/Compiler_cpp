#include "directory_manager.h"

// Define the variable and function directories
std::map<std::string, VariableInfo> variableDirectory;
std::map<std::string, FunctionInfo> functionDirectory;

void addVariableToDirectory(const std::string& name, const std::string& type) {
    if (variableDirectory.find(name) != variableDirectory.end()) {
        std::cerr << "Error: Variable '" << name << "' already declared\n";
        //exit(EXIT_FAILURE); // Exit the program due to the error
    } else {
        VariableInfo info;
        info.type = type;
        // Initialize other fields if necessary...
        variableDirectory[name] = info;
    }
}

void addFunctionToDirectory(const std::string& name, const std::string& returnType) {
    if (functionDirectory.find(name) != functionDirectory.end()) {
        std::cerr << "Error: Function '" << name << "' already declared\n";
    } else {
        FunctionInfo info;
        info.returnType = returnType;
        // Initialize other fields if necessary...
        functionDirectory[name] = info;
    }
}

// Función para  sacar un output de las variables en un archivo.txt 
void printVariableDirectory(std::ofstream& file) {
    for (const auto& entry : variableDirectory) {
        file << "Variable: " << entry.first << ", Type: " << entry.second.type << "\n";
    }
}

