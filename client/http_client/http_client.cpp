#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <bits/stdc++.h>
#include <string>

#include "http_client.h"

#define GETSOCKETERRNO() (errno)

namespace http {
    HTTPClient::HTTPClient(char * addr, int port) {
        this->host_port = port;
        this->host_addr = addr;
    }

    HTTPClient::~HTTPClient() {
        this->close_connection();
    }

    void HTTPClient::get_error_message() {
        std::cout << "Something went wrong" << std::endl;
        std::cout << "ERRNO: " << GETSOCKETERRNO() << std::endl;
        std::cout << "message: " << strerror(GETSOCKETERRNO()) << std::endl;
    }

    void HTTPClient::setup_socket() {
        this->socket_client = socket(AF_INET, SOCK_STREAM, 0);

        if (this->socket_client < 0) {
            this->get_error_message();
        }
    }

    void HTTPClient::connect_socket() {
        struct sockaddr_in dest_addr;

        dest_addr.sin_family = AF_INET;
        dest_addr.sin_port = htons(9091);
        dest_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        memset(&(dest_addr.sin_zero), '\0', 8);

        int connection_result = connect(
            this->socket_client,
            (struct sockaddr *) &dest_addr,
            sizeof(struct sockaddr)
        );

        if (connection_result < 0) {
            this->get_error_message();
            return;
        }

        std::cout << "Connected successfully with the server!" << std::endl;
    }

    void HTTPClient::send_message(char * message) {
        int message_length = strlen(message);

        int bytes_sent = send(this->socket_client, message, message_length, 0);

        if (bytes_sent < 0) {
            this->get_error_message();
            return;
        }
        
        std::cout << "Bytes sent: " << bytes_sent << std::endl;
    }

    void HTTPClient::close_connection() {
        int shutdown_result = shutdown(this->socket_client, SHUT_RDWR);

        if (shutdown_result < 0) {
            this->get_error_message();
            return;
        }

        std::cout << "Connection closed successfuly" << std::endl;
    }
};
