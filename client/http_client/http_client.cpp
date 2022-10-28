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
    HTTPClient::HTTPClient(int port) {
        this->host_port = port;
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
        dest_addr.sin_addr.s_addr = inet_addr("192.168.18.83");
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
};
