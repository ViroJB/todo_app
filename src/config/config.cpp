#include "config.h"

const std::string Config::APP_NAME = "ToDo App";
const std::string Config::APP_VERSION = "0.1.0";
const int Config::APP_DEFAULT_WIDTH = 800;
const int Config::APP_DEFAULT_HEIGHT = 600;
const int Config::APP_MIN_WIDTH = 800;
const int Config::APP_MIN_HEIGHT = 600;
const char* Config::DB_FILE = "todo.db";

// wxWidgets IDs
const int Config::ID_TODO_ADD = 0;
const int Config::ID_TODO_TITLE_TEXTCTRL = 1;
const int Config::ID_TODO_DESCRIPTION_TEXTCTRL = 2;