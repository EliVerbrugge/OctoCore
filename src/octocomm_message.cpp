#include "octocomm_message.h"

void parse_message(char *data, int len)
{
    OctoCommMessage msg = OctoCommMessage();

    // Parse version as the first 4 bytes
    msg.octocomm_version = (data[3] << 24) | (data[2] << 16) | (data[1] << 8) | data[0];

    // Parse the next bytes as the topic string
    int index = 4;
    for (; index < TOPIC_LENGTH; index++)
    {
        // A "\" indicates end of topic
        if (data[index] == '\\')
        {
            index++;
            break;
        }
        else
        {
            msg.topic[index - 4] = data[index]; //index is offset by 4 due to version parsing
        }
    }

    // Parse data_count as the next 4 bytes
    msg.data_count = (data[index + 3] << 24) | (data[index + 2] << 16) | (data[index + 1] << 8) | data[index];

    // TODO: Debug log contents of packet
    std::cout << "New Packet" << std::endl;
    std::cout << "----------" << std::endl;
    std::cout << "Version: " << msg.octocomm_version << std::endl;
    std::cout << "Topic: " << msg.topic << std::endl;
    std::cout << "Data Count: " << msg.data_count << std::endl;
    std::cout << std::endl;
}
