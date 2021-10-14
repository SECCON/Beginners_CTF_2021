#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

int main(void) {
  int rsock, wsock;
  struct sockaddr_in addr, client;
  int len;

  rsock = socket(AF_INET, SOCK_STREAM, 0);

  if (rsock < 0) {
    perror("Failed to set socket.");
    return 1;
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
  addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(rsock, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
    perror("Failed to bind.");
    return 1;
  }

  if (listen(rsock, 5) != 0) {
    perror("Failed to listen.");
    return 1;
  }

  while (1) {
    len = sizeof(client);
    wsock = accept(rsock, (struct sockaddr *)&client, &len);

    char reqbuf[4096];

    // readfile
    FILE *fp;
    char *ascii;
    long numbytes;

    fp = fopen("ascii.txt", "r");
    if (fp == NULL) {
      perror("Failed to read file.");
      close(wsock);
      return 1;
    };

    fseek(fp, 0L, SEEK_END);
    numbytes = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    ascii = (char *)calloc(numbytes, sizeof(char));
    if (ascii == NULL) {
      perror("Failed to read file.");
      close(wsock);
      return 1;
    };

    fread(ascii, sizeof(char), numbytes, fp);
    fclose(fp);

    send(wsock, ascii, (int)strlen(ascii), 0);
    free(ascii);
    // readfile

    char text[] =
        "This is a IoT device made by ctf4b networks. Password authentication "
        "is required to operate.\n";
    send(wsock, text, (int)strlen(text), 0);

    char welcome[] = "Input password (password is FLAG) > ";
    send(wsock, welcome, (int)strlen(welcome), 0);

    // 入力を受け付ける
    memset(reqbuf, 0, sizeof(reqbuf));
    recv(wsock, reqbuf, sizeof(reqbuf), 0);

    printf("%s", reqbuf);

    int arr[61] = {48,  39, 53, 103, 49, 40,  58, 99, 39, 12,  55, 54, 37,
                   98,  48, 54, 12,  53, 58,  33, 62, 36, 103, 33, 54, 12,
                   50,  61, 50, 98,  42, 32,  58, 96, 12, 33,  54, 37, 96,
                   50,  98, 32, 12,  50, 12,  63, 99, 39, 12,  60, 53, 12,
                   102, 54, 48, 33,  54, 100, 32, 46, 89};

    if (strlen(reqbuf) != 61) {
      char message[] = "Incorrect password.\n";
      send(wsock, message, (int)strlen(message), 0);
      close(wsock);
    }

    for (int i = 0; i < 61; i++) {
      if ((reqbuf[i] ^ 0x53) != arr[i]) {
        char message[] = "Incorrect password.\n";
        send(wsock, message, (int)strlen(message), 0);
        close(wsock);
      }
    }

    char corr[] = "Correct password!!!\n";
    send(wsock, corr, (int)strlen(corr), 0);
    close(wsock);
  };

  close(rsock);

  return 0;
}
