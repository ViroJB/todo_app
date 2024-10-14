#pragma once
#include <complex.h>

#include <map>
#include <vector>

#include "gui_style.hpp"

namespace TodoApp {

class WindowAddTodo {
   public:
    static void draw(const std::vector<const char *> &categories, GuiStyle style);
};

}  // namespace TodoApp
