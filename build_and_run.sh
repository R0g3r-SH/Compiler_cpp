#!/bin/bash
rm -f lex.yy.c y.tab.* tester logs.txt
# Step 1: Run Bison to generate the parser
byacc -d parser.y
if [ $? -ne 0 ]; then
    echo "Bison failed"
    exit 1
fi

# Create a temporary file to hold the includes
echo "#include <iostream>" > tmp_y.tab.h
echo "#include <string>" >> tmp_y.tab.h
echo "#include <vector>" >> tmp_y.tab.h
echo "#include <map>" >> tmp_y.tab.h
echo "#include <memory>" >> tmp_y.tab.h

# Append the content of generated y.tab.h to the temporary file
cat y.tab.h >> tmp_y.tab.h

# Replace y.tab.h with the temporary file
mv tmp_y.tab.h y.tab.h

# Step 2: Run Flex to generate the scanner
flex scanner.l
if [ $? -ne 0 ]; then
    echo "Flex failed"
    exit 1
fi

# Step 3: Compile the program
g++ -o tester main_test.cpp directory_manager.cpp  memory_manager.cpp quadruple_manager.cpp stacks.cpp lex.yy.c y.tab.c -lfl
if [ $? -ne 0 ]; then
    echo "Compilation failed"
    exit 1
fi

# Step 4: Run the program with the input file
./tester
