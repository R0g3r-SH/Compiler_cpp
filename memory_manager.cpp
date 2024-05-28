
#include <stdexcept>
#include <fstream>
#include <iostream>
#include "memory_manager.h"

MemoryManager memoryManager(5001, 6001, 7001);

MemoryManager::MemoryManager(int intStart, int floatStart, int tempStart)
    : intCounter(intStart), floatCounter(floatStart), tempCounter(tempStart) {}

int MemoryManager::allocateInt(const std::string &var)
{
    if (varToAddress.find(var) != varToAddress.end())
    {
        return varToAddress[var];
    }
    if (intCounter > 6000)
    {
        throw std::runtime_error("Integer memory overflow");
    }
    varToAddress[var] = intCounter++;
    return varToAddress[var];
}

int MemoryManager::allocateFloat(const std::string &var)
{
    if (varToAddress.find(var) != varToAddress.end())
    {
        return varToAddress[var];
    }
    if (floatCounter > 7000)
    {
        throw std::runtime_error("Float memory overflow");
    }
    varToAddress[var] = floatCounter++;
    return varToAddress[var];
}

int MemoryManager::allocateTemp()
{
    if (tempCounter > 8000)
    {
        throw std::runtime_error("Temporary memory overflow");
    }
    return tempCounter++;
}

void MemoryManager::freeMemory(const std::string &var)
{
    varToAddress.erase(var);
}

int MemoryManager::allocateMemoryByType(const std::string &var, const std::string &type)
{
    if (type == "INT")
    {
        return allocateInt(var);
    }
    else if (type == "FLOAT")
    {
        return allocateFloat(var);
    }
    else if (type == "TEMP")
    {
        return allocateTemp();
    }
    else
    {
        throw std::runtime_error("Unknown type");
        return -1;
    }
}

void MemoryManager::printMemory()
{

    std::ofstream logFile("./memory/memory.txt");
    if (!logFile)
    {
        std::cerr << "No se pudo crear el archivo de logs." << std::endl;
        return;
    }
    for (const auto &pair : varToAddress)
    {
        logFile << pair.first << " : " << pair.second << std::endl;
    }
}
