#ifndef HTTP_CLIENT
#define HTTP_CLIENT

namespace http {
    class HTTPClient {
        private:
            int socket_client;
            int host_port;
            char* host_addr;

        public:
            HTTPClient(char * addr, int port);
            ~HTTPClient();

            void setup_socket();
            void connect_socket();
            void get_error_message();
            void close_connection();

            void send_message(char * message);
    };
};

#endif
