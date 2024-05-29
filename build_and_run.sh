#!/bin/bash
rm -f lex.yy.c y.tab.* tester logs.txt

# remove the cuads file  and the output file
rm -f ./quadruples/quads.txt
rm -f ./vm/quads.txt

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
echo '#include "syntax_tree.h"' >> tmp_y.tab.h

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
g++ -o tester main.cpp  semantic_cube.cpp syntax_tree.cpp directory_manager.cpp memory_manager.cpp quadruple_manager.cpp stacks.cpp  lex.yy.c y.tab.c -lfl
if [ $? -ne 0 ]; then
    echo "Compilation failed"
    exit 1
fi

# Step 4: Run the program with the input file
./tester

#!/bin/bash

# Set path to cuads.txt
cuads_file="./quadruples/quads.txt"
vm_folder="./vm/quads.txt"

# Set timeout limit
timeout_limit=3
timeout_counter=0

# Wait until the file is created or timeout
# Wait until the file is created or timeout
echo -n "Waiting for the file to be created ..."
while [ ! -f "$cuads_file" ] && [ $timeout_counter -lt $timeout_limit ]; do
  sleep 1
  ((timeout_counter++))
  echo -n "."
done



# Check if the file was created or timeout occurred
if [ ! -f "$cuads_file" ]; then
  echo "File not created within timeout. Exiting."
  exit 1
else
  echo "File $cuads_file is created."
fi

# Attempt to copy the cuads file to the vm folder
echo "Copying cuads file to vm folder..."
cp "$cuads_file" "$vm_folder"

# Check if the file was copied successfully
if [ $? -eq 0 ]; then
  echo "File $cuads_file copied to $vm_folder successfully."
else
  echo "Failed to copy $cuads_file to $vm_folder."
  exit 1
fi

# Run the Python virtual machine script
echo "Running Python virtual machine script..."
python3 ./vm/virtual_machine.py
