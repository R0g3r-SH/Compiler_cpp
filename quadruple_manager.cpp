#include "quadruple_manager.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>


// Define the queue of quadruples
std::vector<Quadruple> quadruples;

int temporaryCounter = 0; // Counter for generating temporary variables



std::string getNextTemporary() {
    return "T" + std::to_string(temporaryCounter++);
}

std::string getNextLabel() {
    static int labelCount = 0;
    return "LABEL_" + std::to_string(labelCount++);
}


const std::string QUADS_FILE = "./quadruples/quads.txt";

void addQuadruple(const std::string &op, const std::string &arg1, const std::string &arg2, const std::string &result) {
    quadruples.push_back(Quadruple{op, arg1, arg2, result});

}

void printQuadruples(std::ofstream &logFile) {

    
    std::ofstream quadFile(QUADS_FILE);
    if (!quadFile) {
        std::cout << "No quads file :( " << std::endl;
        return;
    }

    while (!quadruples.empty()) {
        Quadruple q = quadruples.front();
        quadruples.erase(quadruples.begin());
        quadFile << "(" << q.op << ", " << q.arg1 << ", " << q.arg2 << ", " << q.result << ")\n";
    }

    quadFile.close();
}




void clearQuadruples() {
    quadruples.clear();
    temporaryCounter = 0; // Reset temporary counter
}