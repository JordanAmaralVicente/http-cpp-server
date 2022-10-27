#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <bits/stdc++.h>
#include <string>

#include "http_client.h"

namespace http {
    HTTPClient::HTTPClient(int port) {
        this->host_port = port;
    }

    void HTTPClient::setup_socket() {
        this->socket_client = socket(AF_INET, SOCK_STREAM, 0);
    }

    void HTTPClient::connect_socket() {
        struct sockaddr_in dest_addr;

        dest_addr.sin_family = AF_INET;
        dest_addr.sin_port = htons(this->host_port);
        dest_addr.sin_addr.s_addr = inet_addr(INADDR_ANY);
        memset(&(dest_addr.sin_zero), '\0', 8);

        int connection_result = connect(
            this->socket_client,
            (struct sockaddr *) &dest_addr,
            sizeof(struct sockaddr)
        );

        if (connection_result < 0) {
            std::cout << "Couldn't connect with the server ";
            std::cout << "ERRNO: " << connection_result << std::endl;
        }
    }
};
