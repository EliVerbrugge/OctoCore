#ifndef OCTOCOMM_MESSAGE_H
#define OCTOCOMM_MESSAGE_H

#include <iostream>

const int TOPIC_LENGTH = 100;
const int version = 1;

struct OctoCommMessage
{
    int octocomm_version;
    char topic[TOPIC_LENGTH]; // the topic of the message
    int data_count;           // how many distinct entries there are in the packet
    void *data;               // the actual data, type can be determined from the topic
};

void parse_message(char *data, int len);

#endif OCTOCOMM_MESSAGE_H