#include "octocomm.h"

OctoComm::OctoComm()
{
    udp_node = UDPSocket();
}

bool OctoComm::send_to(char *host, int port, void *buf, size_t len, bool reliable)
{
    if (!reliable)
    {
        udp_node.send_to(host, port, buf, len);
        return true;
    }
    else
    {
        return false;
    }
}

/*
SOCKET OctoComm::connect(char *address)
{
    return connect(address, DEFAULT_PORT);
}

SOCKET OctoComm::connect(char *address, char *port)
{
    SOCKET _sock;

    int iResult = getaddrinfo(address, port, &hints, &result);

    // Check if we were able to fetch the address
    if (iResult != 0)
    {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return NULL;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
    {

        // Create a SOCKET for connecting to server
        _sock = socket(ptr->ai_family, ptr->ai_socktype,
                       ptr->ai_protocol);

        if (_sock == INVALID_SOCKET)
        {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return NULL;
        }

        // Connect to server.
        iResult = ::connect(_sock, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR)
        {
            closesocket(_sock);
            _sock = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (_Sock == INVALID_SOCKET)
    {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return NULL;
    }

    return _sock;
}
*/