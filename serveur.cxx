#include "fonction.h"

int main(int argc, char const *argv[]) {
    int port = 0;
    if (argc < 2)
        ExitErreur("argument non valable");
    if (argc == 2)
        port = stoi(argv[1]);
    else
        port = PORT;

    int sock_serveur = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in sockaddr_serveur{};
    sockaddr_serveur.sin_family = AF_INET;
    sockaddr_serveur.sin_port = htons(port);
    sockaddr_serveur.sin_addr.s_addr = htonl(INADDR_ANY);

    int yes = 1;
    if (setsockopt(sock_serveur, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
        ExitErreur("setsockopt()");

    if (bind(sock_serveur, (sockaddr *) &sockaddr_serveur, sizeof(sockaddr_serveur)) == -1)
        ExitErreur("bind()");

    if (listen(sock_serveur, BACKLOG))
        ExitErreur("listen()");
    cout << "Serveur en écoute sur le port TCP : " << port << endl;
    for (int i = 0; i < NB_CLIENTS; ++i) {
        cout << "En attente d'un client :" << endl;
        int sock_client = accept(sock_serveur, nullptr, nullptr);
        if (sock_client == -1)
            ExitErreur("accept()");

        cout << "Client n°" << i + 1 << " est connecté" << endl;

        while (true) {


            string message;

            if (!ReadLineOld(sock_client, message))
                break;
            cout << "Client : " << message;
            if (message == "bye\n" || message == "bye\r\n")
                break;

            cout << "Serveur : ";
            getline(cin, message);
            message += '\n';
            write(sock_client, message.c_str(), message.size());
        }
        close(sock_client);
        cout << "le client est partie" << endl;
    }
    close(sock_serveur);
    return 0;
}
