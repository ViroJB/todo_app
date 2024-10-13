#pragma once
#include <complex.h>
#include <todo/todo.h>

#include <map>

namespace TodoApp {

class WindowTodoList {
   public:
    void draw(std::map<int, Todo>* todoList);
};

}  // namespace TodoApp
