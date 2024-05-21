#ifndef STACKS_H
#define STACKS_H

#include <stack>
#include <string>

// Define the necessary stacks
extern std::stack<std::string> operators;
extern std::stack<int> operands;
extern std::stack<std::string> types;
extern std::stack<int> jumps;

#endif // STACKS_H
