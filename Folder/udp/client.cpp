#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(9090);

    bind(sockfd, (sockaddr*)&serverAddr, sizeof(serverAddr));

    cout << "UDP Server running on port 9090...\n";

    char buffer[1024];
    sockaddr_in clientAddr{};
    socklen_t len = sizeof(clientAddr);

    while (true) {
        int n = recvfrom(sockfd, buffer, sizeof(buffer), 0,
                         (sockaddr*)&clientAddr, &len);

        buffer[n] = '\0';
        cout << "Received: " << buffer;

        sendto(sockfd, buffer, strlen(buffer), 0,
               (sockaddr*)&clientAddr, len);
    }

    close(sockfd);
    return 0;
}
// g++ tcp_server.cpp -o tcp_server
// g++ tcp_client.cpp -o tcp_client
// g++ udp_server.cpp -o udp_server
// g++ udp_client.cpp -o udp_client
// ./tcp_server
