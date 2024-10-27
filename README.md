
# Assembler Simulator (VSM) - `assem.c`

This project, `assem.c`, is a Virtual Simulation Machine (VSM) written in C. It simulates an assembler, handling various binary instructions and performing memory operations. This simulator can read, process, and execute a series of binary instructions and outputs the final result, along with a memory dump.

## Features

- **Binary to Hex Conversion**: Converts 16-bit binary strings into hexadecimal values.
- **Memory Dump**: Displays the contents of memory, allowing inspection of both code and data segments.
- **Instruction Handling**: Supports a wide range of instructions, including arithmetic operations (add, subtract, multiply, divide), jumps, conditional jumps, and accumulator manipulation.
- **Binary Instruction Parsing**: Parses 16-bit binary strings to execute as instructions.

## Requirements

- A Linux system with GCC for compilation
- Standard libraries: `<stdio.h>`

## Functions

### `binstr2num`
- **Purpose**: Converts a 16-bit binary string to a hexadecimal value.
- **Parameters**: 
  - `*s` (char pointer): Pointer to the binary string.
- **Returns**: The hexadecimal (unsigned short) equivalent of the binary input.

### `dump`
- **Purpose**: Displays the contents of memory in a readable format.
- **Parameters**: 
  - `memory[]` (unsigned short array): Memory array to display.
  - `accumulator` (int): The accumulator register value.
  - `IR` (unsigned short): The instruction register value.
  - `opcode` (unsigned short): The opcode being executed.
  - `opn` (unsigned short): The operand associated with the opcode.
- **Output**: Shows the current state of registers and the contents of memory.

### `main`
- **Purpose**: Takes binary strings as input, converts them, and runs instructions based on parsed values.
- **Process**:
  - Reads and stores each 16-bit binary instruction in memory.
  - Executes instructions by decoding the opcode and performing actions like `LOAD`, `STORE`, `ADD`, etc.
  - Outputs the final memory dump.

## Usage

1. **Compiling**:
   ```bash
   gcc -o assem assem.c
   ```

2. **Running the Program**:
   ```bash
   ./assem
   ```
   The program will start and prompt for 16-bit binary input strings. Each string represents an instruction to execute.

3. **Input Format**:
   - Provide 16-bit binary strings as input. The program will process these and execute the corresponding instructions.

4. **Output**:
   - After processing, the program will print the memory dump, showing the contents of both the code and data segments.

### Example

1. Start the assembler simulation:
   ```bash
   ./assem
   ```

2. Input a binary string (example):
   ```
   0001000000000010
   ```

3. Output after execution:
   ```
   REGISTERS:
   accumulator          0x0000
   instructionCounter   0x0001
   instructionRegister  0x0000
   opCode               0x0001
   operand              0x0002
   ```

## Notes

- Ensure binary strings are exactly 16 characters long for accurate processing.
- Unsupported operations or incorrect binary format may cause unexpected behavior.
