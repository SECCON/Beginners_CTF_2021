#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ptrace.h>

#define N 256


char e[27] = {0x80, 0x97, 0x85, 0xD7, 0x81, 0x98, 0x87, 0xD2, 0x87, 0xBC, 0x9A, 0xD3, 0x96, 0xBC, 0x87, 0xD0, 0x80, 0x91, 0x9A, 0x93, 0x97, 0xBC, 0x91, 0x80, 0xD7, 0xDC, 0x9E};

void generate_key(char *key) {
    strcpy(key, "nickelodeon");
}

void swap(unsigned char *a, unsigned char *b) {
    unsigned char tmp = *a;
    *a = *b;
    *b = tmp;
}

char *rc4(char *const text, char *const key) {
    int text_len = strlen(text);
    char *ret = malloc(text_len);
    unsigned char s[N];

    int key_len = strlen(key);
    for (int i = 0; i < N; i++)
        s[i] = i;

    for (int i = 0, j = 0; i < N; i++)
        j = (j + s[i] + key[i % key_len]) % N, swap(&s[i], &s[j]);

    for(int i = 0, j = 0, n = 0; n < text_len; n++) {
        swap(&s[i], &s[j]);
        ret[n] = (s[(s[i] + s[j]) %N]) ^ text[n];
    }

    return ret;
}

int main() {
    char *key;
    int i = 0;
    while(1) {
        switch (i) {
            case 0:
                 {
                    int offset = 0;
                    if (ptrace(PTRACE_TRACEME, 0, 1, 0) == 0)
                        offset = 2;
                    if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1)
                        offset *= 3;
                    if (offset != 2*3)
                        fprintf(stderr, "prease not trace me...\n"), exit(1);
                }
                break;
            case 1:
                key = malloc(0x10);
                break;
            case 2:
                generate_key(key);
                break;
            case 3:
                rc4(e, key);
                break;
            case 4:
                puts("flag decrypted. bye.");
                break;
            case 5:
                exit(0);
        }
        i++;
    }
}
