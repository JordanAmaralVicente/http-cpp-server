#include <iostream>
#include <string.h>
#include "http_client/http_client.h"

int main(){
    http::HTTPClient client = http::HTTPClient(9091);

    client.setup_socket();
    client.connect_socket();

    int opt;

    do {
        std::string msg;

        std::cout << "Digite uma mensagem: ";
        std::cin >> msg;

        char * message = (char *) msg.c_str();

        client.send_message(message);

        std::cout << "Digite 0 para continuar..." << std::endl;
        std::cin >> opt;
    } while (opt == 0);

    return 0;
}
