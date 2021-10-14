#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

enum {
    A,
    B,
    C,
    D,
    E,
    H,
    L,
    PC_H,
    PC_L,
    SP_H,
    SP_L,
    FLAG,
    REGISTERS_COUNT,
    PC = PC_H,
    SP = SP_H,
    HL = H,
    M
};

struct emulator {
    uint8_t         registers[REGISTERS_COUNT];
    uint8_t         memory[0x4000];
    void (*instructions[0xFF])(struct emulator*);
};

typedef void instruction_t(struct emulator *);

void load_to_mem(struct emulator *emu, FILE *f) {
    char c;
    for(int i = 0, c = fgetc(f); c != EOF && i < 0x4000; i++, c = fgetc(f)) {
        emu->memory[i] = c;
        if (c == 0xC9)
            break;
    }
}

uint16_t get_pc(struct emulator *e) {
    uint16_t ret = 0;
    ret |= (e->registers[PC_H] << 8);
    ret |= e->registers[PC_L];
    return ret;
}

uint16_t get_hl(struct emulator *e) {
    uint16_t ret = 0;
    ret |= (e->registers[H] << 8);
    ret |= e->registers[L];
    return ret;
}

uint16_t get_sp(struct emulator *e) {
    uint16_t ret = 0;
    ret |= (e->registers[SP_H] << 8);
    ret |= e->registers[SP_L];
    return ret;
}

uint8_t get_mem_pc(struct emulator *e) {
    return e->memory[get_pc(e)];
}

uint8_t get_m(struct emulator *e) {
    return e->memory[get_hl(e)];
}

void inc_pc(struct emulator *e) {
    if (e->registers[PC_L] == 0xFF) {
        e->registers[PC_L] = 0;
        e->registers[PC_H]++;
    } else {
        e->registers[PC_L]++;
    }
}
