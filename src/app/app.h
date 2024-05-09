#pragma once

#include <iostream>
#include <wx/wx.h>
#include <wx/event.h>
#include <fmt/core.h>

#include "../config/config.h"
#include "../database/sqlite_db.h"
#include "../view/main_frame.h"

class App : public wxApp {
   public:
    App() {}
    bool OnInit();
};