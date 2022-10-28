#include "http_client/http_client.h"

int main(){
    http::HTTPClient client = http::HTTPClient(9091);

    client.setup_socket();
    client.connect_socket();

    return 0;
}
