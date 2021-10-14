#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOTE 0x10

char *note[MAX_NOTE];

void readline(char *buf) {
  char c;
  while ((read(0, &c, 1) == 1) && c != '\n')
    *(buf++) = c;
}
void print(const char *msg) {
  if (write(1, msg, strlen(msg)) < 0)
    _exit(1);
}
int readi(void) {
  char buf[0x10];
  if (read(0, buf, sizeof(buf)) < 0)
    _exit(1);
  return atoi(buf);
}

int menu(void) {
  print("1. new\n2. edit\n3. show\n> ");
  return readi();
}

int main() {
  unsigned int idx, size;
  while (1) {
    switch (menu()) {

    case 1:
      print("index: ");
      idx = (unsigned int)readi();
      if (idx >= MAX_NOTE || note[idx]) {
        print("[-] invalid index\n");
      } else {
        print("size: ");
        size = (unsigned int)readi();
        if (size >= 0x1000) {
          print("[-] size too big\n");
        } else {
          note[idx] = (char*)malloc(size);
        }
      }
      break;

    case 2:
      print("index: ");
      idx = (unsigned int)readi();
      if (idx >= MAX_NOTE || note[idx] == NULL) {
        print("[-] invalid index\n");
      } else {
        print("data: ");
        readline(note[idx]);
      }
      break;

    case 3:
      print("index: ");
      idx = (unsigned int)readi();
      if (idx >= MAX_NOTE || note[idx] == NULL) {
        print("[-] invalid index\n");
      } else {
        print("data: ");
        print(note[idx]);
        print("\n");
      }
      break;

    default:
      print("[+] bye");
      _exit(0);
    }
  }
}
