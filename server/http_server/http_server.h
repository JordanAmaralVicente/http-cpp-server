#include <netinet/in.h>

#ifndef HTTP_SERVER
#define HTTP_SERVER

namespace http {
    class HTTPServer {
        private:
            struct sockaddr * sockaddr;
            struct sockaddr * external_sockaddr;

            struct sockaddr_in sockadd_in;
            struct sockaddr_in external_sockadd_in;

            socklen_t * sockaddr_len;
            
            int server_socket;
            int enable_sockets;

            void get_error_message();
            void show_binded_socket_info();

        public:
            HTTPServer(char * addr, int port, int max_connections);
            HTTPServer(char * addr, int port);
            HTTPServer();
            ~HTTPServer();
            
            int server_port;
            int max_connections;
            
            void start_server();
            void bind_server();
            void create_listener();
            void accept_pending_connections();
            void close_connection();

            std::string receive_messages();
            void receive_and_show_message();
    };
};

#endif
