class VirtualMachine:
    def __init__(self):
        self.memory = {}
        self.labels = {}
        self.pc = 0  # Program counter

    def get_value(self, arg):
            return self.memory.get(int(arg), 0)

    def set_value(self, arg, value):
            self.memory[int(arg)] = value

    def execute_code(self, instructions):
        print("Executing code...")
        # First pass: collect labels
        for idx, instruction in enumerate(instructions):
            if instruction[0] == 'LABEL':
                self.labels[instruction[3]] = idx

        while self.pc < len(instructions):
            instruction = instructions[self.pc]
            op = instruction[0]
            arg1 = instruction[1]
            arg2 = instruction[2]
            arg3 = instruction[3]

            if op == '=':
                self.set_value(arg3, int(arg1))
            elif op == '>':
                if self.get_value(arg1) > self.get_value(arg2):
                    self.pc = self.labels[arg3] if arg3 in self.labels else int(arg3) - 1
            elif op == 'GOTO_FALSE':
                if not self.get_value(arg1):
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

        print("Execution completed.")


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
