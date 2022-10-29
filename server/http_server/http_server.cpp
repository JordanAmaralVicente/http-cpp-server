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
    HTTPServer::HTTPServer(char * addr, int port, int max_connections) {
        this->server_port = port;
        this->max_connections = max_connections;

        struct sockaddr_in sock_address;

        sock_address.sin_family = AF_INET;
        sock_address.sin_port = htons(port);
        sock_address.sin_addr.s_addr = inet_addr(addr);
        memset(&(sock_address.sin_zero), '\0', 8);

        this->sockadd_in = sock_address;

        this->sockaddr = (struct sockaddr *) &sock_address;

        this->sockaddr_len = (socklen_t *) sizeof(this->sockaddr);
    }

    HTTPServer::HTTPServer(char * addr, int port) {
        int default_max_connections = 10;

        this->server_port = port;
        this->max_connections = default_max_connections;

        struct sockaddr_in sock_address;

        sock_address.sin_family = AF_INET;
        sock_address.sin_port = htons(port);
        sock_address.sin_addr.s_addr = inet_addr(addr);
        memset(&(sock_address.sin_zero), '\0', 8);

        this->sockadd_in = sock_address;
        this->sockaddr = (struct sockaddr *) &sock_address;
        this->sockaddr_len = (socklen_t *) sizeof(this->sockaddr);
    }

    HTTPServer::HTTPServer() {
        int default_max_connections = 10;
        int default_port = 9091;

        this->server_port = default_port;
        this->max_connections = default_max_connections;

        struct sockaddr_in sock_address;

        sock_address.sin_family = AF_INET;
        sock_address.sin_port = htons(default_port);
        sock_address.sin_addr.s_addr = htonl(INADDR_ANY);
        memset(&(sock_address.sin_zero), '\0', 8);

        this->sockadd_in = sock_address;
        this->sockaddr = (struct sockaddr *) &sock_address;
        this->sockaddr_len = (socklen_t *) sizeof(this->sockaddr);
    }

    HTTPServer::~HTTPServer() {
        this->close_connection();
    }

    void HTTPServer::get_error_message() {
        std::cout << "Something went wrong" << std::endl;
        std::cout << "ERRNO: " << GETSOCKETERRNO() << std::endl;
        std::cout << "message: " << strerror(GETSOCKETERRNO()) << std::endl << std::endl;
        exit(EXIT_FAILURE);
    }

    void HTTPServer::start_server() {
        this->server_socket = socket(AF_INET, SOCK_STREAM, 0);

        if (this->server_socket < 0) {
            std::cout << "on: start_server ";
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
            std::cout << "on: bind_server ";
            this->get_error_message();
            return;
        }

        std::cout << "Server binded successfuly!" << std::endl;
        this->show_binded_socket_info();
	}

    void HTTPServer::create_listener() {
        int listerner_result = listen(this->server_socket, this->max_connections);

        if (listerner_result < 0) {
            std::cout << "on: create_listener ";
            this->get_error_message();
        }
    }

    void HTTPServer::accept_pending_connections() {
        this->enable_sockets = accept(this->server_socket, NULL, NULL);

        this->external_sockaddr = (struct sockaddr *) &this->external_sockadd_in;

        if (this->enable_sockets < 0) {
            std::cout << "on: accept_pending_connections ";
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
            std::cout << "on: close_connection ";
            this->get_error_message();
        }

        std::cout << "Connection closed sucessfuly" << std::endl;
    }

    std::string HTTPServer::receive_messages() {
        int default_flag = 0;
        char buffer[1024];

        int message_status = recv(
            this->enable_sockets,
            buffer,
            sizeof (buffer),
            default_flag
        );

        if (message_status == 0) {
            std::cout << "Connection closed by the client" << std::endl;
            return "";
        } else if (message_status < 0) {
            std::cout << "on: receive_messages ";
            this->get_error_message();
            return "";
        }

        std::string message = static_cast<std::string>(buffer);

        return message;
    }

    void HTTPServer::receive_and_show_message() {
        std::string message = this->receive_messages();

        std::cout << message << std::endl;
    }

    void HTTPServer::receive_messages_runtime() {
        int default_flag = 0;
        char buffer[1024];
        std::string final_message = std::string();
        int bytes_received;

        do {
            bytes_received = recv(
                this->enable_sockets,
                buffer,
                sizeof (buffer),
                default_flag
            );

            std::cout << buffer << std::endl;
        } while (bytes_received > 0);

        if (bytes_received == 0) {
            std::cout << "Connection closed by the client" << std::endl;
            return;
        } else if (bytes_received < 0) {
            std::cout << "on: receive_messages_runtime ";
            this->get_error_message();
            return;
        }

        return;
    }
};
