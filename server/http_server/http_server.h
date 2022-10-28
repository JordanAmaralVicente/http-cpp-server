#ifndef HTTP_SERVER
#define HTTP_SERVER

namespace http {
    class HTTPServer {
        private:
            int server_socket;
            int file_descriptor;
            void get_error_message();

        public:
            HTTPServer(int port);
            void start_server();
            void bind_server();
            void create_listener();
            int server_port;
    };
};

#endif
