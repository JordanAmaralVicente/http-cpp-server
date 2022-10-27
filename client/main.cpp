#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "http_client/http_client.h"

int main(){
    int dest_port = 9091;

    http::HTTPClient client = http::HTTPClient(dest_port);

    client.setup_socket();
    client.connect_socket();

    return 0;
}
