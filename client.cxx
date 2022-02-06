#include "fonction.h"

int main(int argc, char const *argv[]) {

    if (argc != 3)
        ExitErreur("argc non valable");


    int sock_client = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in sockaddr_serveur{};
    sockaddr_serveur.sin_family = AF_INET;
    sockaddr_serveur.sin_port = htons(stoi(argv[2]));
    inet_aton(argv[1], &sockaddr_serveur.sin_addr);

    if (connect(sock_client, (sockaddr *) &sockaddr_serveur, sizeof(sockaddr_serveur)))
        ExitErreur("connect()");
    else
        cout << "Vous êtes maintenant connecté au serveur TCP" << endl;


    while (true) {
        string message;

        cout << "Client : ";
        getline(cin, message);
        message += '\n';
        write(sock_client, message.c_str(), message.size());


        if (!ReadLineOld(sock_client, message))
            break;
        cout << "Serveur : " << message;
        if (message == "bye\n" || message == "bye\r\n")
            break;
    }
    close(sock_client);
    cout << "vous avez quittez le chat TCP" << endl;

    return 0;
}
