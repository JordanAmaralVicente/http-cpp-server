#ifndef HTTP_SERVER
#define HTTP_SERVER

namespace http {
    class HTTPServer {
        private:
            int server_socket;
            int file_descriptor;

        public:
            HTTPServer(int port);
            void start_server();
            void bind_server();
            int server_port;
    };
};

#endif
