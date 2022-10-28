#include <iostream>
#include "http_server/http_server.h"

#define HTTP_SERVER_PORT 9091

int main() {
    http::HTTPServer server = http::HTTPServer(HTTP_SERVER_PORT);

    server.start_server();
    server.bind_server();

    while (1) {}

    return 0;
}
