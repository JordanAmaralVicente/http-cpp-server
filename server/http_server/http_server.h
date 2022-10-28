#ifndef HTTP_SERVER
#define HTTP_SERVER

namespace http {
    class HTTPServer {
        private:
            int server_socket;
            int file_descriptor;
            void get_error_message();

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
