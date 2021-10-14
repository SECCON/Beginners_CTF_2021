#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FLAG_LEN 24

int main() {
    int base = 100;
    char input[FLAG_LEN + 1];
    fgets(input, FLAG_LEN + 1, stdin);
    if (    input[0]    == base + -1 &&
            input[1]     == base + 16 &&
            input[2]     == base + 2 &&
            input[3]     == base + -48 &&
            input[4]     == base + -2 &&
            input[5]     == base + 23 &&
            input[6]     == base + -49 &&
            input[7]     == base + 10 &&
            input[8]     == base + -1 &&
            input[9]     == base + -52 &&
            input[10]     == base + 0 &&
            input[11]     == base + -49 &&
            input[12]     == base + -5 &&
            input[13]     == base + -48 &&
            input[14]     == base + 14 &&
            input[15]     == base + -51 &&
            input[16]     == base + 16 &&
            input[17]     == base + 4 &&
            input[18]     == base + 9 &&
            input[19]     == base + -49 &&
            input[20]     == base + 16 &&
            input[21]     == base + -51 &&
            input[22]     == base + -1 &&
            input[23]     == base + 25)
        puts("Correct!!");
    else
        puts("Incorrect!!");
}
