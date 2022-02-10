#include "octocomm.h"

OctoComm::OctoComm()
{
    // Create the UDP Socket
    udp_node = UDPSocket();
    int sock = udp_node.begin();

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
    std::cout << "Thread" << std::endl;
    char RecvBuf[1024];
    int BufLen = 1024;

    while (!stop_)
    {
        memset(RecvBuf, '0', BufLen);
        udp_node.read(sock, RecvBuf, BufLen);

        // TODO: call octocomm_message parse() here
        parse_message(RecvBuf, BufLen);
        // TODO: check for topic in callbacks, and call with packet if appropriate
    }
}

void OctoComm::close()
{
    stop_ = true;
    read_thread_obj.join();
}