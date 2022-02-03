#include "octocomm.h"

OctoComm::OctoComm()
{
    // Create the UDP Socket
    udp_node = UDPSocket();
    int sock = udp_node.begin();
    std::this_thread::sleep_for(std::chrono::milliseconds(600));

    // Start the reading thread
    stop_ = false;
    read_thread_obj = std::thread(&OctoComm::read, this, std::ref(stop_), sock);
}

bool OctoComm::write_to(char *host, int port, void *buf, size_t len, bool reliable)
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

void OctoComm::set_callback(std::string topic, callback clbk)
{
    // Set the entry for the topic to the desired callback
    callbacks[topic] = clbk;
    return;
}

void OctoComm::read(bool &stop_, int sock)
{
    std::cout << "Thread";
    char *data = new char();
    while (!stop_)
    {
        data = udp_node.read(sock);

        std::cout << data << std::endl;
        // TODO: call octocomm_message parse() here
        // TODO: check for topic in callbacks, and call with packet if appropriate
    }
}

void OctoComm::close()
{
    stop_ = true;
    read_thread_obj.join();
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