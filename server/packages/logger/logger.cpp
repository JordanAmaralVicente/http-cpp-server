#include <iostream>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fstream>

#include "logger.h"

namespace logger {
    void Logger::print_red(std::string message) {
        std::cout << "\033[31m";
        std::cout << message<< std::endl;
        std::cout << "\033[0m";

        Logger::save_log(message);
    }

    void Logger::print_yellow(std::string message) {
        std::cout << "\033[33m";
        std::cout << message << std::endl;
        std::cout << "\033[0m";

        Logger::save_log(message);
    }

    void Logger::print_blue(std::string message) {
        std::cout << "\033[34m";
        std::cout << message << std::endl;
        std::cout << "\033[0m";

        Logger::save_log(message);
    }

    void Logger::log(std::string message, int LOG_LEVEL) {
        switch (LOG_LEVEL) {
            case INFO:
                Logger::print_blue("[INFO]: ");
                Logger::print_blue(message);
                break;
            case ERROR:
                Logger::print_red("[ERROR]: ");
                Logger::print_red(message);
                break;
            case WARN:
                Logger::print_yellow("[WARN]: ");
                Logger::print_yellow(message);
                break;
            default:
                Logger::print_blue("[DEFAULT]: ");
                Logger::print_blue(message);
                break;
        }
    }

    bool Logger::save_log(std:: string message) {
        std::ofstream log_file;
        
        try {
            // TODO: find a way to create the folder and file automatically
            log_file.open(LOG_FILE_PATH, std::ios::ate | std::ios::in);

            if (log_file.is_open()) {
                log_file << message << "\n";
            }

            log_file.close();

            return true;
        } catch (const std::exception& e) {
            std::cerr << e.what() << '\n';

            return false;
        }
    }
}