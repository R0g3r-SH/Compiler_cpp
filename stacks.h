#ifndef STACKS_H
#define STACKS_H

#include <stack>
#include <string>

// Declare the necessary stacks as extern
extern std::stack<std::string> operators;
extern std::stack<int> operands;
extern std::stack<std::string> types;
extern std::stack<int> jumps;

#endif // STACKS_H
