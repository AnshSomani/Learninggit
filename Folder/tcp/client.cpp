#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        cerr << "Connection failed\n";
        return 1;
    }

    char msg[1024], buffer[1024];

    while (true) {
        cout << "Enter message: ";
        cin.getline(msg, 1024);

        write(clientSocket, msg, strlen(msg));

        int n = read(clientSocket, buffer, 1024);
        buffer[n] = '\0';

        cout << "Server replied: " << buffer << endl;
    }

    close(clientSocket);
    return 0;
}
