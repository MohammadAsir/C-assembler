
/*
 * Program: assem.c
 * Purpose: simulate VSM
 * Author: Mohammad Shaker Asir
 * Date: 11/10/2023
 */

#include <stdio.h>

/*
 * Function: binstr2num
 * Purpose: find the hex value of a 16bit long binary input
 *
 * Parameters:
 *  *s: pointer pointing to the char of the binary string
 *
 * returns: the unsigned value of the binary string
 */
unsigned short binstr2num(char* s) {
    unsigned short num = 0; // the variable i will store result in
    s = s + 15; // moving to the least significant bit
    for(int i = 0; i < 16; i++) { // loop through all bits of binary string
        if(*s == '1') { // if the bit is 1
            num += (1 << i); // multiply by 2 to the power of i
        }
        s--; // move to the next bit
    }
    return num;
}

/*
 * Function: dump
 * Purpose: Print Memory dump
 *
 * Parameters:
 *  memory[] : array used for memory
 *  accumulator : holds and modifies the return value
 *  IR: unsigned short (value of binary input)
 *  opcode: unsigned short representing the opcode value
 *  opn: unsigned short representing the operand value
 *
 * Prints: the memory dump in the specified format
 */
void dump(unsigned short memory[], int accumulator, int PC, unsigned short IR, unsigned short opcode, unsigned short opn) {
    // Print the state of the registers
    printf("REGISTERS:\n");
    printf("accumulator\t\t0x%04X\n", accumulator);
    printf("instructionCounter\t0x%04X\n", PC);
    printf("instructionRegister\t0x%04X\n", IR);
    printf("opCode\t\t\t0x%04X\n", opcode);
    printf("operand\t\t\t0x%04X\n\n", opn);

    // Print the code segment
    printf("CODE:\n");
    printf(" 0 1 2 3 4 5 6 7 8 9\n");
    for(int i = 0; i < 100; i += 10) {
        printf("%04d ", i);
        for(int j = 0; j < 10; ++j) {
            printf("%02X ", memory[i + j] & 0xFF); // printing memory values
        }
        printf("\n");
    }

    printf("...\n"); // separator

    // Print the data segment
    printf("DATA:\n");
    printf(" 0 1 2 3 4 5 6 7 8 9\n");
    for(int i = 1024; i < 1124; i += 10) {
        printf("%d ", i);
        for(int j = 0; j < 10; ++j) {
            printf("%02X ", memory[i + j] & 0xFF); // printing memory values
        }
        printf("\n");
    }
}

/*
 * Function: main
 * Purpose: Read binary strings and execute the instructions they represent
 *
 * Prints: Final result of binary instructions and memory dump
 */
int main() {
    unsigned short memory[2048]; // memory register
    int accumulator = 0; // Accumulator register
    unsigned short IR = 0; // instruction register holds the current instruction
    int PC = 0; // Program Counter
    int count = 0; // index for memory
    char binary_string[17]; // Char array for binary input
    unsigned short num; // variable for each instruction

    while(scanf("%16s", binary_string) == 1) { // take 16-char instructions
        binary_string[16] = '\0'; // null-terminate the string
        num = binstr2num(binary_string); // convert to unsigned short
        memory[count] = num; // store in memory array
        count++;
        if (num == 0x0) { // break if instruction is 0
            break;
        }
    }

    unsigned short opcode = 0;
    unsigned short opn;

    do {
        IR = memory[PC]; // get the current instruction
        opcode = IR >> 12; // get opcode
        opn = IR & 0xFFF; // get operand
        int mnem = IR & 0x0800; // get mnemonic using bitmask

        switch(opcode) { // execute based on opcode
            case 0: // end of program
                PC++;
                break;
            case 1: // LOAD
                accumulator = (mnem == 0) ? memory[opn / 2] : opn;
                PC++;
                break;
            case 2: // STORE
                memory[opn / 2] = accumulator;
                PC++;
                break;
            case 3: // READ
                scanf("%16s", binary_string);
                unsigned short res = binstr2num(binary_string) & 0xFFF;
                memory[opn / 2] = res;
                PC++;
                break;
            case 4: // WRITE
                printf("%d\n", memory[opn / 2]);
                PC++;
                break;
            case 5: // ADD
                accumulator += (mnem == 1) ? opn : memory[opn / 2];
                PC++;
                break;
            case 6: // SUB
                accumulator -= (mnem == 1) ? opn : memory[opn / 2];
                PC++;
                break;
            case 7: // MUL
                accumulator *= (mnem == 1) ? opn : memory[opn / 2];
                PC++;
                break;
            case 8: // DIV
                accumulator /= (mnem == 1) ? opn : memory[opn / 2];
                PC++;
                break;
            case 9: // MOD
                accumulator %= (mnem == 1) ? opn : memory[opn / 2];
                PC++;
                break;
            case 10: // NEG
                accumulator = -accumulator;
                PC++;
                break;
            case 11: // NOP
                PC++;
                break;
            case 12: // JMP
                PC = opn / 2;
                break;
            case 13: // JNEG
                PC = (accumulator < 0) ? opn / 2 : PC + 1;
                break;
            case 14: // JZERO
                PC = (accumulator == 0) ? opn / 2 : PC + 1;
                break;
        }
    } while(opcode != 15); // halt the program on opcode 15

    dump(memory, accumulator, PC, IR, opcode, opn);
}
