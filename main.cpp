#include "src/octocomm.h"

int main(int argc, char **argv)
{
    OctoComm octo_node = OctoComm();
    bool success = octo_node.connect_to("127.0.0.1");

    return 0;
}