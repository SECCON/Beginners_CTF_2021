#include "emulator.h"
#include <string.h>

char read_byte_pc(struct emulator *emu) {
    return emu->memory[emu->registers[PC]++];
}

static void nop(struct emulator *emu) {
    emu->registers[A] = emu->registers[A];
}

static void mov_r_r(struct emulator *emu, uint8_t r1, uint8_t r2) {
    if (r2 == M)
        emu->registers[r1] = get_m(emu);
    else if (r1 == M)
        emu->memory[get_hl(emu)] = emu->registers[r2];
    else
        emu->registers[r1] = emu->registers[r2];
}

static void hlt(struct emulator *emu) {
    printf("sorry I can't halt...\n");
}

static void mvi(struct emulator *emu) {
    uint8_t pc = get_mem_pc(emu);
    inc_pc(emu);
    switch (pc) {
        case 0x06:
            emu->registers[B] = get_mem_pc(emu);
            break;
        case 0x0E:
            emu->registers[C] = get_mem_pc(emu);
            break;
        case 0x16:
            emu->registers[D] = get_mem_pc(emu);
            break;
        case 0x1E:
            emu->registers[E] = get_mem_pc(emu);
            break;
        case 0x26:
            emu->registers[H] = get_mem_pc(emu);
            break;
        case 0x2E:
            emu->registers[L] = get_mem_pc(emu);
            break;
        case 0x36:
            emu->memory[get_hl(emu)] = get_mem_pc(emu);
            break;
        case 0x3E:
            emu->registers[A] = get_mem_pc(emu);
            break;

        default:
            fprintf(stderr, "NOT IMPLEMENTED!!!!\n");
            exit(1);
    }
}

static void mov(struct emulator *emu) {
    uint8_t pc = get_mem_pc(emu);
    switch (pc) {
        case 0x40:
            mov_r_r(emu, B, B);
            break;
        case 0x41:
            mov_r_r(emu, B, C);
            break;
        case 0x42:
            mov_r_r(emu, B, D);
            break;
        case 0x43:
            mov_r_r(emu, B, E);
            break;
        case 0x44:
            mov_r_r(emu, B, H);
            break;
        case 0x45:
            mov_r_r(emu, B, L);
            break;
        case 0x46:
            mov_r_r(emu, B, M);
            break;
        case 0x47:
            mov_r_r(emu, B, A);
            break;
        case 0x48:
            mov_r_r(emu, C, B);
            break;
        case 0x49:
            mov_r_r(emu, C, C);
            break;
        case 0x4A:
            mov_r_r(emu, C, D);
            break;
        case 0x4B:
            mov_r_r(emu, C, E);
            break;
        case 0x4C:
            mov_r_r(emu, C, H);
            break;
        case 0x4D:
            mov_r_r(emu, C, L);
            break;
        case 0x4E:
            mov_r_r(emu, C, M);
            break;
        case 0x4F:
            mov_r_r(emu, C, A);
            break;
        case 0x50:
            mov_r_r(emu, D, B);
            break;
        case 0x51:
            mov_r_r(emu, D, C);
            break;
        case 0x52:
            mov_r_r(emu, D, D);
            break;
        case 0x53:
            mov_r_r(emu, D, E);
            break;
        case 0x54:
            mov_r_r(emu, D, H);
            break;
        case 0x55:
            mov_r_r(emu, D, L);
            break;
        case 0x56:
            mov_r_r(emu, D, M);
            break;
        case 0x57:
            mov_r_r(emu, D, A);
            break;
        case 0x58:
            mov_r_r(emu, E, B);
            break;
        case 0x59:
            mov_r_r(emu, E, C);
            break;
        case 0x5A:
            mov_r_r(emu, E, D);
            break;
        case 0x5B:
            mov_r_r(emu, E, E);
            break;
        case 0x5C:
            mov_r_r(emu, E, H);
            break;
        case 0x5D:
            mov_r_r(emu, E, L);
            break;
        case 0x5E:
            mov_r_r(emu, E, M);
            break;
        case 0x5F:
            mov_r_r(emu, E, A);
            break;
        case 0x60:
            mov_r_r(emu, H, B);
            break;
        case 0x61:
            mov_r_r(emu, H, C);
            break;
        case 0x62:
            mov_r_r(emu, H, D);
            break;
        case 0x63:
            mov_r_r(emu, H, E);
            break;
        case 0x64:
            mov_r_r(emu, H, H);
            break;
        case 0x65:
            mov_r_r(emu, H, L);
            break;
        case 0x66:
            mov_r_r(emu, H, M);
            break;
        case 0x67:
            mov_r_r(emu, H, A);
            break;
        case 0x68:
            mov_r_r(emu, L, B);
            break;
        case 0x69:
            mov_r_r(emu, L, C);
            break;
        case 0x6A:
            mov_r_r(emu, L, D);
            break;
        case 0x6B:
            mov_r_r(emu, L, E);
            break;
        case 0x6C:
            mov_r_r(emu, L, H);
            break;
        case 0x6D:
            mov_r_r(emu, L, L);
            break;
        case 0x6E:
            mov_r_r(emu, L, M);
            break;
        case 0x6F:
            mov_r_r(emu, L, A);
            break;
        case 0x70:
            mov_r_r(emu, M, B);
            break;
        case 0x71:
            mov_r_r(emu, M, C);
            break;
        case 0x72:
            mov_r_r(emu, M, D);
            break;
        case 0x73:
            mov_r_r(emu, M, E);
            break;
        case 0x74:
            mov_r_r(emu, M, H);
            break;
        case 0x75:
            mov_r_r(emu, M, L);
            break;
        case 0x77:
            mov_r_r(emu, M, A);
            break;
        case 0x78:
            mov_r_r(emu, A, B);
            break;
        case 0x79:
            mov_r_r(emu, A, C);
            break;
        case 0x7A:
            mov_r_r(emu, A, D);
            break;
        case 0x7B:
            mov_r_r(emu, A, E);
            break;
        case 0x7C:
            mov_r_r(emu, A, H);
            break;
        case 0x7D:
            mov_r_r(emu, A, L);
            break;
        case 0x7E:
            mov_r_r(emu, A, M);
            break;
        case 0x7F:
            mov_r_r(emu, A, A);

        default:
            fprintf(stderr, "NOT IMPLEMENTED!!!!\n");
            exit(1);
    }
}

static void ret(struct emulator *emu) {
    printf("A register is %d !\n", emu->registers[A]);
    puts("bye");
    exit(0);
}

void init_instructions(struct emulator *emu) {
    for (int i = 0; i <= 0xFF; i++)
        emu->instructions[i] = nop;

    for (int i = 0x40; i < 0x80; i++)
        emu->instructions[i] = mov;
    for (int i = 0x06; i < 0x3F; i+=8)
        emu->instructions[i] = mvi;
    emu->instructions[0x76] = hlt;
    emu->instructions[0xC9] = ret;
}
