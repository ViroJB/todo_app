#pragma once
#pragma warning(disable : 4996) // NOTE this is here, because wxwidgets throws alot of warnings otherwise... sucks

#include <iostream>
#include <wx/wx.h>
#include <wx/event.h>

#include "../config/config.h"
#include "../database/sqlite_db.h"
#include "../view/main_frame.h"

class App : public wxApp {
   public:
    App() {}
    bool OnInit();
};