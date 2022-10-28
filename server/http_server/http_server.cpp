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

        struct sockaddr_in sock_address;

        sock_address.sin_family = AF_INET;
        sock_address.sin_port = htons(port);
        sock_address.sin_addr.s_addr = inet_addr("192.168.18.83");
        memset(&(sock_address.sin_zero), '\0', 8);

        this->sockadd_in = sock_address;

        this->sockaddr = (struct sockaddr *) &sock_address;
        this->external_sockaddr = (struct sockaddr *) &this->external_sockadd_in;

        this->sockaddr_len = (socklen_t *) sizeof(this->sockaddr);
    }

    HTTPServer::~HTTPServer() {
        this->close_connection();
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
        int bind_response = bind(
            this->server_socket,
            this->sockaddr,
            sizeof(struct sockaddr)
        );

        if (bind_response < 0) {
            this->get_error_message();
            return;
        }

        std::cout << "Server binded successfuly!" << std::endl;
        this->show_binded_socket_info();
	}

    void HTTPServer::create_listener() {
        int listerner_result = listen(this->server_socket, this->max_connections);

        if (listerner_result < 0) {
            this->get_error_message();
        }
    }

    void HTTPServer::accept_pending_connections() {
        socklen_t sin_size = sizeof(struct sockaddr_in);
        
        int acception_result = accept(
            this->server_socket,
            this->external_sockaddr,
            &sin_size
        );

        if (acception_result < 0) {
            this->get_error_message();
            return;
        }
    }

    void HTTPServer::show_binded_socket_info() {
        char server_ip_address[16];
        unsigned int server_port = ntohs(this->sockadd_in.sin_port);

        getsockname(
            this->server_socket,
            this->sockaddr,
            this->sockaddr_len
        );

        inet_ntop(
            AF_INET,
            &this->sockadd_in.sin_addr,
            server_ip_address,
            sizeof(server_ip_address)
        );
        
        std::cout << "Ip Address: " << server_ip_address << std::endl;
        std::cout << "Port: " << server_port << std::endl; 
    }

    void HTTPServer::close_connection() {
        int shutdown_result = shutdown(this->server_socket, SHUT_RDWR);

        if (shutdown_result < 0) {
            this->get_error_message();
        }

        std::cout << "Connection closed sucessfuly" << std::endl;
    }
};
