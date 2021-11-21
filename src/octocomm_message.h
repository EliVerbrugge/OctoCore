#ifndef OCTOCOMM_MESSAGE_H
#define OCTOCOMM_MESSAGE_H

const int TOPIC_LENGTH = 100;
const int version = 1;

struct OctoCommMessage
{
    int octocomm_version;
    char topic[TOPIC_LENGTH]; // the topic of the message
    int data_count;           // how many distinct entries there are in the packet
    int seq_num;              // can be used to determine order if there are multiple messages in sequnece, defaults to -1
    void *data;               // the actual data, type can be determined from the topic
};

#endif OCTOCOMM_MESSAGE_H