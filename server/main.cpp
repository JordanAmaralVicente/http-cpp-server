#include <iostream>
#include <stdlib.h>

#include "packages/http_server/http_server.h"

#define HTTP_SERVER_PORT 9093
#define MAX_CONNECTIONS 10

int main() {
    http::HTTPServer server = http::HTTPServer();

    server.start_server();
    server.bind_server();
    server.create_listener();

    while (1) {
        server.accept_pending_connections();
        server.receive_messages_runtime();
    }

    return 0;
}
