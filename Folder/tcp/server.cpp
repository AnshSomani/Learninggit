#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        cerr << "Socket creation failed\n";
        return 1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        cerr << "Bind failed\n";
        return 1;
    }

    listen(serverSocket, 5);
    cout << "TCP Server running on port 8080...\n";

    sockaddr_in clientAddr{};
    socklen_t len = sizeof(clientAddr);
    int clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &len);

    if (clientSocket < 0) {
        cerr << "Accept failed\n";
        return 1;
    }

    cout << "Client connected.\n";

    char buffer[1024];
    int n;

    while ((n = read(clientSocket, buffer, sizeof(buffer))) > 0) {
        buffer[n] = '\0';
        cout << "Received: " << buffer;
        write(clientSocket, buffer, strlen(buffer)); // Echo back
    }

    close(clientSocket);
    close(serverSocket);
    return 0;
}
