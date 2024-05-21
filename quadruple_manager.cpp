#include "quadruple_manager.h"

std::queue<Quadruple> quadruples;

void generateQuadruple(const std::string &op, const std::string &arg1, const std::string &arg2, const std::string &result) {
    quadruples.push({op, arg1, arg2, result});
}

void printQuadruples(std::ofstream &logFile) {
    while (!quadruples.empty()) {
        Quadruple q = quadruples.front();
        quadruples.pop();
        logFile << "(" << q.op << ", " << q.arg1 << ", " << q.arg2 << ", " << q.result << ")\n";
    }
}
