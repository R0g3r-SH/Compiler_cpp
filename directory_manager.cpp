#include "directory_manager.h"

// Define the variable and function directories
std::map<std::string, VariableInfo> symbolTable;
std::map<std::string, FunctionInfo> functionDirectory;
int curr_scope = 0;

void addVariableToDirectory(const std::string &name, const std::string &type, int scope)
{
    if (symbolTable.find(name) != symbolTable.end())
    {
        std::cout << "Error: Variable '" << name << "' already declared\n";
        // terminar el programa
        exit(1);
    }
    else
    {
        VariableInfo info;
        info.type = type;
        info.name = name;
        info.scope = curr_scope;
        symbolTable[name] = info;
    }
}

void addFunctionToDirectory(const std::string &name, const std::string &returnType)
{
    if (functionDirectory.find(name) != functionDirectory.end())
    {
        std::cerr << "Error: Function '" << name << "' already declared\n";
    }
    else
    {
        FunctionInfo info;
        info.returnType = returnType;
        // Initialize other fields if necessary...
        functionDirectory[name] = info;
    }
}

// Función para  sacar un output de las variables en un archivo.txt
void printVariableDirectory(std::ofstream &file)
{
    for (const auto &entry : symbolTable)
    {
        file << "Variable: " << entry.first << " | Type: " << entry.second.type << " | Scope: " << entry.second.scope << std::endl;
    }
}

// Función para checar si una variable ya fue declarada
bool isVariableDefined(const std::string &name)
{
    if (symbolTable.find(name) != symbolTable.end())
    {
        return true;
    }
    std::cout << "Error: Variable '" << name << "' not declared\n";
    // terminar el programa
    exit(1);
    return false;

}
