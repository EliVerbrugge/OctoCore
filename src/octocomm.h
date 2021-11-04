#if defined(_WIN32)
#include "windows/udp_socket.hpp"
#endif

class OctoComm
{
private:
    UDPSocket udp_node;

public:
    OctoComm();

    // Sends a packet to the host/port pair. Uses TCP/UDP depending on if reliable or not
    bool OctoComm::send_to(char *host, int port, void *buf, size_t len, bool reliable);

    /*
    // Connects a socket to the desired address, with default port
    SOCKET connect(char *address);
    // Connects a socket to the desired address at designated port
    SOCKET connect(char *address, char *port);
    */
};