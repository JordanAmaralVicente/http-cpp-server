#include <iostream>
#include <string.h>
#include "http_client/http_client.h"

int main(){
    std::string address;
    int port;

    std::cout << "Porta: "; std::cin >> port;
    std::cout << "Endereço: "; std::cin >> address;

    http::HTTPClient client = http::HTTPClient((char *)address.c_str(), port);

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
