#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <map>
#include <string>
#include <stdexcept>
#include <fstream>

class MemoryManager {
public:
    MemoryManager(int intStart, int floatStart, int tempStart);

    int allocateInt(const std::string& var);
    int allocateFloat(const std::string& var);
    int allocateTemp();
    void printMemory();
    void freeMemory(const std::string& var);
    int allocateMemoryByType(const std::string& var, const std::string& type);


private:
    int intCounter;
    int floatCounter;
    int tempCounter;
    std::map<std::string, int> varToAddress;
};

extern MemoryManager memoryManager;

#endif // MEMORY_MANAGER_H
