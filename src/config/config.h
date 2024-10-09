#pragma once

#include <string>


namespace TodoApp {

class Config {
   public:
    static const std::string APP_NAME;
    static const std::string APP_VERSION;
    static const int APP_DEFAULT_WIDTH;
    static const int APP_DEFAULT_HEIGHT;
    static const int APP_MIN_WIDTH;
    static const int APP_MIN_HEIGHT;
    static const char* DB_FILE;
};

}