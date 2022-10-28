#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <bits/stdc++.h>

#include "http_server.h"

#define GETSOCKETERRNO() (errno)

namespace http {
    HTTPServer::HTTPServer(int port, int max_connections) {
        this->server_port = port;
        this->max_connections = max_connections;
    }

    void HTTPServer::get_error_message() {
        std::cout << "Something went wrong" << std::endl;
        std::cout << "ERRNO: " << GETSOCKETERRNO() << std::endl;
        std::cout << "message: " << strerror(GETSOCKETERRNO()) << std::endl;
    }

    void HTTPServer::start_server() {
        this->server_socket = socket(AF_INET, SOCK_STREAM, 0);

        if (this->server_socket < 0) {
            this->get_error_message();
        }
    }

    void HTTPServer::bind_server() {
        struct sockaddr_in socket_address;

        socket_address.sin_family = AF_INET;
        socket_address.sin_port = htons(this->server_port);
        socket_address.sin_addr.s_addr = inet_addr("192.168.18.83");
        memset(&(socket_address.sin_zero), '\0', 8);

        int bind_response = bind(
            this->server_socket,
            (struct sockaddr *)&socket_address,
            sizeof(struct sockaddr)
        );

        if (bind_response < 0) {
            this->get_error_message();
            return;
        }

        std::cout << "Server binded successfuly!" << std::endl;

        getsockname(
            this->server_socket,
            (struct sockaddr*) &socket_address,
            (socklen_t *) sizeof(socket_address)
        );

        char server_ip_address[16];
        inet_ntop(AF_INET, &socket_address.sin_addr, server_ip_address, sizeof(server_ip_address));
        
        unsigned int server_port = ntohs(socket_address.sin_port);

        std::cout << "Ip Address: " << server_ip_address << std::endl;
        std::cout << "Port: " << server_port << std::endl; 
	}

    void HTTPServer::create_listener() {
        int listerner_result = listen(this->server_socket, this->max_connections);

        if (listerner_result < 0) {
            this->get_error_message();
        }
    }
};
