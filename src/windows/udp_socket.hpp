#ifndef UDP_SOCKET_H
#define UDP_SOCKET_H

#include "win_sockets.h"

class UDPSocket
{
private:
    WSADATA wsaData;
    SOCKET _udp_server_sock;
    struct sockaddr_in result;
    char _message[200];

public:
    UDPSocket()
    {
        // Initializing Winsock
        int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

        // Create UDP server socket
        _udp_server_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

        if (_udp_server_sock == SOCKET_ERROR)
        {
            sprintf_s(_message, "Failed to create UDP server socket!");
            return;
        }

        // Prepare the UDP socket structure
        struct sockaddr_in server;
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons(DEFAULT_UDP_PORT);

        // Bind the UDP socket
        if (bind(_udp_server_sock, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
        {
            sprintf_s(_message, "Binding the UDP socket failed");
            return;
        }
    }
    void send_to(char *host, void *buf, size_t len)
    {
        send_to(host, DEFAULT_UDP_PORT, buf, len);
    }

    void send_to(char *host, int port, void *buf, size_t len)
    {
        // Setup address structure
        sockaddr_in dest;
        memset((char *)&dest, 0, sizeof(dest));
        dest.sin_family = AF_INET;
        dest.sin_port = htons(port);
        InetPton(AF_INET, (PCSTR)(host), &dest.sin_addr.s_addr);

        // Send buffer to our desired host/port combination
        sendto(_udp_server_sock, (const char *)buf, (int)len, 0, (struct sockaddr *)&dest, sizeof(dest));
    }
};

#endif