#include <netinet/in.h>

#ifndef HTTP_SERVER
#define HTTP_SERVER

namespace http {
    class HTTPServer {
        private:
            struct sockaddr * sockaddr;
            struct sockaddr_in sockadd_in;

            socklen_t * sockaddr_len;
            int server_socket;
            void get_error_message();
            void show_binded_socket_info();

        public:
            HTTPServer(int port, int max_connections);
            
            int server_port;
            int max_connections;
            
            void start_server();
            void bind_server();
            void create_listener();
    };
};

#endif
