#include <iostream>
#include <unistd.h> // read write
#include <sys/socket.h> // socket
#include <netinet/in.h> // sockaddr_in
#include <arpa/inet.h> // inet_aton

#define NB_CLIENTS 10
#define BACKLOG 128
#define TAILLE_BUFFER 16
#define PORT 1234
using namespace std;

void ExitErreur(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

unsigned ReadLineOld(int fd, string &msgIn) {


    char buffer[TAILLE_BUFFER];
    msgIn = "";
    while (true) {
        unsigned  n = read(fd, buffer, sizeof(buffer));
        if (!n) return 0;
        if (n == -1) return -1;

        int i;
        for (i = 0; i < n; ++i)
            if (buffer[i] == '\n') break;

        if (i < n) {
            msgIn += string(buffer, i + 1);
            break;
        } else
            msgIn += string(buffer, n);

    }
    return msgIn.size();
}