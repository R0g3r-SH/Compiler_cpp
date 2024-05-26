class VirtualMachine:
    def __init__(self):
        self.memory = {}
        self.temp_vars = {}
        self.labels = {}
        self.pc = 0  # Program counter

    def get_value(self, arg):
        return self.memory.get(int(arg), 0)
    
    def set_value(self, arg, value):
        self.memory[int(arg)] = value

    def execute_code(self, instructions):
        print("💻 Executing code... ")
        # First pass: collect labels
        print("First pass: collecting labels...")
        for idx, instruction in enumerate(instructions):
            if instruction[0] == 'LABEL':
                self.labels[instruction[3]] = idx

        print("Executing instructions...")
        while self.pc < len(instructions):
            instruction = instructions[self.pc]
            op = instruction[0]
            arg1 = instruction[1]
            arg2 = instruction[2]
            arg3 = instruction[3]


            if op == '=':
                # Review if arg1 is already a memory address
                value_to_assign = int(arg1) if self.memory.get(int(arg1)) is None else self.get_value(arg1)
                self.set_value(arg3, value_to_assign)
            elif op == '>':
                # Review if arg1 is already a memory address
                arg1 = int(arg1) if self.memory.get(int(arg1)) is None else self.get_value(arg1)
                arg2 = int(arg2) if self.memory.get(int(arg2)) is None else self.get_value(arg2)
                if arg1 > arg2:
                    #save the value of the comparison in the memory
                    self.set_value(arg3, 1)
                    #jump to the label next to the comparison
                else:
                    self.set_value(arg3, 0)
                    
            elif op == '<':
                # Review if arg1 is already a memory address
                arg1 = int(arg1) if self.memory.get(int(arg1)) is None else self.get_value(arg1)
                arg2 = int(arg2) if self.memory.get(int(arg2)) is None else self.get_value(arg2)
                
                if arg1 < arg2:
                    #save the value of the comparison in the memory
                    self.set_value(arg3, 1)
                    #jump to the label next to the comparison
                else:
                    self.set_value(arg3, 0)
            
            elif op == '+':
                arg1 = int(arg1) if self.memory.get(int(arg1)) is None else self.get_value(arg1)
                arg2 = int(arg2) if self.memory.get(int(arg2)) is None else self.get_value(arg2)
                self.set_value(arg3, arg1 + arg2)
            elif op == '-':
                arg1 = int(arg1) if self.memory.get(int(arg1)) is None else self.get_value(arg1)
                arg2 = int(arg2) if self.memory.get(int(arg2)) is None else self.get_value(arg2)
                self.set_value(arg3, arg1 - arg2)
            elif op == '*':
                arg1 = int(arg1) if self.memory.get(int(arg1)) is None else self.get_value(arg1)
                arg2 = int(arg2) if self.memory.get(int(arg2)) is None else self.get_value(arg2)
                self.set_value(arg3, arg1 * arg2)

            elif op == '/':
                arg1 = int(arg1) if self.memory.get(int(arg1)) is None else self.get_value(arg1)
                arg2 = int(arg2) if self.memory.get(int(arg2)) is None else self.get_value(arg2)
                self.set_value(arg3, arg1 / arg2)

            elif op == 'GOTO_TRUE':
                condition =int(arg1) if self.memory.get(int(arg1)) is None else self.get_value(arg1)
                if condition:
                    self.pc = self.labels[arg3] - 1

            elif op == 'GOTO_FALSE':
                condition =int(arg1) if self.memory.get(int(arg1)) is None else self.get_value(arg1)
                if not condition:
                    self.pc = self.labels[arg3] - 1
    
            elif op == 'PRINT':
                print("Output:", self.get_value(arg3))
            elif op == 'GOTO':
                self.pc = self.labels[arg3] - 1
            elif op == 'LABEL':
                pass
            else:
                raise ValueError(f"Unknown instruction: {op}")

            self.pc += 1

        print("Execution completed. ⚡")


def preprocess_line(line):
    # Remove leading and trailing spaces and parentheses
    line = line.strip().replace('(', '').replace(')', '')
    parts = [part.strip() for part in line.split(',')]
    # Replace empty parts with default values
    if len(parts) != 4:
        return None
    for i in range(len(parts)):
        if parts[i] == '':
            parts[i] = '0' if i != 3 else ''  # Default to '0' for args, keep '' for labels
    return parts

# Load instructions from the text file
def load_instructions_from_file(file_path):
    instructions = []
    with open(file_path, 'r') as file:
        for line in file:
            processed_line = preprocess_line(line)
            if processed_line:
                instructions.append(tuple(processed_line))
            else:
                print(f"Skipping malformed line: {line.strip()}")

    
    return instructions

# Main function
def main():

    print(" \n  \n 🚀 Starting Virtual Machine... \n")
    vm = VirtualMachine()
    instructions = load_instructions_from_file('./vm/quads.txt')
    for inst in instructions:
        print(inst)  # Debug output to see each instruction
    print("\n")
    vm.execute_code(instructions)

if __name__ == "__main__":
    main()
