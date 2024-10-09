#include "app.h"

// TODO add categories to todo list, edit panel
// TODO add tabs for completed and overdue tasks.
// TODO show uncompleted tasks in the main tab by default and ordered by category.
// TODO now: minimize to tray, notifications, ect.

namespace TodoApp {

bool App::init() {
    fmt::print("hellooo\n");

    TodoController todoController;
    auto todos = todoController.GetAll();
    for (const auto& [id ,todo ]: *todos) {
        fmt::print("todo: {}\n", todo.title);
    }

    return true;
}

}