#ifndef QUADRUPLE_MANAGER_H
#define QUADRUPLE_MANAGER_H

#include <queue>
#include <string>
#include <fstream>
#include <vector>


struct Quadruple {
    std::string op;
    std::string arg1;
    std::string arg2;
    std::string result;


};


extern std::vector<Quadruple> quadruples;

std::string getNextTemporary();

std::string getNextLabel(); 

void addQuadruple(const std::string &op, const std::string &arg1, const std::string &arg2, const std::string &result);

void printQuadruples(std::ofstream &logFile);

void clearQuadruples();





#endif // QUADRUPLE_MANAGER_H
