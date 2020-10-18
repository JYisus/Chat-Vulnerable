#include <cstdio>
#include <iostream>
#include <unistd.h>
#include "chat/chat.h"

enum execMode {
    HELP,
    SERVER,
    CLIENT
};

typedef struct {
    int mode = 0;
    char* remote_ip;
    char* username;
    int port = 0;

} ChatConfig;

ChatConfig getChatConfig(int argc, char* argv[]) {

    ChatConfig chatConfig;

    char c;
    while ((c=getopt(argc, argv, "hs:c:p:u:")) != -1) {
        switch(c) {
            case 'h':
                chatConfig.mode = HELP;
                break;
            case 's':
                chatConfig.mode = SERVER;
                chatConfig.remote_ip = (char *) calloc(strlen(optarg), sizeof(char));
                break;
            case 'c':
                chatConfig.mode = CLIENT;
                chatConfig.remote_ip = (char *) calloc(strlen(optarg), sizeof(char));
                strcpy(chatConfig.remote_ip, optarg);
                break;
            case 'u':
                chatConfig.username = (char *) calloc(strlen(optarg), sizeof(char));
                strcpy(chatConfig.username, optarg);
                break;
            case 'p':
                chatConfig.port = atoi(optarg);
                break;
            case '?':
                break;
            default:
                chatConfig.mode = HELP;
                break;
        }

        
    }

    return chatConfig;
}

void showHelp() {
    printf("Iniciar servidor: ./char -s -p [puerto de escucha]\n");
    printf("Iniciar cliente: ./char -c [ip servidor] -p [puerto del servidor] -u [nombre de user]\n");
}

int main(int argc, char* argv[]) {
    printf(" ---------------\n");
    printf("      CHAT\n");
    printf(" ---------------\n");
    try {
        ChatConfig chatConfig = getChatConfig(argc, argv);

        printf("| Configuration: \
                \n|   - Mode: %d \
                \n|   - Username: %s \
                \n|   - Port: %d\n",chatConfig.mode, chatConfig.username, chatConfig.port);
        
        printf(" ---------------\n");
        
        if (chatConfig.mode == HELP) {
            showHelp();
            return 0;
        }

        if (chatConfig.mode == CLIENT) {
            Chat chat(chatConfig.remote_ip, chatConfig.port, chatConfig.username, chatConfig.mode);
            // Chat chat(std::string(chatConfig.remote_ip), chatConfig.port, std::string(chatConfig.username));
            chat.init_conversation();
            return 0;
        } 

        if (chatConfig.mode == SERVER) {
            Chat chat(chatConfig.remote_ip, chatConfig.port, chatConfig.username, chatConfig.mode);
            chat.listen_messages();
            return 0;
        }



    } catch(...) {
        std::cerr << "Error desconocido" << '\n';
        return 2;
    }








    return 0;
}