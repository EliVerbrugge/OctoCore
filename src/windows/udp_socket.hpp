#ifndef UDP_SOCKET_H
#define UDP_SOCKET_H

#include "win_sockets.h"
#include <iostream>
#include <thread>

const int BUF_LEN = 500;

class UDPSocket
{
private:
    struct sockaddr_in SenderAddr;
    int SenderAddrSize = sizeof(SenderAddr);
    struct sockaddr_in RecvAddr;
    unsigned short Port = 27015;
    int RecvSocket;

    std::thread read_thread_obj;
    WSADATA wsaData;
    int iResult = 0;

public:
    int begin()
    {
        //-----------------------------------------------
        // Initialize Winsock
        iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult != NO_ERROR)
        {
            wprintf(L"WSAStartup failed with error %d\n", iResult);
        }
        //-----------------------------------------------
        // Create a receiver socket to receive datagrams
        RecvSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

        if (RecvSocket == INVALID_SOCKET)
        {
            wprintf(L"socket failed with error %d\n", WSAGetLastError());
        }
        //-----------------------------------------------
        // Bind the socket to any address and the specified port.
        RecvAddr.sin_family = AF_INET;
        RecvAddr.sin_port = htons(Port);
        RecvAddr.sin_addr.s_addr = htonl(INADDR_ANY);

        char yes = 1;
        if (setsockopt(RecvSocket, SOL_SOCKET, SO_REUSEADDR,
                       &yes, sizeof(yes)) < 0)
        {
            fprintf(stderr, "setsockopt() failed. Error: %d\n", WSAGetLastError());
        }
        iResult = bind(RecvSocket, (SOCKADDR *)&RecvAddr, sizeof(RecvAddr));
        if (iResult != 0)
        {
            wprintf(L"bind failed with error %d\n", WSAGetLastError());
        }
        return RecvSocket;
    }

    // A sample of the select() return value
    int recvfromTimeOutUDP(SOCKET socket, long sec, long usec)

    {
        // Setup timeval variable
        struct timeval timeout;
        struct fd_set fds;
        timeout.tv_sec = sec;
        timeout.tv_usec = usec;

        // Setup fd_set structure
        FD_ZERO(&fds);
        FD_SET(socket, &fds);

        // Return value:
        // -1: error occurred
        // 0: timed out
        // > 0: data ready to be read
        return select(0, &fds, 0, 0, &timeout);
    }

    void read(int sock, char *recvBuf, int len)
    {
        struct sockaddr_in SenderAddr;
        int SenderAddrSize = sizeof(SenderAddr);

        //Clear the buffer to make sure there was no old data
        iResult = recvfrom(sock,
                           recvBuf, len, 0, (SOCKADDR *)&SenderAddr, &SenderAddrSize);
        if (iResult == SOCKET_ERROR)
        {
            wprintf(L"recvfrom failed with error %d\n", WSAGetLastError());
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
        sendto(RecvSocket, (const char *)buf, (int)len, 0, (struct sockaddr *)&dest, sizeof(dest));
    }
};

#endif