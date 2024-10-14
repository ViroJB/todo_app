#pragma once
#include <complex.h>
#include <todo/todo.h>

#include <map>

#include "gui_style.hpp"

namespace TodoApp {

class WindowTodoList {
   public:
    static void draw(std::map<int, Todo>* todoList, GuiStyle style);
};

}  // namespace TodoApp
