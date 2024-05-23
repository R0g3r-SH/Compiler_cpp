
#include <stdexcept>
#include <fstream>
#include <iostream>
#include "memory_manager.h"


MemoryManager memoryManager(5001, 6001, 7001);

MemoryManager::MemoryManager(int intStart, int floatStart, int tempStart)
    : intCounter(intStart), floatCounter(floatStart), tempCounter(tempStart) {}

int MemoryManager::allocateInt(const std::string& var) {
    if (varToAddress.find(var) != varToAddress.end()) {
        return varToAddress[var];
    }
    if (intCounter > 6000) {
        throw std::runtime_error("Integer memory overflow");
    }
    varToAddress[var] = intCounter++;
    return varToAddress[var];
}

int MemoryManager::allocateFloat(const std::string& var) {
    if (varToAddress.find(var) != varToAddress.end()) {
        return varToAddress[var];
    }
    if (floatCounter > 7000) {
        throw std::runtime_error("Float memory overflow");
    }
    varToAddress[var] = floatCounter++;
    return varToAddress[var];
}

int MemoryManager::allocateTemp() {
    if (tempCounter > 8000) {
        throw std::runtime_error("Temporary memory overflow");
    }
    return tempCounter++;
}

void MemoryManager::printMemory(std::ofstream& logFile) const {
    for (const auto& pair : varToAddress) {
        logFile << pair.first << " : " << pair.second << std::endl;
    }
}
