#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

void vvv(int *str)
{
    unsigned int idx;
    for (idx = 0; idx < 10; ++idx)
    {
        printf("%c", str[idx] ^ (idx % 10));
    }
}

int v[] = {114, 103, 119, 50, 91, 113, 116, 51, 123, 96, 12, 87, 11, 74, 37, 110, 102, 93, 119, 52, 53, 55, 50, 87, 56, 12, 89, 112, 104, 124, 99, 117, 100, 55, 102, 126, 118, 55, 127, 108, 12, 125, 84, 124, 13, 53, 94, 119, 112, 97, 99, 115, 54, 117, 0, 12, 141, 44, 99, 102};

void hoge(int ans, int size, int cnt, int _ans)
{
    if ((ans *= cnt) > 0 && !(ans < 0))
    {
        if (ans > 3)
        {
            vvv(&v[30]);
        }
        if (ans < 0)
        {
            printf("ctf4b{h0");
        }
        else
        {
            vvv(&v[0]);
        }
        if (ans == 5)
        {
            printf("g3_1s_p0");
        }
        else
        {
            vvv(&v[15]);
        }
        vvv(&v[45]);
    }
}

int main()
{
    int pid = -1;
    int size = 10;
    int ans = 0;

    puts("I will generate 10 child processes.");
    puts("They also might generate additional child process.");
    puts("Please tell me each process id in order to identify them!");
    puts("");
    srand((unsigned int)time(NULL));
    for (int idx = 0; idx < size; ++idx)
    {
        pid = fork();
        if (pid < 1)
        {
            return 1;
        }
        ++ans;
        if (rand() % 3 == 1)
        {
            pid = fork();
            if (pid < 1)
            {
                return 1;
            }
            ++ans;
        }

        int ans = -1;
        puts("Please give me my child pid!");
        scanf("%d", &ans);
        if (pid == ans)
        {
            puts("ok");
        }
        else
        {
            puts("This is NOT my child pid!");
            return 1;
        }
    }
    wait(0);
    int cnt = 0;
    puts("How many children were born?");
    scanf("%d", &cnt);
    if (ans == cnt && ans >= size)
    {
        hoge(ans, size, cnt, ans);
    }
    else
    {
        puts("You didn't understand me...bye");
    }
}
