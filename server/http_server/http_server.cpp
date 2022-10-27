#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <bits/stdc++.h>

#include "http_server.h"

namespace http {
    HTTPServer::HTTPServer(int port) {
        this->server_port = port;
    }

    void HTTPServer::start_server() {
        this->server_socket = socket(AF_INET, SOCK_STREAM, 0);

        if (this->server_socket < 0) {
            std::cout << "Couldn't stablish a connection";
            std::cout << "ERRNO: " << this->server_socket << std::endl;
        }
    }

    void HTTPServer::bind_server() {
        struct sockaddr_in socket_address;

        socket_address.sin_family = AF_INET;
        socket_address.sin_port = htons(this->server_port);
        socket_address.sin_addr.s_addr = inet_addr(INADDR_ANY);
        memset(&(socket_address.sin_zero), '\0', 8);

        int bind_response = bind(
            this->server_socket,
            (struct sockaddr *)&socket_address,
            sizeof(struct sockaddr)
        );

        if (bind_response < 0) {
            std::cout << "Couldn't bind socket address";
            std::cout << "ERRNO: " << bind_response << std::endl;
            return;
        }
        
        std::cout << "Server binded successfuly!" << std::endl;
    }
};
