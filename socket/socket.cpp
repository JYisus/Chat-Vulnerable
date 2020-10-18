#include "socket.h"

//Constructor
Socket::Socket(char* ip_address, int remote_port) {

    remote_address = get_ip_address(ip_address, remote_port);
    // self_address = get_ip_address(ip_address, self_port);


    socket_id = socket(AF_INET,SOCK_DGRAM,0);     //Crea el socket

    if (socket_id < 0){
        throw std::system_error(errno, std::system_category(),
                                 "no se pudo crear el socket");
    }

    int result = bind(socket_id, reinterpret_cast<const sockaddr*>(&remote_address), sizeof(remote_address));   //Hacer el bind con el socket y la IP

    if (result < 0){     //Si el resultado de bind es menor que cero, se lanza una excepción.
        throw std::system_error(errno, std::system_category(),
                                "falló bind");
    }
}

//Destructor
Socket::~Socket() {
    close(socket_id);
}

//Sobrecarga del operador =
Socket& Socket::operator=(Socket&& rhs) {
    socket_id = rhs.socket_id;
    rhs.socket_id = -1;
    return *this;
}

//send_to: envía un mensaje a message
void Socket::send_to(const Message& message, int remote_port) {

    sockaddr_in address = get_ip_address("127.0.0.1", remote_port);

    int result = sendto(socket_id, &message, sizeof(message), 0,
        reinterpret_cast<const sockaddr*>(&address),
        sizeof(address));

    if (result < 0) {
        throw std::system_error(errno, std::system_category(),
                                "No se ha podido enviar el mensaje.");
    }
}

//receive_from: escucha por el socket creado para recibir un mensaje
void Socket::receive_from(Message& message, sockaddr_in& address)
{
    socklen_t src_len = sizeof(address);
    int result = recvfrom(socket_id, &message, sizeof(message), 0,
        reinterpret_cast<sockaddr*>(&address), &src_len);
    // Tratar este error
    if (result < 0)
    {
        throw std::system_error(errno, std::system_category(),
                                "No se ha podido recibir el mensaje.");
    }
}

sockaddr_in Socket::get_ip_address(const char* ip_address, int port) {
    
    sockaddr_in new_address{};    // Se recomienda inicializar la estructura a 0

    new_address.sin_family = AF_INET;     // Indicamos que el dominio de la dirección es AF_INET

    if(strcmp(ip_address,"")){                                    // Si la cadena en address está vacía, se emplea INADDR_ANY
        new_address.sin_addr.s_addr = htonl(INADDR_ANY);
    } else {                                                    // En caso contrario, empleamos la dirección indicada
        // char caddress[16];

        // ip_address.copy(caddress, sizeof(caddress) - 1, 0);
        inet_aton(ip_address, &new_address.sin_addr);
    }

    new_address.sin_port = htons(port);   // Asignamos el puerto

    return new_address;
}