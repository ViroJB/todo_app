#pragma once

#include <fmt/core.h>

#include <iostream>

#include "config/config.h"
#include "database/sqlite_db.h"
#include "todo/todo_controller.h"

namespace TodoApp {

class App {
   public:
    App() = default;
    bool init();
};
}
