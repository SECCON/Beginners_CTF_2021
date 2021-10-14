#include "instruction.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <err.h>

void print_banner();

int main() {
    struct emulator *emu = calloc(sizeof(struct emulator), 0);
    init_instructions(emu);

    print_banner();

    puts("loading to memory...");
    load_to_mem(&emu->memory, stdin);
    puts("running emulator...");
    while (1) {
        uint8_t pc = get_mem_pc(emu);
        emu->instructions[pc](emu);
        inc_pc(emu);
    }
}

void print_banner() {
    system("cat banner.txt");
}

__attribute__((constructor))
void setup() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    alarm(60);
}
