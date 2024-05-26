#include "semantic_cube.h"
#include <iostream>
#include <string>


std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_map<std::string, std::string>>> semanticCube;


std::string toUpper(const std::string &str) {
    std::string upperStr = str;
    for (char &c : upperStr) {
        c = toupper(c);
    }
    return upperStr;
}

void initializeCube() {
    semanticCube["INT"]["INT"]["+"] = "INT";
    semanticCube["INT"]["INT"]["-"] = "INT";
    semanticCube["INT"]["INT"]["*"] = "INT";
    semanticCube["INT"]["INT"]["/"] = "INT";

    semanticCube["FLOAT"]["FLOAT"]["+"] = "FLOAT";
    semanticCube["FLOAT"]["FLOAT"]["-"] = "FLOAT";
    semanticCube["FLOAT"]["FLOAT"]["*"] = "FLOAT";
    semanticCube["FLOAT"]["FLOAT"]["/"] = "FLOAT";

    semanticCube["INT"]["FLOAT"]["+"] = "FLOAT";
    semanticCube["INT"]["FLOAT"]["-"] = "FLOAT";
    semanticCube["INT"]["FLOAT"]["*"] = "FLOAT";
    semanticCube["INT"]["FLOAT"]["/"] = "FLOAT";

    semanticCube["FLOAT"]["INT"]["+"] = "FLOAT";
    semanticCube["FLOAT"]["INT"]["-"] = "FLOAT";
    semanticCube["FLOAT"]["INT"]["*"] = "FLOAT";
    semanticCube["FLOAT"]["INT"]["/"] = "FLOAT";
}



std::string getResultType(const std::string &leftType, const std::string &rightType, const std::string &op) {
    std::string upperLeftType = toUpper(leftType);
    std::string upperRightType = toUpper(rightType);
    std::string upperOp = toUpper(op);

    if (semanticCube.find(upperLeftType) != semanticCube.end() &&
        semanticCube[upperLeftType].find(upperRightType) != semanticCube[upperLeftType].end() &&
        semanticCube[upperLeftType][upperRightType].find(upperOp) != semanticCube[upperLeftType][upperRightType].end()) {
        return semanticCube[upperLeftType][upperRightType][upperOp];
    } else {
        std::cerr << "Error: Operación no válida entre tipos '" << leftType << "' y '" << rightType << "' con operador '" << op << "'\n";
        exit(1);
    }
    return "UNKNOWN";
}


