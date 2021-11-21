#ifndef OCTOCOMM_H
#define OCTOCOMM_H

#if defined(_WIN32)
#include "windows/udp_socket.hpp"
#endif

#include "octocomm_message.h"
#include <map>
#include <thread>
#include <string>

typedef void (*callback)(OctoCommMessage); // function pointer type that takes a message

class OctoComm
{
private:
    UDPSocket udp_node;
    std::map<std::string, callback> callbacks;
    std::thread read_thread_obj;

public:
    OctoComm();

    // Sends a packet to the host/port pair. Uses TCP/UDP depending on if reliable or not
    bool OctoComm::write_to(char *host, int port, void *buf, size_t len, bool reliable = true);

    // Method to run a background thread that grabs all TCP/UDP packets and calls the respective callbacks
    void OctoComm::read();

    // Method to set a desired callback for a certain topic
    // NOTE: currently callbacks:topics is a 1:1 relationship
    void OctoComm::set_callback(std::string topic, callback clbk);

    // Method to clean up OctoComm and its children
    void OctoComm::close();

    /*
    // Connects a socket to the desired address, with default port
    SOCKET connect(char *address);
    // Connects a socket to the desired address at designated port
    SOCKET connect(char *address, char *port);
    */
};

#endif OCTOCOMM_H