#include "quadruple_manager.h"
#include <iostream>

// Define the queue of quadruples
std::queue<Quadruple> quadruples;
const std::string QUADS_FILE = "quads.txt";

void generateQuadruple(const std::string &op, const std::string &arg1, const std::string &arg2, const std::string &result) {
    quadruples.push({op, arg1, arg2, result});
}

void printQuadruples(std::ofstream &logFile) {
    std::ofstream quadFile(QUADS_FILE);
    if (!quadFile) {
        std::cout << "No quads file :( " << std::endl;
        return;
    }

    while (!quadruples.empty()) {
        Quadruple q = quadruples.front();
        quadruples.pop();
        quadFile << "(" << q.op << ", " << q.arg1 << ", " << q.arg2 << ", " << q.result << ")\n";
    }

    quadFile.close();
}

// Function to generate unique label
std::string generateLabel() {
    static int labelCount = 0;
    return "L" + std::to_string(labelCount++);
}
