#include "src/octocomm.h"

int main(int argc, char **argv)
{
    OctoComm octo_node = OctoComm();
    char buf[6] = "12345";
    int bufint[6] = {1, 2, 3, 4, 5, 6};
    bool success = octo_node.send_to("127.0.0.1", 12007, bufint, sizeof(bufint), false);

    return 0;
}