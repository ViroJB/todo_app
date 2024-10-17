#pragma once
#include <complex.h>
#include <todo/todo.h>
#include <todo/todo_controller.h>

#include <complex>
#include <map>

#include "gui_style.hpp"

namespace TodoApp {

class WindowTodoList {
   public:
    static void draw(std::shared_ptr<GuiStyle> &style, std::shared_ptr<TodoController> &todoController);
};

}  // namespace TodoApp
