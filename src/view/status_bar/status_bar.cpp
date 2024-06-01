#include "status_bar.h"

StatusBar::StatusBar(wxWindow* parent) : wxStatusBar(parent) {
    SetStatusText("Todo App", 0);
}