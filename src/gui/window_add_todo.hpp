#pragma once
#include <complex.h>
#include <todo/todo_controller.h>

#include <map>
#include <vector>

#include "gui_style.hpp"

namespace TodoApp {

class WindowAddTodo {
   public:
    static void draw(std::shared_ptr<GuiStyle>& style, const std::shared_ptr<TodoController>& todoController);
};

}  // namespace TodoApp
