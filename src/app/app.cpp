#include "app.h"

// #include "commands/command_handler.hpp"

namespace TodoApp {

bool App::init() {
    // CommandHandler commandHandler;
    // commandHandler.queueCommand<ExampleCommand>(5, 5);
    // commandHandler.queueCommand<ExampleCommand>(10, 5);
    // commandHandler.queueCommand<ExampleCommand>();

    // std::shared_ptr<TodoController> tc = std::make_shared<TodoController>();
    // std::shared_ptr<Todo> td = std::make_shared<Todo>();
    // td->description = "todo add command, hehehehehe";
    // commandHandler.queueCommand<AddTodoCommand>(tc, td);

    // commandHandler.executeCommands();

    return true;
}

void App::run() {
    Gui gui;
    gui.init();
    const auto window = gui.getWindow();

    while (!glfwWindowShouldClose(window)) {
        gui.render();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        // do this inside the gui render?
        // if (ImGui::IsWindowFocused()) {
        //     std::this_thread::sleep_for(std::chrono::milliseconds(10));
        // } else {
        //     std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // }
    }
}

}  // namespace TodoApp