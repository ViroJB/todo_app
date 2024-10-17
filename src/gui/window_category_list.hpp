#pragma once
#include <complex.h>
#include <todo/todo_controller.h>

#include <map>

#include "gui_style.hpp"
#include "todo/category.hpp"

namespace TodoApp {

class WindowCategoryList {
   public:
    static void draw(std::shared_ptr<GuiStyle> &style, std::shared_ptr<TodoController> &todoController);
};

}
