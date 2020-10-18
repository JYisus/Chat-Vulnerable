#ifndef CHAT_H
#define CHAT_H
#include <string>
#include "../socket/socket.h"

class Chat {
    char remote_ip[16];
    char username[24];
    Socket* socket;
    int remote_port; 
    public:
        // Chat(std::string remote_ip_, int port_, std::string username);
        Chat(const char* remote_ip_, const int port_, const char* username, const int mode);
        void init_conversation();
        void listen_messages();
    private:
        bool is_valid_message(const char*);
        void send_message(const char*);
        void receive_message();
        Message create_message(const char*, const char*);
};

#endif // CHAT_H