#ifndef SOCKET_H
#define SOCKET_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <system_error>
#include <unistd.h>
#include "../message/message.h"

class Socket {
    int socket_id;        // Identificador del socket
    sockaddr_in remote_address;
public:
    Socket(char*,int);
    ~Socket();
    Socket(const Socket& that) = delete;    // Eliminar constructor de copia
    Socket& operator=(Socket&& rhs);
    void send_to(const Message& message, int);
    void receive_from(Message& message, sockaddr_in& address);

private:
    sockaddr_in get_ip_address(const char* ip_address, int port);

};

#endif // SOCKET_H
