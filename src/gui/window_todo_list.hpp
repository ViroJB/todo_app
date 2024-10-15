#pragma once
#include <complex>
#include <todo/todo.h>

#include <map>

#include "gui_style.hpp"

namespace TodoApp {

class WindowTodoList {
   public:
    static void draw(std::map<int, Todo>* todoList, GuiStyle style);
};

}  // namespace TodoApp
