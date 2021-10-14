#include <stdio.h>
#include <unistd.h>

char *gets(char *s);

int main() {
    char str[0x100];
    gets(str);
    puts(str);
}

__attribute__((constructor))
void setup() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    alarm(60);
}

