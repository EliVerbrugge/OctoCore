#ifndef OCTOCOMM_H
#define OCTOCOMM_H

#if defined(_WIN32)
#include "windows/udp_socket.hpp"
#endif

#include "octocomm_message.h"
#include <map>
#include <thread>
#include <string>
#include <atomic>
#include <iostream>
#include <chrono>
#include <vector>

typedef void (*callback)(OctoCommMessage); // function pointer type that takes a message

class OctoComm
{
private:
    UDPSocket udp_node;
    std::map<std::string, std::vector<callback> clbk> callbacks;
    std::thread read_thread_obj;
    bool stop_;

public:
    OctoComm();

    // Sends a packet to the host/port pair. Uses TCP/UDP depending on if reliable or not
    bool OctoComm::write_to(char *host, int port, void *buf, size_t len, bool reliable = true);

    // Method to run a background thread that grabs all TCP/UDP packets and calls the respective callbacks
    void OctoComm::read(bool &stop_, int sock);

    // Method to set a desired callback for a certain topic
    // Will append clbk to list of callbacks for the topic
    void OctoComm::set_callback(std::string topic, callback clbk);

    // Method to clean up OctoComm and any associated threads
    void OctoComm::close();
};

#endif OCTOCOMM_H