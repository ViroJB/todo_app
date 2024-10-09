#pragma once

#include <fmt/core.h>

#include "config/config.h"
#include "database/sqlite_db.h"
#include "todo/todo_controller.h"
#include "gui/gui.hpp"

namespace TodoApp {

class App {
   public:
    bool init();
    void mainLoop();
};

}  // namespace TodoApp
