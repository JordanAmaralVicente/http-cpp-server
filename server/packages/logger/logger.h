#include <iostream>

#ifndef INTERNAL_LOGGER
#define INTERNAL_LOGGER

#define INFO 0
#define ERROR 1
#define WARN 2

#define LOG_FILE_PATH "logs/log_file.log"

namespace logger {
    class Logger {
        private:
            static void print_blue(std::string message); // INFO
            static void print_yellow(std::string message); // WARNING
            static void print_red(std::string message); // ERROR
            
            static bool save_log(std:: string message);

        public:
            static void log(std::string message, int LOG_LEVEL);
    };
};

#endif
