#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>

#define BUFF_SIZE 0x20

void win() {
    execve("/bin/cat", (char*[3]){"/bin/cat", "flag.txt", NULL}, NULL);
}

void show_stack(unsigned long *stack);

int main() {
    unsigned long target = 0, value = 0;
    char buf[BUFF_SIZE] = {0};
    show_stack(buf);
    printf("Where would you like to rewrite it?\n> ");
    buf[read(STDIN_FILENO, buf, BUFF_SIZE-1)] = 0;
    target = strtol(buf, NULL, 0);
    printf("0x%016lx = ", target);
    buf[read(STDIN_FILENO, buf, BUFF_SIZE-1)] = 0;
    value = strtol(buf, NULL, 0);
    *(long*)target = value;
}

void show_stack(unsigned long *stack) {
    printf("\n%-20s|%-20s\n", "[Addr]", "[Value]");
    puts("====================+===================");
    for (int i = 0; i < 10; i++) {
        printf(" 0x%016lx | 0x%016lx ", &stack[i], stack[i]);
        if (&stack[i] == stack)
            printf(" <- buf");
        if (&stack[i] == ((unsigned long)stack + BUFF_SIZE))
            printf(" <- target");
        if (&stack[i] == ((unsigned long)stack + BUFF_SIZE + 0x8))
            printf(" <- value");
        if (&stack[i] == ((unsigned long)stack + BUFF_SIZE + 0x10))
            printf(" <- saved rbp");
        if (&stack[i] == ((unsigned long)stack + BUFF_SIZE + 0x18))
            printf(" <- saved ret addr");
        puts("");
    }
    puts("");
}

__attribute__((constructor))
void init() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    alarm(60);
}
