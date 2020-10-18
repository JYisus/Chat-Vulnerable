#ifndef MESSAGE_H
#define MESSAGE_H
#include <ctime>

struct Message
{
    char user[50];
    char text[1024];
    std::time_t hour;
};

#endif // MESSAGE_H