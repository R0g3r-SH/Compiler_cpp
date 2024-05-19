#!/bin/bash
rm -f lex.yy.c y.tab.* tester logs.txt
# Step 1: Run Bison to generate the parser
byacc -d parser.y
if [ $? -ne 0 ]; then
    echo "Bison failed"
    exit 1
fi

# Step 2: Run Flex to generate the scanner
flex scanner.l
if [ $? -ne 0 ]; then
    echo "Flex failed"
    exit 1
fi

# Step 3: Compile the program
g++ -o tester main_test.cpp directory_manager.cpp lex.yy.c y.tab.c -lfl
if [ $? -ne 0 ]; then
    echo "Compilation failed"
    exit 1
fi

# Step 4: Run the program with the input file
./tester
