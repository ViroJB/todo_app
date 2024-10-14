#pragma once
#include <complex.h>

#include <map>

#include "gui_style.hpp"

namespace TodoApp {

class WindowCategoryList {
   public:
    static void draw(const std::map<int, std::string> &categories, GuiStyle &style);
};

}
