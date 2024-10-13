#include "app.h"

#include "commands/command_handler.hpp"

namespace TodoApp {

bool App::init() {
    CommandHandler commandHandler;
    commandHandler.queueCommand<ExampleCommand>(5, 5);
    commandHandler.queueCommand<ExampleCommand>(10, 5);
    commandHandler.queueCommand<ExampleCommand>();
    commandHandler.executeCommands();

    TodoController todoController;
    auto todos = todoController.GetAll();
    for (const auto& [id, todo] : *todos) {
        fmt::print("todo: {}\n", todo.title);
    }

    return true;
}

void App::run() {
    Gui gui;
    gui.init();
    const auto window = gui.getWindow();

    while (!glfwWindowShouldClose(window)) {
        gui.render();
    }
}

}  // namespace TodoApp