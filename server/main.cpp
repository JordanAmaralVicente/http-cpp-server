#include <iostream>
#include "http_server/http_server.h"

#define HTTP_SERVER_PORT 9091
#define MAX_CONNECTIONS 10

int main() {

    http::HTTPServer server = http::HTTPServer(HTTP_SERVER_PORT, MAX_CONNECTIONS);

    server.start_server();
    server.bind_server();
    server.create_listener();

    while (1) {}

    return 0;
}
