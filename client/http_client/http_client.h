#ifndef HTTP_CLIENT
#define HTTP_CLIENT

namespace http {
    class HTTPClient {
        private:
            int socket_client;
            int host_port;
            char* host_addr;

        public:
            HTTPClient(int port);
           
            void setup_socket();
            void connect_socket();
    };
};

#endif
