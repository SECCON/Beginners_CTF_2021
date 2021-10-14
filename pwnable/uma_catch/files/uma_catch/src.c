#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void catch();
void naming();
void show();
void dance();
void release();
int read_int();

struct hourse {
    char name[0x20];
    void (*dance)();
};

struct hourse *list[10] = {NULL};

int main() {
    int cmd;
    puts("-*-*-*-*-");
    puts("UMA catch");
    puts("-*-*-*-*-");
    puts("");
    puts("Commands");
    puts("1. catch hourse");
    puts("2. naming hourse");
    puts("3. show hourse");
    puts("4. dance");
    puts("5. release hourse");
    puts("6. exit");

    while (1) {
        puts("");
        printf("command?\n> ");
        cmd = read_int();
        switch (cmd) {
            case 1:
                catch();
                break;
            case 2:
                naming();
                break;
            case 3:
                show();
                break;
            case 4:
                dance();
                break;
            case 5:
                release();
                break;
            case 6:
                exit(0);
            default:
                break;
        }
    }
}

int read_int() {
    char buf[0x10];
    buf[read(0, buf, 0xf)] = 0;

    return atoi(buf);
}

void bay_dance() {
    puts(
        "　　 (＼ノ))／)\n"
        "　　　Ｙ 彡 Ｙ\n"
        "　　　 (●　●)\n"
        "　　　 ∧|　|∧\n"
        "　＿／　(^^)　＼＿\n"
        "　L/／|　￣　|＼L/\n"
        "　　　|　ｘ　|彡\n"
        "　　　ヽ ＿ ノ\n"
        "　　　 |｜｜|\n"
        "　　 〈二)(二〉\n"
    );
    sleep(1);
    puts(
        "　　 (＼ノ))／)\n"
        "　　　Ｙ彡彡Ｙ\n"
        "　　　(●)(●)　/ヲ\n"
        "　　　∧　　∧／／\n"
        "　＿／ |^⌒^| ／\n"
        "　L/／|ヽ二ノ|\n"
        "　　　|　ｘ　|彡\n"
        "　　　ヽ ＿ ノ\n"
        "　　　 |｜｜|\n"
        "　　 〈二)(二〉\n"
    );
    sleep(1);
    puts(
        "　　 (＼ノ))／)\n"
        "　　　Ｙ 彡 Ｙ\n"
        "　　　 (●　●)\n"
        "　　　 ∧|　|∧\n"
        "　＿／　(^^)　＼＿\n"
        "　L/／|　￣　|＼L/\n"
        "　　　|　ｘ　|彡\n"
        "　　　ヽ ＿ ノ\n"
        "　　　 |｜｜|\n"
        "　　 〈二)(二〉\n"
    );
}

void chestnut_dance() {
    puts(
        "　　 (＼ノ))／)\n"
        "　　　Ｙ彡彡Ｙ\n"
        "　　　(●)(●)　/ヲ\n"
        "　　　∧　　∧／／\n"
        "　＿／ |^⌒^| ／\n"
        "　L/／|ヽ二ノ|\n"
        "　　　|　ｘ　|彡\n"
        "　　　ヽ ＿ ノ\n"
        "　　　 |｜｜|\n"
        "　　 〈二)(二〉"
    );
    sleep(1);
    puts(
        "　　 (＼ノ))／)\n"
        "　　　Ｙ 彡 Ｙ\n"
        "　　　 (●　●)\n"
        "　　　 ∧|　|∧\n"
        "　＿／　(^^)　＼＿\n"
        "　L/／|　￣　|＼L/\n"
        "　　　|　ｘ　|彡\n"
        "　　　ヽ ＿ ノ\n"
        "　　　 |｜｜|\n"
        "　　 〈二)(二〉"
    );
    sleep(1);
    puts(
        "　　 (＼ノ))／)\n"
        "　　　Ｙ 彡 Ｙ\n"
        "　　　 (●　●)\n"
        "　　　 ∧|　|∧\n"
        "　＿／　(^^)　＼＿\n"
        "　L/／|　￣　|＼L/\n"
        "　　ミ|　ｘ　|\n"
        "　　　ヽ ＿ ノ\n"
        "　　　 |｜｜|\n"
        "　　 〈二)(二〉"
    );
}

void gray_dance() {
    puts(
        "　　 (＼ノ))／)\n"
        "　　　Ｙ 彡 Ｙ\n"
        "　　　 (●　●)\n"
        "　　　 ∧|　|∧\n"
        "　＿／　(^^)　＼＿\n"
        "　L/／|　￣　|＼L/\n"
        "　　ミ|　ｘ　|\n"
        "　　　ヽ ＿ ノ\n"
        "　　　 |｜｜|\n"
        "　　 〈二)(二〉\n"
    );
    sleep(1);
    puts(
        "　　 (＼ノ))／)\n"
        "　　　Ｙ 彡 Ｙ\n"
        "　　　 (●　●)\n"
        "　　　 ∧|　|∧\n"
        "　＿／　(^^)　＼＿\n"
        "　L/／|　￣　|＼L/\n"
        "　　　|　ｘ　|彡\n"
        "　　　ヽ ＿ ノ\n"
        "　　　 |｜｜|\n"
        "　　 〈二)(二〉\n"
    );
    sleep(1);
    puts(
        "　　 (＼ノ))／)\n"
        "　　　Ｙ彡彡Ｙ\n"
        "　　　(●)(●)　/ヲ\n"
        "　　　∧　　∧／／\n"
        "　＿／ |^⌒^| ／\n"
        "　L/／|ヽ二ノ|\n"
        "　　　|　ｘ　|彡\n"
        "　　　ヽ ＿ ノ\n"
        "　　　 |｜｜|\n"
        "　　 〈二)(二〉\n"
    );
}

int get_index() {
    printf("index?\n> ");
    return read_int();
}

void show() {
    printf(list[get_index()]->name);
}

void catch() {
    int i = get_index();
    list[i] = malloc(sizeof(struct hourse));
    while (1) {
        printf("color?(bay|chestnut|gray)\n> ");
        char buf[10];
        buf[read(0, buf, 9)] = 0;
        if (strncmp(buf, "bay", 3) == 0) { list[i]->dance = bay_dance; break; }
        if (strncmp(buf, "chestnut", 8) == 0) { list[i]->dance = chestnut_dance; break; }
        if (strncmp(buf, "gray", 4) == 0) { list[i]->dance = gray_dance; break; }
    }
}

void dance() {
    int i = get_index();
    list[i]->dance();
}

void naming() {
    int i = get_index();
    printf("name?\n> ");
    fgets(list[i]->name, 0x20, stdin);
}

void release() {
    free(list[get_index()]);
}

__attribute__((constructor))
void init() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    alarm(60);
}
