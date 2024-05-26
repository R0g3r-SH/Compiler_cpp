#ifndef SEMANTIC_CUBE_H
#define SEMANTIC_CUBE_H

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <unordered_map>



void initializeCube();

std::string getResultType(const std::string &leftType, const std::string &rightType, const std::string &op);


#endif // SEMANTIC_CUBE_H