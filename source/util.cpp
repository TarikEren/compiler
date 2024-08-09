#include "../headers/util.hpp"
#include <iostream>

void util::log(util::Loglevel level, const std::string& message) {
    switch (level) {
        case INFO:
            std::cout << util::INFO_SEQUENCE << message << std::endl;
            break;
        case WARNING:
            std::cout << util::WARNING_SEQUENCE << message << std::endl;
            break;
        case ERROR:
            std::cout << util::ERROR_SEQUENCE << message << std::endl;
            break;
    }
}