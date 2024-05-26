// semantic_cube.h

// semantic_cube.h

#ifndef DIRECTORY_MANAGER_H
#define DIRECTORY_MANAGER_H

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
    std::string name;
    int scope;
    int memoryAllocation;
};

struct FunctionInfo {
    std::string returnType;
    // Other relevant fields...
};

extern std::map<std::string, VariableInfo> symbolTable;
extern std::map<std::string, FunctionInfo> functionDirectory;

void addVariableToDirectory(const std::string& name, const std::string& type , int scope);
bool isVariableDefined(const std::string& name);
void addFunctionToDirectory(const std::string& name, const std::string& returnType);
void printVariableDirectory(std::ofstream& file);


#endif 

