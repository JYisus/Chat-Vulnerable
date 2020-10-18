#include "chat.h"
#include "../message/message.h"

// Chat::Chat(std::string remote_ip_, int port_, std::string username_) {
Chat::Chat(const char* remote_ip_, const int remote_port_, const char* username_, const int mode) {
    strcpy(remote_ip, remote_ip_);
    strcpy(username, username_);
    remote_port = remote_port_;
    if (mode == 2) {
        socket = new Socket(remote_ip, 0);
    } else {
        socket = new Socket(remote_ip, remote_port_);
    }
    

}

void Chat::init_conversation() {
    bool quit = false;
    char msg[1024];
    do {
        gets(msg);
        while(!is_valid_message(msg)) {
            printf("Message too long, try again.\n");
            gets(msg);
        }

        send_message(msg);

        if(std::string(msg) == "/quit"){
            quit = true;
        }

        for(int i=0; i < strlen(msg); i++) {
            msg[i] ='\0';
        }

        if(quit == true) {
            printf("Bye!\n");
        }
    } while(!quit);
}

bool Chat::is_valid_message(const char* msg) {
    return ((strlen(msg) > 0) && (strlen(msg) <= 1024));
}

void Chat::send_message(const char* msg) {
    Message message = create_message(msg, username);
    socket->send_to(message, remote_port);

}

void Chat::listen_messages() {
    receive_message();
}

void Chat::receive_message() {

    bool stop_listening = false;
    do {
        //std::mutex mutex_;
        Message message_rcv;
        sockaddr_in rcv_address{};
        socket->receive_from(message_rcv,rcv_address);

        char* rcv_remote_ip = inet_ntoa(rcv_address.sin_addr);
        std::string remote_ip = std::string(rcv_remote_ip);
        int remote_port = ntohs(rcv_address.sin_port);
        std::string auxuser = std::string(message_rcv.user);
        
        if(std::string(message_rcv.text) == "/quit") {
            printf("Bye!\n");
            stop_listening = true;
            return;
        }

        printf("[%ld] %s: %s\n", message_rcv.hour, message_rcv.user, message_rcv.text);


    } while(stop_listening == false);
}

Message Chat::create_message(const char* text_, const char* username_) {
    Message message;
    strcpy(message.text, text_);
    strcpy(message.user, username_);
    std::asctime(std::localtime(&message.hour));

    return message;
}
