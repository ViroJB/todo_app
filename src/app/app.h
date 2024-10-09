#pragma once

#include <fmt/core.h>

#include <iostream>

#include "config/config.h"
#include "database/sqlite_db.h"

class App {
   public:
    App() {}
    bool OnInit();
};