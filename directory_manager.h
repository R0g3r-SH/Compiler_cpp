// semantic_cube.h

// semantic_cube.h

#ifndef SEMANTIC_CUBE_H
#define SEMANTIC_CUBE_H

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <fstream>


struct VariableInfo {
    std::string type;
    // Other relevant fields...
};

struct FunctionInfo {
    std::string returnType;
    // Other relevant fields...
};

extern std::map<std::string, VariableInfo> variableDirectory;
extern std::map<std::string, FunctionInfo> functionDirectory;

void addVariableToDirectory(const std::string& name, const std::string& type);
void addFunctionToDirectory(const std::string& name, const std::string& returnType);
void printVariableDirectory(std::ofstream& file);

#endif // SEMANTIC_CUBE_H

