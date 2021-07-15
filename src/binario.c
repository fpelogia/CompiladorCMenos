#include <stdio.h>
#include <stdint.h>

typedef union{
    struct{
        unsigned int opcode: 7; // 7 bits
        unsigned int rs2: 5; // 5 bits
        unsigned int funct3: 3; // 3 bits
        unsigned int rs1: 5; // 5 bits
        unsigned int rd: 5; // 5 bits
        unsigned int funct7: 7; // 7 bits
    };
    unsigned int valor_bin: 32;// 32 bits

} instr_tipo_R;

int main(){
    // add x3,x2, x3 
    // 0000000 00011 00010 000 00011 0110011
    // 0x3101B3
    // 3211699
    instr_tipo_R inst;
    inst.funct7 = 0;
    inst.rs2 = 3;
    inst.rs1 = 2;
    inst.funct3 = 0;
    inst.rd = 3;
    inst.opcode = 51;//0x33
    printf("HAHA:\n%x\n", inst.valor_bin);

}
