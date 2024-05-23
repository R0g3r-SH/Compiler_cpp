#ifndef QUADRUPLE_MANAGER_H
#define QUADRUPLE_MANAGER_H

#include <queue>
#include <string>
#include <fstream>

struct Quadruple {
    std::string op;
    std::string arg1;
    std::string arg2;
    std::string result;
};

// Function to generate unique label
std::string generateLabel();

extern std::queue<Quadruple> quadruples;

void generateQuadruple(const std::string &op, const std::string &arg1, const std::string &arg2, const std::string &result);
void printQuadruples(std::ofstream &logFile);
void generateQuadruplesForIf(const std::string& condition);
void generateQuadruplesForIfElse(const std::string& condition);

#endif // QUADRUPLE_MANAGER_H
